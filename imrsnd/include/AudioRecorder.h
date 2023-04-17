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

#ifndef ___AUDIORECORDER_H___
#define ___AUDIORECORDER_H___

#include <pthread.h>

#include "AudioFileHeader.h"
#include "Audio.h"

namespace IMR
{

/**
* Class AudioRecorder.
*
* This class implements an audio recorder.
*
* Recording is done by the followind features:
* - Sample Rate = 11025
* - Byte Rate = 22050
* - Number of Channels = 1
* - Bits per sample = 16
*
* After recording, you can retrieve the recorded Audio object and store it in a audio file.
*
* @see AudioFile
*/
class AudioRecorder
{

public:
/** Constructor */
AudioRecorder();
/** Destructor */
~AudioRecorder();

/**
* Sets the device ID for this audio recorder object.
*
* @param int Device ID
*
* @see AudioDevice
*/
void SetDeviceID(int);

/**
* Gets the recorded Audio.
*
* @return the recorded Audio object
*/
const Audio& GetAudio() const;

/**
* Stars recording.
*
* @return 0 if success, 1 otherwise
*/
int Rec();

/**
* Stops recording.
*/
void Stop();

private:
int _devID;
Audio _audio;
AudioFileHeader _fileHeader;
void FillRecordedAudio();

pthread_t _pt;
static void* LaunchThread(void* ptr);
void thread_code();
};

}

#endif
