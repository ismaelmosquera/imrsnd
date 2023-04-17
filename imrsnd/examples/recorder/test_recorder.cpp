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

#include <iostream>
#include <stdlib.h>

#include "AudioDevice.h"
#include "Player.h"
#include "AudioPlayer.h"
#include "AudioRecorder.h"
#include "AudioFile.h"
#include "AudioSystem.h"

void show_menu();
void ListAudioDevs(std::list<IMR::AudioDevice*>, const char*);

int main()
{
IMR::Player* player = IMR::AudioSystem::GetPlayer();
IMR::AudioRecorder* recorder = IMR::AudioSystem::GetRecorder();
IMR::AudioFile* file = IMR::AudioSystem::GetWaveFile();

char s[64];
	char opt[25];
	int option;
bool has_audio = false;
int dev_id = 0;
bool hasRecord = false;

std::list<IMR::AudioDevice*> devOutLst = IMR::AudioSystem::GetOutputDeviceList();
std::list<IMR::AudioDevice*> devInLst = IMR::AudioSystem::GetInputDeviceList();
if(devOutLst.size() < 1)
{
std::cout << "Audio out device not found in your system." << std::endl;
}
if(devInLst.size() < 1)
{
std::cout << "Audio In device not found in your system." << std::endl;
}
if(devOutLst.size() <1 && devInLst.size() < 1) return 1;

	show_menu();

	do
	{
std::cout << std::endl;
std::cout << "option: ";
std::cin >> opt;
option = atoi(opt);
if(option == 0) option = 13;
switch(option)
{
	case 1:
	show_menu();
	break;
	case 2:
	ListAudioDevs(devInLst, "In");
		std::cout << "Select ID: ";
		std::cin >> s;
		dev_id = atoi(s);
		if(dev_id >= 0 && dev_id < devInLst.size())
		{
			recorder->SetDeviceID(dev_id);
			std::cout << "DevID set to " << dev_id << std::endl;
		}
		else
		{
			std::cout << "Sorry, devID must be in the range (0 .. number of devices - 1)." << std::endl;
		}
		break;
	case 3:
ListAudioDevs(devOutLst, "Out");
std::cout << "Select ID: ";
std::cin >> s;
dev_id = atoi(s);
if(dev_id >= 0 && dev_id < devOutLst.size())
{
	player->SetDeviceID(dev_id);
	std::cout << "DevID set to " << dev_id << std::endl;
}
else
{
	std::cout << "Sorry, devID must be in the range (0 .. number of devices - 1)." << std::endl;
}
	break;
	case 4:
	player->Stop();
	if(recorder->Rec() == 0)
	{
	std::cout << "Recording Started..." << std::endl;
	}
	else
	{
		std::cout << "Sorry, your recorder is not configured yet." << std::endl;
	}
		break;
case 5:
recorder->Stop();
std::cout << "Recording Stopped..." << std::endl;
hasRecord = true;
	break;
case 6:
if(hasRecord)
		{
			((IMR::AudioPlayer*)player)->SetAudio(recorder->GetAudio());
			has_audio = true;
			std::cout << "Audio set successfully. Select option 7 to reproduce it." << std::endl;
		}
		else
		{
			std::cout << "Sorry, there is not audio recorded yet." << std::endl;
		}
		break;
case 7:
if(has_audio)
{
	if(player->Play() != 0)
	{
		std::cout << "Sorry, cannot play audio, or the player is already playing." << std::endl;
	}
}
else
{
	std::cout << "Sorry, no audio has been set yet." << std::endl;
}
	break;
	case 8:
	player->Stop();
	break;
	case 9:
	if(hasRecord)
	{
		std::cout << "filename: ";
		std::cin >> s;
		file->Store(recorder->GetAudio(), s);
		std::cout << s << " stored." << std::endl;
	}
	else
	{
		std::cout << "Sorry, there is not audio recorded to stored." << std::endl;
	}
	break;
	case 10:
	player->Stop();
	recorder->Stop();
	option = 0;
	break;
	default:
	std::cout << "Not available." << std::endl;
}
	}while(option != 0);

delete player;
delete recorder;
delete file;

devInLst.clear();
devOutLst.clear();

std::cout << std::endl;
std::cout << "bye." << std::endl;
return 0;
}

void show_menu()
{
std::cout << "1: Show Menu." << std::endl;
std::cout << "2: Select Audio In Device." << std::endl;
std::cout << "3: Select Audio Out Device." << std::endl;
std::cout << "4: Rec Audio." << std::endl;
std::cout << "5: Stop Recording." << std::endl;
std::cout << "6: Set Rec Audio to Play." << std::endl;
std::cout << "7: Play Audio." << std::endl;
std::cout << "8: Stop Playing." << std::endl;
std::cout << "9: Store Rec Audio." << std::endl;
std::cout << "10: Exit." << std::endl;
}

void ListAudioDevs(std::list<IMR::AudioDevice*> lst, const char* dev_type)
{
	std::cout << std::endl;
	std::cout << "Audio " << dev_type << " Devices in your System: " << std::endl;
	std::list<IMR::AudioDevice*>::iterator it = lst.begin();
	for(; it != lst.end(); it++)
	{
		std::cout << "Dev ID: " << (*it)->GetId() << " => " << (*it)->GetName() << std::endl;
	}
	std::cout << std::endl;
}


// END
