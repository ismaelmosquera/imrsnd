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

#ifndef ___MIDISONG_H___
#define ___MIDISONG_H___

#include <vector>

namespace IMR
{

class MIDITrack;

/**
* Class MIDISong.
*
* A MIDISong has a list of MIDI tracks.
* It keeps also a Division ( ticks per quarter note ) value.
*
* @see MIDITrack
*/
class MIDISong
{

typedef std::vector<MIDITrack*> MIDITrackList;

public:

/** Constructor without parameters */
MIDISong();

/** Destructor */
~MIDISong();

/**
* Adds a track to this song object.
*
* @param MIDITrack* A pointer to the added track
*
* @see MIDITrack
*/
void AddTrack(MIDITrack*);

/**
* Gets a track from this MIDISong object.
*
* @param int Index of the requested track in the internal track list
*
* @see MIDITrack
*
* @return The requested track
*/
MIDITrack* GetTrack(int) const;

/**
* Gets the number of traks in this MIDISong object.
*
* @return The number of tracks in the song
*/
int GetNumTracks() const;

/**
* Gets the division ( ticksperq ) for this MIDISong object.
*
* @return ticksperq
*/
unsigned short GetTicksPerQ() const;

/**
* Sets the division ( ticksperq ) to this MIDISong object.
*
* @param unsigned short TicksPerQ
*
*/
void SetTicksPerQ(unsigned short);

/**
* Clears this MIDISong object.
* That is, clears all of the MIDI tracks in the list.
*
*/
void Clear();

private:
MIDITrackList _tracks;
unsigned short _ticksPerQ;
};

}

#endif
