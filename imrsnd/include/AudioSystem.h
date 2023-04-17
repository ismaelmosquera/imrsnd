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

#ifndef ___AUDIOSYSTEM_H___
#define ___AUDIOSYSTEM_H___

#include <list>

namespace IMR
{

class AudioDevice;
class Player;
class AudioRecorder;
class AudioFile;

/**
* Class AudioSystem.
*
* This class acts like a facade to get the most relevant objects for the IMR audio system.
* It has static methods to do the task.
*
* @see AudioDevice
* @ see AudioInDevice
* @see AudioOutDevice
* @see Player
* @see AudioPlayer
* @see AudioRecorder
* @see AudioFile
* @see WaveAudioFile
*/
class AudioSystem
{

public:

/**
* Gets a list containing all the audio input devices in your system.
*
* @return The list of audio input devices available in your system.
*/
static std::list<AudioDevice*> GetInputDeviceList();

/**
* Gets a list with all the audio output devices available in your system
*
* @return The list of audio output devices available in your system
*/
static std::list<AudioDevice*> GetOutputDeviceList();

/**
* Gets an audio player.
*
* Retrieves a pointer to an audio player suitable to load, play and stop audio.
*
* @ see Player
* @see AudioPlayer
*
* @return An audio player object.
*/
static Player* GetPlayer();

/**
* Gets an audio recorder from your audio system.
*
* @see AudioRecorder
* @return An audio recorder object
*/
static AudioRecorder* GetRecorder();

/**
* Gets a WaveAudioFile object from your audio system.
*
* @see AudioFile
* @see WaveAudioFile
* @return a WaveAudioFileObject
*/
static AudioFile* GetWaveFile();

};

}

#endif
