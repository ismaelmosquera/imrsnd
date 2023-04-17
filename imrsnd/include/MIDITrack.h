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

#ifndef ___MIDITRACK_H___
#define ___MIDITRACK_H___

#include <list>
#include "MIDISong.h"

namespace IMR
{

class MIDIEvent;

/**
* Class MIDITrack.
*
* A MIDI track is a list of MIDI events.
* It also can have a name.
* This class has methods to manage tracks properly.
* It has also a method to merge all the tracks in a MIDISong object into a single multichannel track.
*
* @see MIDIEvent
* @see MIDISong
*/
class MIDITrack
{

typedef std::list<MIDIEvent*> MIDIEventList;

public:

/** Constructor */
MIDITrack();

/** Destructor */
~MIDITrack();

/**
* Sets a name for this track.
*
* @param const char* Name
* @param int Length of the name
*
*/
void SetName(const unsigned char*, int);

/**
* Gets the name of this track.
*
* @return Name of this track.
*/
const char* GetName() const;

/**
* Adds a MIDI event to this track.
*
* @param MIDIEvent* A pointer to an event to add
*
* @see MIDIEvent
*/
void AddEvent(MIDIEvent*);

/**
* Merges all the tracks in a song to a single multichannel track.
*
* @param const MIDISong& A MIDISong object
*
* @see MIDISong
*
* @return The merged multichannel MIDITrack object
*/
MIDITrack& MergeTracks(const MIDISong&);

/**
* Clears this track object.
*/
void Clear();

/**
* MIDITrack iterator to traverse the track.
*/
typedef std::list<MIDIEvent*>::const_iterator MIDITrackIterator;
MIDITrackIterator BeginTrack()
{
return _track.begin();
}

MIDITrackIterator EndTrack()
{
return _track.end();
}


private:
MIDIEventList _track;
char* _name;
};

}

#endif
