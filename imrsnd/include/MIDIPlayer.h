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

#ifndef ___MIDIPLAYER_H___
#define ___MIDIPLAYER_H___

#include <pthread.h>
#include "Player.h"
#include "MIDISong.h"
#include "MIDITrack.h"

namespace IMR
{

/**
* Class MIDIPlayer.
*
* This class implements a MIDI player for MsWindows low level API.
* It has functionality to set MIDI data, load, play and stop playing it.
* The player is launched as an independent thread by using posix threads ( pthread ) library.
* This class inherits from Player, for the method to set MIDI you must cast it.
*
* @see Player
* @see MIDISong
*/
class MIDIPlayer : public Player
{

public:

/** Constructor without parameters */
MIDIPlayer();

/**
* Constructor.
*
* @param const MIDISong& A MIDISong object.
*
* @see MIDISong
*/
MIDIPlayer(const MIDISong&);

/** Destructor */
~MIDIPlayer();

/**
* Sets a MIDI object to be played.
*
* Since this method is a specialized one, it must be cast if you instantiated just a Player.
*
* @param const MIDISong& A MIDISong object.
*
* @see MIDISong
*/
void SetMIDI(const MIDISong&);

/**
* Sets a MIDISong object from a file.
*
* @param const char* Filename
*
* @return true if success, false otherwise
*/
bool Load(const char*);

/**
* Stars playing MIDI.
*
* @return 0 if success, 1 otherwise
*/
int Play();

/**
* Stops playing.
*/
void Stop();

private:
MIDITrack _track;
int _division;
bool _hasMIDI;
bool _isPlaying;
bool _stopRequested;

pthread_t _pt;
static void* LaunchThread(void* ptr);
void thread_code();
};

}

#endif
