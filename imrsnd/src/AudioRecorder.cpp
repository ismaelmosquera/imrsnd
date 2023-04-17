/*
 * Copyright (c) 2023 Ismael Mosquera Rivera
 *
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 */

#include <windows.h>
#include <mmsystem.h>

#include "AudioRecorder.h"


namespace IMR
{

static HWAVEIN _inDev;
static WAVEFORMATEX _wFormat;
static WAVEHDR _frame[2];

static const unsigned long REC_BUFFER_SIZE = 22050 * 900;
static const unsigned int FRAME_SIZE = 22050;
static char _recBuffer[REC_BUFFER_SIZE];
static unsigned int _frameSize = FRAME_SIZE;
static unsigned long _totalBytesRecorded = 0;
static bool _isRecording = false;
static bool _stopRequested = false;


static void FillFormatex()
{
_wFormat.wFormatTag = 1;  // PCM format.
_wFormat.nChannels = 1;
_wFormat.nSamplesPerSec = 11025;
_wFormat.nAvgBytesPerSec = 22050;
_wFormat.nBlockAlign = 2;
_wFormat.wBitsPerSample = 16;
_wFormat.cbSize = 0;
}

static DWORD WINAPI waveInMsg(LPVOID arg)
{
MSG msg;
while(GetMessage(&msg, 0, 0, 0) == 1)
{
	if((_totalBytesRecorded+_frameSize+11025) > REC_BUFFER_SIZE)
		{
			_isRecording = false;
			_stopRequested = true;
			return 0;
		}

switch(msg.message)
{
	case MM_WIM_DATA:
	if(((WAVEHDR*)msg.lParam)->dwBytesRecorded)
	{
	int bytes_rec = ((WAVEHDR*)msg.lParam)->dwBytesRecorded;
	int j = _totalBytesRecorded;
	for(int i = 0; i < bytes_rec; i++) _recBuffer[j++] = ((WAVEHDR*)msg.lParam)->lpData[i];
	_totalBytesRecorded += bytes_rec;
	if(_isRecording)
	{
	waveInAddBuffer(_inDev, (WAVEHDR*)msg.lParam, sizeof(WAVEHDR));
	}
continue;
}
case MM_WIM_OPEN:
continue;
case MM_WIM_CLOSE:
break;
	}
}
return 0;
}


AudioRecorder::AudioRecorder() : _devID(0)
{
}

AudioRecorder::~AudioRecorder()
{
}

void AudioRecorder::SetDeviceID(int id)
{
	_devID = id;
}

const Audio& AudioRecorder::GetAudio() const
{
	return _audio;
}

int AudioRecorder::Rec()
{
if(_isRecording) return 1;
return pthread_create(&_pt, NULL, LaunchThread, this);
}

void AudioRecorder::Stop()
{
	_isRecording = false;
_stopRequested = true;
}

void AudioRecorder::FillRecordedAudio()
{
	_fileHeader.SetRiffSize(_totalBytesRecorded + 36);
	_fileHeader.SetFmtSize(16);
	_fileHeader.SetFormatType(1);
	_fileHeader.SetNumChannels(1);
	_fileHeader.SetSampleRate(11025);
	_fileHeader.SetByteRate(22050);
	_fileHeader.SetBlockAlign(2);
	_fileHeader.SetBitsPerSample(16);
	_fileHeader.SetDataSize(_totalBytesRecorded);
	_audio.SetHeader(_fileHeader);
	unsigned int data_size = _audio.GetHeader().GetDataSize();
	int frame_size = (int)_audio.GetHeader().GetByteRate();
	unsigned long total_bytes = 0;
	char* frame = new char[frame_size];
	while(total_bytes < data_size)
	{
		if((total_bytes + frame_size) > data_size)
		{
	delete[] frame;
	frame_size = data_size - total_bytes;
	frame = new char[frame_size];
		}
		int j = total_bytes;
		for(int i = 0; i < frame_size; i++) frame[i] = _recBuffer[j++];
		_audio.SetFrame(frame, total_bytes, frame_size);
	total_bytes += frame_size;
	}
	delete[] frame;
}

void* AudioRecorder::LaunchThread(void* ptr)
{
((AudioRecorder*)ptr)->thread_code();
return NULL;
}

void AudioRecorder::thread_code()
{
unsigned long thread_id;
CreateThread(0, 0, (LPTHREAD_START_ROUTINE)waveInMsg, 0, 0, &thread_id);
ZeroMemory(&_frame[0], sizeof(WAVEHDR) * 2);
FillFormatex();
if(waveInOpen(&_inDev, _devID, &_wFormat, (DWORD)thread_id, 0, CALLBACK_THREAD) != MMSYSERR_NOERROR) return;
_frameSize = FRAME_SIZE;
_totalBytesRecorded = 0;
_frame[0].lpData = new char[FRAME_SIZE];
_frame[1].lpData = new char[FRAME_SIZE];
_frame[0].dwBufferLength = _frame[1].dwBufferLength = FRAME_SIZE;
waveInPrepareHeader(_inDev, &_frame[0], sizeof(WAVEHDR));
waveInPrepareHeader(_inDev, &_frame[1], sizeof(WAVEHDR));
waveInAddBuffer(_inDev, &_frame[0], sizeof(WAVEHDR));
waveInAddBuffer(_inDev, &_frame[1], sizeof(WAVEHDR));
_isRecording = true;
_stopRequested = false;
	waveInStart(_inDev);
while(!_stopRequested) ;
_isRecording = false;

FillRecordedAudio();

waveInReset(_inDev);

waveInUnprepareHeader(_inDev, &_frame[1], sizeof(WAVEHDR));
waveInUnprepareHeader(_inDev, &_frame[0], sizeof(WAVEHDR));

		waveInClose(_inDev);

if(_frame[0].lpData) delete[] _frame[0].lpData;
if(_frame[1].lpData) delete[] _frame[1].lpData;

pthread_join( _pt, 0);
}

}

// END
