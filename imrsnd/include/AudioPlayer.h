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

#ifndef ___AUDIOPLAYER_H___
#define ___AUDIOPLAYER_H___

#include <pthread.h>
#include "Player.h"
#include "Audio.h"

namespace IMR
{

/**
* Class Audio Player.
*
* This class implements an audio player for MsWindows low level API.
* It has functionality to set audio data, load, play and stop playing it.
* The player is launched as an independent thread by using posix threads ( pthread ) library.
* This class inherits from Player, for the method to set audio you must cast it.
*/
class AudioPlayer : public Player
{

public:
/** constructor */
AudioPlayer();

/**
* Constructor.
*
* @param const Audio& An Audio object.
*
* @see Audio
*/
AudioPlayer(const Audio&);

/** Destructor */
~AudioPlayer();

/**
* Sets an Audio object to be played.
*
* Since this method is a specialized one, it must be cast if you instantiated just a Player.
*
* @param const Audio& An Audio object.
*
* @see Audio
*/
void SetAudio(const Audio&);

/**
* Sets an Audio object from a file.
*
* @param const char* Filename
*
* @return true if success, false otherwise
*/
bool Load(const char*);

/**
* Stars playing audio.
*
* @return 0 if success, 1 otherwise
*/
int Play();

/**
* Stops playing.
*/
void Stop();

private:
bool _hasAudio;
bool _isPlaying;

pthread_t _pt;
static void* LaunchThread(void* ptr);
void thread_code();
};

}

#endif
