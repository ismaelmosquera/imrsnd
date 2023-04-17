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

#include "AudioInDevice.h"

namespace IMR
{

AudioInDevice::AudioInDevice()
{
_id = 0;
_mid = 0;
_pid = 0;
_version = 0;
_name = "";
_formats = 0;
_numChannels = 0;
_support = 0;
}

AudioInDevice::AudioInDevice(int id, const WAVEINCAPS& wcaps)
{
_id = id;
_mid = wcaps.wMid;
_pid = wcaps.wPid;
_version = wcaps.vDriverVersion;
_name = wcaps.szPname;
_formats = wcaps.dwFormats;
_numChannels = wcaps.wChannels;
_support = 0;
}

AudioInDevice::~AudioInDevice(){}

int AudioInDevice::GetId() const
{
return _id;
}

int AudioInDevice::GetMid() const
{
	return _mid;
}

int AudioInDevice::GetPid() const
{
return _pid;
}

unsigned short AudioInDevice::GetVersion() const
{
	return _version;
}

const std::string& AudioInDevice::GetName() const
{
return _name;
}

unsigned int AudioInDevice::GetFormats() const
{
	return _formats;
}

int AudioInDevice::GetNumChannels() const
{
return _numChannels;
}

unsigned int AudioInDevice::GetSupport() const
{
	return _support;
}

}

// END
