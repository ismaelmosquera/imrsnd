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

#include "MIDIEvent.h"
#include "MIDIUtil.h"
#include "MIDIFile.h"
#include "MIDIPlayer.h"

namespace IMR
{

MIDIPlayer::MIDIPlayer()
{
	_division = 0;
	_hasMIDI = false;
	_isPlaying = false;
	_stopRequested = false;
}

MIDIPlayer::MIDIPlayer(const MIDISong& song)
{
MIDIPlayer();
_division = song.GetTicksPerQ();
_track = _track.MergeTracks(song);
_hasMIDI = true;
}

MIDIPlayer::~MIDIPlayer()
{
_track.Clear();
}

void MIDIPlayer::SetMIDI(const MIDISong& song)
{
_track.Clear();
_division = song.GetTicksPerQ();
_track = _track.MergeTracks(song);
_hasMIDI = true;
}

bool MIDIPlayer::Load(const char* filename)
{
	MIDISong s;
	MIDIFile smf;
	bool flag = smf.Load(s, filename);
	if(flag)
	{
		_division = s.GetTicksPerQ();
		_track.Clear();
		_track = _track.MergeTracks(s);
		_hasMIDI = true;
		}
		return flag;
}

int MIDIPlayer::Play()
{
if(_isPlaying) return 1;
if(!_hasMIDI) return 1;
return pthread_create(&_pt, NULL, LaunchThread, this);
}

void MIDIPlayer::Stop()
{
	_isPlaying = false;
_stopRequested = true;
}


void* MIDIPlayer::LaunchThread(void* ptr)
{
((MIDIPlayer*)ptr)->thread_code();
return NULL;
}

void MIDIPlayer::thread_code()
{
int flag;
unsigned long tempo = 500000; /* default */
unsigned long t;
unsigned long last_ticks;
unsigned long current_ticks;
unsigned long duration; /* duration in milliseconds */
HMIDIOUT dev; /* MIDI device interface for sending MIDI output */

_stopRequested = false;
/* Open the MIDI output port */
   flag = midiOutOpen(&dev, _devID, 0, 0, CALLBACK_NULL);
   if (flag != MMSYSERR_NOERROR) return; /* error openning the midi out device */
   _isPlaying = true;
MIDITrack::MIDITrackIterator it = _track.BeginTrack();
/* send all midi messages where ticks = 0 */
while((*it)->GetTicks() == 0)
{
if((*it)->IsTempoEvent())
{
tempo = MIDIUtil::GetTempoMu(*it);
}
else
{
midiOutShortMsg(dev, (*it)->GetMessage().Dispatch());
}
it++;
}
last_ticks = 0;
while(it != _track.EndTrack() && !_stopRequested)
{
	current_ticks = (*it)->GetTicks();
duration = MIDIUtil::Ticks2Milliseconds(current_ticks - last_ticks, _division, tempo);
t = timeGetTime();
while((timeGetTime() - t) < duration) ;
while((it != _track.EndTrack()) && ((*it)->GetTicks() == current_ticks && !_stopRequested))
{
if((*it)->IsTempoEvent())
{
tempo = MIDIUtil::GetTempoMu(*it);
}
else
{
midiOutShortMsg(dev, (*it)->GetMessage().Dispatch());
}
	it++;
}
last_ticks = current_ticks;
}
/* close all */
midiOutReset(dev);
midiOutClose(dev);
_isPlaying = false;
pthread_join(_pt, 0);
}

}

// END
