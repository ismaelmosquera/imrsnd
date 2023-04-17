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

#ifndef ___AUDIOINPUTDEVICE_H___
#define ___AUDIOINPUTDEVICE_H___

#include <windows.h>
#include <mmsystem.h>
#include "AudioDevice.h"

namespace IMR
{

/**
* Class AudioInDevice.
* This class encapsulates information for an audio input device.
*
* This class inherits from the AudioDevice abstract class and implements its abstract methods.
* Actually, the objects constructed by this class are inmutable objects,
* that is, you can get information about the audio input device but you cannot modify it.
*
* @see AudioDevice
*/
class AudioInDevice : public AudioDevice
{

public:

/** constructor without parameters */
AudioInDevice();

/**
* Constructor.
*
* @param int id for this audio input device
* @param WAVEINCAPS structure with information about this audio input device
*
*/
AudioInDevice(int id, const WAVEINCAPS& wcaps);

/** destructor */
~AudioInDevice();

/**
* Gets the ID of this AudioInDevice.
*
* @return ID
*/
int GetId() const;

/**
* Gets the manufacturer ID for this AudioInDevice.
*
* @return Manufacturer ID
*/
int GetMid() const;

/**
* Gets the product ID for this AudioInDevice.
*
* @return Product ID
*/
int GetPid() const;

/**
* Gets the version for this AudioInDevice.
*
* @return Version
*/
unsigned short GetVersion() const;

/**
* Gets the name of this AudioInDevice.
*
* @return Name of the audio input device
*/
const std::string& GetName() const;

/**
* Gets the formats for this AudioInDevice.
*
* @return Formats
*/
unsigned int GetFormats() const;

/**
* Gets the number of channels for this AudioInDevice.
*
* @return Number of channels
*/
int GetNumChannels() const;

/**
* Gets the support for this AudioInDevice.
*
* @return Support
*/
unsigned int GetSupport() const;

};

}

#endif
