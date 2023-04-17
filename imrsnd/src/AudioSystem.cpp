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

#include "AudioDevice.h"
#include "AudioInDevice.h"
#include "AudioOutDevice.h"
#include "Player.h"
#include "AudioPlayer.h"
#include "AudioRecorder.h"
#include "AudioFile.h"
#include "WaveAudioFile.h"
#include "AudioSystem.h"

namespace IMR
{

std::list<AudioDevice*> AudioSystem::GetInputDeviceList()
{
WAVEINCAPS wcaps;
int numdevs = waveInGetNumDevs();
std::list<AudioDevice*> lst;
for(int i = 0; i < numdevs; i++)
{
	if(!waveInGetDevCaps(i, &wcaps, sizeof(WAVEINCAPS)))
	{
		lst.push_back(new AudioInDevice(i, wcaps));
	}
}
return lst;
}

std::list<AudioDevice*> AudioSystem::GetOutputDeviceList()
{
WAVEOUTCAPS wcaps;
int numdevs = waveOutGetNumDevs();
std::list<AudioDevice*> lst;
for(int i = 0; i < numdevs; i++)
{
	if(!waveOutGetDevCaps(i, &wcaps, sizeof(WAVEOUTCAPS)))
	{
		lst.push_back(new AudioOutDevice(i, wcaps));
	}
}
return lst;
}

Player* AudioSystem::GetPlayer()
{
return new AudioPlayer();
}

AudioRecorder* AudioSystem::GetRecorder()
{
return new AudioRecorder();
}

AudioFile* AudioSystem::GetWaveFile()
{
return new WaveAudioFile();
}

}

// END
