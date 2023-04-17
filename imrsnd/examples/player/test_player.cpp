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
#include <string.h>

#include "AudioDevice.h"
#include "MIDIDevice.h"
#include "Player.h"
#include "AudioSystem.h"
#include "MIDISystem.h"

void show_menu();
void ListAudioDevs(std::list<IMR::AudioDevice*>, const char*);
void ListMIDIOutDevs(std::list<IMR::MIDIDevice*> lst);
int get_player_type(const char*);

int main()
{
	IMR::Player* player = 0;
	IMR::Player* audio_player = IMR::AudioSystem::GetPlayer();
IMR::Player* midi_player = IMR::MIDISystem::GetPlayer();

char s[64];
	char opt[25];
	int option;
int player_t = -1;
bool has_file = false;
int dev_id = 0;

std::list<IMR::AudioDevice*> audioOutDevLst = IMR::AudioSystem::GetOutputDeviceList();
std::list<IMR::MIDIDevice*> midiOutDevLst = IMR::MIDISystem::GetOutputDeviceList();

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
ListAudioDevs(audioOutDevLst, "Out");
std::cout << "Select ID: ";
std::cin >> s;
dev_id = atoi(s);
if(dev_id >= 0 && dev_id < audioOutDevLst.size())
{
	player = audio_player;
	player->SetDeviceID(dev_id);
	std::cout << "DevID set to " << dev_id << std::endl;
}
else
{
	std::cout << "Sorry, devID must be in the range (0 .. number of devices - 1)." << std::endl;
}
	break;
	case 3:
	ListMIDIOutDevs(midiOutDevLst);
	std::cout << "Select ID: ";
	std::cin >> s;
	dev_id = atoi(s);
	if(dev_id >= 0 && dev_id < midiOutDevLst.size())
	{
		player = midi_player;
		player->SetDeviceID(dev_id);
		std::cout << "DevID set to " << dev_id << std::endl;
	}
	else
	{
		std::cout << "Sorry, devID must be in the range (0 .. number of devices - 1)." << std::endl;
	}
	break;
	case 4:
	if(has_file)
	{
player->Stop();
}
std::cout << "filename: ";
std::cin >> s;
player_t = get_player_type(s);
switch(player_t)
{
	case 0:
	player = audio_player;
	break;
	case 1:
	player = midi_player;
	break;
	default:
	std::cout << std::endl;
	std::cout << "Sorry, file format not supported." << std::endl;
}
if(player_t != -1)
{
if(player->Load(s))
{
	has_file = true;
	std::cout << std::endl;
	std::cout << "File loaded successfully." << std::endl;
}
else
{
	std::cout << std::endl;
	std::cout << "Sorry, cannot load file." << std::endl;
}
}
	break;
	case 5:
if(has_file)
{
	if(player->Play() != 0)
	{
		std::cout << "Sorry, cannot play file, or the player is already playing." << std::endl;
	}
}
else
{
	std::cout << "Sorry, no file has been loaded yet." << std::endl;
}
	break;
	case 6:
	if(has_file)
	{
	player->Stop();
}
	break;
	case 7:
	if(has_file)
	{
	player->Stop();
}
	option = 0;
	break;
	default:
	std::cout << "Not available." << std::endl;
}
	}while(option != 0);

if(audio_player) delete audio_player;
if(midi_player) delete midi_player;

audioOutDevLst.clear();
midiOutDevLst.clear();

std::cout << std::endl;
std::cout << "bye." << std::endl;
return 0;
}

void show_menu()
{
std::cout << "1: Show Menu." << std::endl;
std::cout << "2: Select Audio Out Device." << std::endl;
std::cout << "3: Select MIDI Out Device." << std::endl;
std::cout << "4: Load file." << std::endl;
std::cout << "5: Play." << std::endl;
std::cout << "6: Stop Playing." << std::endl;
std::cout << "7: Exit." << std::endl;
}

void ListMIDIOutDevs(std::list<IMR::MIDIDevice*> lst)
{
std::cout << std::endl;
	std::cout << "MIDI out devices in your system: " << std::endl;
	std::list<IMR::MIDIDevice*>::const_iterator it = lst.begin();
	for(; it != lst.end(); it++)
	{
		std::cout << "Dev ID: " << (*it)->GetId() << " => " << (*it)->GetName() << std::endl;
	}
	std::cout << std::endl;
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

int get_player_type(const char* filename)
{
int i = strlen(filename) - 3;
char ext[3];
ext[0] = filename[i];
ext[1] = filename[i+1];
ext[2] = filename[i+2];
if(ext[0]=='w' && ext[1]=='a' && ext[2]=='v') return 0;
if(ext[0]=='m' && ext[1]=='i' && ext[2]=='d') return 1;
return -1;
}


// END
