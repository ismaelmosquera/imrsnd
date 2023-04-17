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

#include <windows.h>
#include <mmsystem.h>

#include "MIDIInDevice.h"
#include "MIDIOutDevice.h"
#include "MIDIPlayer.h"
#include "MIDIFile.h"
#include "MIDISystem.h"

namespace IMR
{

std::list<MIDIDevice*> MIDISystem::GetInputDeviceList()
{
MIDIINCAPS mcaps;
int numDevs = midiInGetNumDevs();
std::list<MIDIDevice*> lst;
for(int i = 0; i < numDevs; i++)
{
if(!midiInGetDevCaps(i, &mcaps, sizeof(MIDIINCAPS)))
{
	lst.push_back(new MIDIInDevice(i, mcaps));
}
}
return lst;
}

std::list<MIDIDevice*> MIDISystem::GetOutputDeviceList()
{
MIDIOUTCAPS mcaps;
int numDevs = midiOutGetNumDevs();
std::list<MIDIDevice*> lst;
for(int i = 0; i < numDevs; i++)
{
if(!midiOutGetDevCaps(i, &mcaps, sizeof(MIDIOUTCAPS)))
{
	lst.push_back(new MIDIOutDevice(i, mcaps));
}
}
return lst;
}

Player* MIDISystem::GetPlayer()
{
return new MIDIPlayer();
}

MIDIFile* MIDISystem::GetMIDIFile()
{
return new MIDIFile();
}

}

// END
