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

#ifndef ___MIDISYSTEM_H___
#define ___MIDISYSTEM_H___

#include <list>

namespace IMR
{

class MIDIDevice;
class Player;
class MIDIFile;

/**
* Class MIDISystem.
*
* This class acts like a facade to get the most relevant objects for the IMR MIDI system.
* It has static methods to do the task.
*
* @see MIDIDevice
* @ see MIDIInDevice
* @see MIDIOutDevice
* @see Player
* @see MIDIPlayer
* @see MIDIFile
*/
class MIDISystem
{

public:

/**
* Gets a list containing all the MIDI input devices in your system.
*
* @return The list of MIDI input devices available in your system.
*/
static std::list<MIDIDevice*> GetInputDeviceList();

/**
* Gets a list with all the MIDI output devices available in your system
*
* @return The list of MIDI output devices available in your system
*/
static std::list<MIDIDevice*> GetOutputDeviceList();

/**
* Gets a MIDI player.
*
* Retrieves a pointer to a MIDI player suitable to load, play and stop MIDI.
*
* @ see Player
* @see MIDIPlayer
*
* @return A MIDI player object.
*/
static Player* GetPlayer();

/**
* Gets a MIDIFile object from your MIDI system.
*
* @see MIDIFile
* @return a MIDIFileObject
*/
static MIDIFile* GetMIDIFile();

};

}

#endif
