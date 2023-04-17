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

#include "MIDITrack.h"
#include "MIDISong.h"

namespace IMR
{

MIDISong::MIDISong()
{
_ticksPerQ = 0;
}

MIDISong::~MIDISong()
{
	this->Clear();
}


void MIDISong::AddTrack(MIDITrack* track)
{
_tracks.push_back(track);
}

MIDITrack* MIDISong::GetTrack(int i) const
{
return _tracks[i];
}

int MIDISong::GetNumTracks() const
{
return _tracks.size();
}

unsigned short MIDISong::GetTicksPerQ() const
{
return _ticksPerQ;
}

void MIDISong::SetTicksPerQ(unsigned short q)
{
_ticksPerQ = q;
}

void MIDISong::Clear()
{
	int ntracks = _tracks.size();
	for(int i = 0; i < ntracks; i++) _tracks[i]->Clear();
	_tracks.clear();
}

}

// END
