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

#ifndef ___MIDIUTIL_H___
#define ___MIDIUTIL_H___

namespace IMR
{

class MIDIEvent;

/**
* Class MIDIUtil.
*
* This class implements static methods to get the tempo from a MIDIEvent
* and to convert ticks to milliseconds.
*
* @see MIDIEvent
* @see MIDISong
*/
class MIDIUtil
{

public:

/**
* Gets the tempo in microseconds.
*
* @param const MIDIEvent* A MIDI tempo event.
*
* @see MIDIEvent
*
* @return Tempo in microseconds
*/
static unsigned long GetTempoMu(const MIDIEvent*);

/**
* Converts ticks to milliseconds.
*
* @param unsigned long Ticks
* @param int Division ( ticks per quarter note )
* @param unsigned long Tempo in microseconds
*
* @see MIDIFile
* @see MIDIEvent
* @see MIDISong
*
* @return Duration in milliseconds
*/
static unsigned long Ticks2Milliseconds(unsigned long, int, unsigned long);

};

}

#endif
