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

#include "MIDIInDevice.h"

namespace IMR
{

MIDIInDevice::MIDIInDevice()
{
_id = 0;
_mid = 0;
_pid = 0;
_version = 0;
_name = "";
_support = 0;
}

MIDIInDevice::MIDIInDevice(int id, const MIDIINCAPS& mcaps)
{
_id = id;
_mid = mcaps.wMid;
_pid = mcaps.wPid;
_version = mcaps.vDriverVersion;
_name = mcaps.szPname;
_support = mcaps.dwSupport;
}

MIDIInDevice::~MIDIInDevice() {}

int MIDIInDevice::GetId() const
{
return _id;
}

int MIDIInDevice::GetMid() const
{
return _mid;
}

int MIDIInDevice::GetPid() const
{
return _pid;
}

unsigned short MIDIInDevice::GetVersion() const
{
return _version;
}

const std::string& MIDIInDevice::GetName() const
{
return _name;
}

unsigned int MIDIInDevice::GetSupport() const
{
return _support;
}

}

// END
