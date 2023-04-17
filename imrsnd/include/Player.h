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

#ifndef ___PLAYER_H___
#define ___PLAYER_H___

namespace IMR
{

/**
* Class Player.
*
* Player abstract class.
* This class acts like an interface from any player can be subclassed.
* It has an already implemented method to set the concrete device ID for a player.
* The virtual methods must be implemented by the subclasses inherited by this class.
*
* @see AudioPlayer
* @ see MIDIPlayer
*/
class Player
{

public:

/** constructor */
Player() : _devID(0) {}

/** virtual destructor */
virtual ~Player() {}

/**
* Sets the device id for this player.
*
* @param int id  The device ID
*
*/
void SetDeviceID(int id)
{
_devID = id;
}

/**
* These methods must be implemented by subclasses inherited from this one.
*/
virtual bool Load(const char*) = 0;
virtual int Play() = 0;
virtual void Stop() = 0;

protected:
int _devID;
};

}

#endif
