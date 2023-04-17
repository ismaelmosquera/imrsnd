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

#ifndef ___MIDIOUTDEVICE_H___
#define ___MIDIOUTDEVICE_H___

#include <windows.h>
#include <mmsystem.h>

#include "MIDIDevice.h"

namespace IMR
{

/**
* Class MIDIOutDevice.
* This class encapsulates information for a MIDI output device.
*
* This class inherits from the MIDIDevice abstract class and implements its abstract methods.
* Actually, the objects constructed by this class are inmutable objects,
* that is, you can get information about the MIDI output device but you cannot modify it.
*
* @see MIDIDevice
*/
class MIDIOutDevice : public MIDIDevice
{

public:
/** constructor without parameters */
MIDIOutDevice();

/**
* Constructor.
*
* @param int id for this MIDI output device
* @param MIDIOUTCAPS structure with information about this MIDI output device
*
*/
MIDIOutDevice(int id, const MIDIOUTCAPS& mcaps);

/** Destructor */
~MIDIOutDevice();

/**
* Gets the ID of this MIDIOutDevice.
*
* @return ID
*/
int GetId() const;

/**
* Gets the manufacturer ID for this MIDIOutDevice.
*
* @return Manufacturer ID
*/
int GetMid() const;

/**
* Gets the product ID for this MIDIOutDevice.
*
* @return Product ID
*/
int GetPid() const;

/**
* Gets the version for this MIDIOutDevice.
*
* @return Version
*/
unsigned short GetVersion() const;

/**
* Gets the name of this MIDIOutDevice.
*
* @return Name of the MIDI output device
*/
const std::string& GetName() const;

/**
* Gets the support for this MIDIOutDevice.
*
* @return Support
*/
unsigned int GetSupport() const;

/**
* The following declared methods are specialized for this class.
* You must cast the object to access them.
*
*/

/**
* Gets the technology for this MIDIOutDevice.
*
* @return technology
*/
int GetTechnology() const;

/**
* Gets the voices for this MIDIOutDevice.
*
* @return voices
*/
int GetVoices() const;

/**
* Gets the notes for this MIDIOutDevice.
*
* @return notes
*/
int GetNotes() const;

/**
* Gets the channel mask for this MIDIOutDevice.
*
* @return channel mask
*/
int GetChannelMask() const;

private:
int _technology;
int _voices;
int _notes;
int _channelMask;

};

}

#endif
