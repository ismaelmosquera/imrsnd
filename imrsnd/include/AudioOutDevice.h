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

#ifndef ___AUDIOOUTPUTDEVICE_H___
#define ___AUDIOOUTPUTDEVICE_H___

#include <windows.h>
#include <mmsystem.h>
#include "AudioDevice.h"

namespace IMR
{

/**
* Class AudioOutDevice.
* This class encapsulates information for an audio output device.
*
* This class inherits from the AudioDevice abstract class and implements its abstract methods.
* Actually, the objects constructed by this class are inmutable objects,
* that is, you can get information about the audio output device but you cannot modify it.
*
* @see AudioDevice
*/
class AudioOutDevice : public AudioDevice
{

public:
/** constructor without parameters */
AudioOutDevice();

/**
* Constructor.
*
* @param int id for this audio output device
* @param WAVEOUTCAPS structure with information about this audio output device
*
*/
AudioOutDevice(int id, const WAVEOUTCAPS& wcaps);

/** destructor */
~AudioOutDevice();

/**
* Gets the ID of this AudioOutDevice.
*
* @return ID
*/
int GetId() const;

/**
* Gets the manufacturer ID for this AudioOutDevice.
*
* @return Manufacturer ID
*/
int GetMid() const;

/**
* Gets the product ID for this AudioOutDevice.
*
* @return Product ID
*/
int GetPid() const;

/**
* Gets the version for this AudioOutDevice.
*
* @return Version
*/
unsigned short GetVersion() const;

/**
* Gets the name of this AudioOutDevice.
*
* @return Name of the audio output device
*/
const std::string& GetName() const;

/**
* Gets the formats for this AudioOutDevice.
*
* @return Formats
*/
unsigned int GetFormats() const;

/**
* Gets the number of channels for this AudioOutDevice.
*
* @return Number of channels
*/
int GetNumChannels() const;

/**
* Gets the support for this AudioOutDevice.
*
* @return Support
*/
unsigned int GetSupport() const;

};

}

#endif
