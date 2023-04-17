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

#ifndef ___AUDIODEVICE_H___
#define ___AUDIODEVICE_H___

#include <string>

namespace IMR
{

/**
* Class AudioDevice.
*
* This is a pure abstract class to encapsulate information about an AudioDevice.
*
* This class is inherited by the classes AudioInDevice and AudioOutDevice.
*
* @see AudioInDevice
* @see AudioOutDevice
*
*/
class AudioDevice
{

public:

/** Constructor */
AudioDevice() {}

/** virtual destructor */
virtual ~AudioDevice() {}

/**
* Pure virtual methods to get information from an audio device.
*
* @see AudioInDevice
* @see AudioOutDevice
*/

virtual int GetId() const = 0;
virtual int GetMid() const = 0;
virtual int GetPid() const = 0;
virtual unsigned short GetVersion() const = 0;
virtual const std::string& GetName() const = 0;
virtual unsigned int GetFormats() const = 0;
virtual int GetNumChannels() const = 0;
virtual unsigned int GetSupport() const = 0;

protected:
int _id;
int _mid;
int _pid;
unsigned short _version;
std::string _name;
unsigned int _formats;
int _numChannels;
unsigned int _support;
};

}

#endif
