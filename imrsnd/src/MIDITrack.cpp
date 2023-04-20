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

#include "MIDIEvent.h"
#include "MIDITrack.h"

namespace IMR
{

MIDITrack::MIDITrack()
{
_name = 0;
}

MIDITrack::~MIDITrack()
{
if(_name) delete _name;
this->Clear();
}

void MIDITrack::SetName(const unsigned char* ptr, int len)
{
if(_name) delete _name;
_name = new char[len+1];
for(int i = 0; i < len; i++) _name[i] = ptr[i];
_name[len] = '\0';
}

const char* MIDITrack::GetName() const
{
return _name;
}

void MIDITrack::AddEvent(MIDIEvent* ev)
{
_track.push_back(ev);
}

MIDITrack& MIDITrack::MergeTracks(const MIDISong& s)
{
if(!_track.empty()) _track.clear();
int ntracks = s.GetNumTracks();
for(int i = 0; i < ntracks; i++)
{
	MIDITrack* track = s.GetTrack(i);
	MIDITrack::MIDITrackIterator it = track->BeginTrack();
	for(; it != track->EndTrack(); it++)
	{
		if((*it)->IsShortEvent() || (*it)->IsTempoEvent())
		{
			if(_track.empty() || (*it)->GetTicks() > _track.back()->GetTicks())
			{
				_track.push_back(*it);
			}
			else if((*it)->GetTicks() < _track.front()->GetTicks())
			{
				_track.push_front(*it);
			}
			else
			{
				std::list<MIDIEvent*>::const_iterator aux = _track.begin();
while((*it)->GetTicks() > (*aux)->GetTicks()) aux++;
_track.insert(aux, *it);
			}
		}
	}
}
return *this;
}

void MIDITrack::Clear()
{
	_track.clear();
}

}

// END
