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

#include "MIDIOutDevice.h"

namespace IMR
{

MIDIOutDevice::MIDIOutDevice()
{
_id = 0;
_mid = 0;
_pid = 0;
_version = 0;
_name = "";
_technology = 0;
_voices = 0;
_notes = 0;
_channelMask = 0;
_support = 0;
}

MIDIOutDevice::MIDIOutDevice(int id, const MIDIOUTCAPS& mcaps)
{
_id = id;
_mid = mcaps.wMid;
_pid = mcaps.wPid;
_version = mcaps.vDriverVersion;
_name = mcaps.szPname;
_technology = mcaps.wTechnology;
_voices = mcaps.wVoices;
_notes = mcaps.wNotes;
_channelMask = mcaps.wChannelMask;
_support = mcaps.dwSupport;
}

MIDIOutDevice::~MIDIOutDevice() {}

int MIDIOutDevice::GetId() const
{
return _id;
}

int MIDIOutDevice::GetMid() const
{
return _mid;
}

int MIDIOutDevice::GetPid() const
{
return _pid;
}

unsigned short MIDIOutDevice::GetVersion() const
{
return _version;
}

const std::string& MIDIOutDevice::GetName() const
{
return _name;
}

unsigned int MIDIOutDevice::GetSupport() const
{
return _support;
}

int MIDIOutDevice::GetTechnology() const
{
return _technology;
}

int MIDIOutDevice::GetVoices() const
{
return _voices;
}

int MIDIOutDevice::GetNotes() const
{
return _notes;
}

int MIDIOutDevice::GetChannelMask() const
{
return _channelMask;
}

}

// END
