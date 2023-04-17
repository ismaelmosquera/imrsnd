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

#ifndef ___MIDIINDEVICE_H___
#define ___MIDIINDEVICE_H___

#include <windows.h>
#include <mmsystem.h>

#include "MIDIDevice.h"

namespace IMR
{

/**
* Class MIDIInDevice.
* This class encapsulates information for a MIDI input device.
*
* This class inherits from the MIDIDevice abstract class and implements its abstract methods.
* Actually, the objects constructed by this class are inmutable objects,
* that is, you can get information about the MIDI input device but you cannot modify it.
*
* @see MIDIDevice
*/
class MIDIInDevice : public MIDIDevice
{

public:

/** constructor without parameters */
MIDIInDevice();

/**
* Constructor.
*
* @param int id for this MIDI input device
* @param MIDIINCAPS structure with information about this MIDI input device
*
*/
MIDIInDevice(int id, const MIDIINCAPS& mcaps);

/** Destructor */
~MIDIInDevice();

/**
* Gets the ID of this MIDIInDevice.
*
* @return ID
*/
int GetId() const;

/**
* Gets the manufacturer ID for this MIDIInDevice.
*
* @return Manufacturer ID
*/
int GetMid() const;

/**
* Gets the product ID for this MIDIInDevice.
*
* @return Product ID
*/
int GetPid() const;

/**
* Gets the version for this MIDIInDevice.
*
* @return Version
*/
unsigned short GetVersion() const;

/**
* Gets the name of this MIDIInDevice.
*
* @return Name of the MIDI input device
*/
const std::string& GetName() const;

/**
* Gets the support for this MIDIInDevice.
*
* @return Support
*/
unsigned int GetSupport() const;

};

}

#endif
