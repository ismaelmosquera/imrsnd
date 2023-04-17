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

#ifndef ___MIDIFILE_H___
#define ___MIDIFILE_H___

#include "MIDISong.h"

namespace IMR
{

/**
* Class MIDIFile.
*
* This class has methods to load an store SMF ( Standard MIDI File ).
* The information is stored in a MIDISong object.
*
* @see MIDISong
*/
class MIDIFile
{

public:

/** constructor */
MIDIFile();

/** destructor */
~MIDIFile();

/**
* This method loads a MIDI file and stores its information in a MIDISong object.
*
* @param const MIDISong& A MIDISong object to store the information extracted from a MIDI file
* @param const char* Filename
*
* @see MIDISong
*
* @return true if success or false otherwise
*/
bool Load(MIDISong&, const char*);

/**
* This method stores the information in a MIDISong object to a MIDI file.
*
* @param const MIDISong& A MIDISong object with proper information
* @param const char* Filename
*
* @see MIDISong
*
* @return true if success or false otherwise
*/
bool Store(const MIDISong&, const char*);

};

}

#endif
