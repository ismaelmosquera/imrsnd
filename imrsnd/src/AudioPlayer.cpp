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

#include "AudioFile.h"
#include "WaveAudioFile.h"
#include "AudioPlayer.h"


namespace IMR
{

static Audio _audio;
static HANDLE _event;
static HWAVEOUT _outDev;
static WAVEFORMATEX _wFormat;
static WAVEHDR _frame[2];
static WAVEHDR* _lastFrame;

static bool _stopRequested;
static const char* _data;
static unsigned long _dataSize;
static unsigned int _frameSize;
static unsigned long _totalBytesWritten;

static void FillFormatex()
{
_wFormat.wFormatTag = _audio.GetHeader().GetFormatType();
_wFormat.nChannels = _audio.GetHeader().GetNumChannels();
_wFormat.nSamplesPerSec = _audio.GetHeader().GetSampleRate();
_wFormat.nAvgBytesPerSec = _audio.GetHeader().GetByteRate();
_wFormat.nBlockAlign = _audio.GetHeader().GetBlockAlign();
_wFormat.wBitsPerSample = _audio.GetHeader().GetBitsPerSample();
_wFormat.cbSize = 0;
}

static long LaunchFrame(WAVEHDR* frame)
{
	if(_stopRequested || _totalBytesWritten >= _dataSize) return 1;
	if((_totalBytesWritten + _frameSize) > _dataSize)
	{
		_frameSize = _dataSize - _totalBytesWritten;
		frame->dwBufferLength = _frameSize;
		_lastFrame = frame;
	}

	int j = _totalBytesWritten;
		for(int i = 0; i < _frameSize; i++) frame->lpData[i] = _data[j++];

_totalBytesWritten += _frameSize;

frame->dwFlags &= ~WHDR_DONE;
waveOutWrite(_outDev, frame, sizeof(WAVEHDR));

if(frame == _lastFrame) return 1;
return 0;
}

static void CALLBACK HandleEvent(HWAVEOUT outDev, UINT msg, DWORD instance, DWORD param1, DWORD param2)
{
	if(msg == MM_WOM_DONE)
	{
		if(LaunchFrame((WAVEHDR*)param1))
		{
			SetEvent(_event);
		}
	}
}


AudioPlayer::AudioPlayer() : _hasAudio(false), _isPlaying(false)
{
	_devID = 0;
	_stopRequested = false;
}

AudioPlayer::AudioPlayer(const Audio& audio)
{
	AudioPlayer();
SetAudio(audio);
}

AudioPlayer::~AudioPlayer()
{
}

void AudioPlayer::SetAudio(const Audio& audio)
{
	_audio = audio;
_hasAudio = true;
}

bool AudioPlayer::Load(const char* filename)
{
AudioFile* file = new WaveAudioFile();
bool result = file->Load(_audio, filename);
if(result) _hasAudio = true;
delete file;
return result;
}

int AudioPlayer::Play()
{
	if(_isPlaying) return 1;
if(!_hasAudio) return 1;
return pthread_create(&_pt, NULL, LaunchThread, this);
}

void AudioPlayer::Stop()
{
	_isPlaying = false;
_stopRequested = true;
}

void* AudioPlayer::LaunchThread(void* ptr)
{
	((AudioPlayer*)ptr)->thread_code();
	return NULL;
}

void AudioPlayer::thread_code()
{
FillFormatex();
_event = CreateEvent(0, FALSE, FALSE, 0);
if(waveOutOpen(&_outDev, _devID, &_wFormat, (DWORD)HandleEvent, 0, CALLBACK_FUNCTION) != MMSYSERR_NOERROR) return;
_stopRequested = false;
_isPlaying = true;
_lastFrame = NULL;
_frameSize = _audio.GetHeader().GetByteRate();
_dataSize = _audio.GetHeader().GetDataSize();
_data = _audio.GetDataPtr();
_totalBytesWritten = 0;
_frame[0].lpData = new char[_frameSize];
_frame[1].lpData = new char[_frameSize];
_frame[0].dwBufferLength = _frame[1].dwBufferLength = _frameSize;
waveOutPrepareHeader(_outDev, &_frame[0], sizeof(WAVEHDR));
waveOutPrepareHeader(_outDev, &_frame[1], sizeof(WAVEHDR));
if(!LaunchFrame(&_frame[0]))
{
	if(LaunchFrame(&_frame[1]) >= 0)
	{
		WaitForSingleObject(_event, INFINITE);
	}
}
_isPlaying = false;
waveOutReset(_outDev);

if(_frame[0].lpData) delete[] _frame[0].lpData;
if(_frame[1].lpData) delete[] _frame[1].lpData;

waveOutUnprepareHeader(_outDev, &_frame[1], sizeof(WAVEHDR));
waveOutUnprepareHeader(_outDev, &_frame[0], sizeof(WAVEHDR));

waveOutClose(_outDev);

CloseHandle(_event);

pthread_join( _pt, 0);
}

}

// END
