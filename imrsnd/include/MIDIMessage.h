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

#ifndef ___MIDIMESSAGE_H___
#define ___MIDIMESSAGE_H___

namespace IMR
{

typedef unsigned char byte;

/**
* Class MIDIMessage.
*
* A MIDI message has 3 bytes as much.
* We define a union in this implementation composed by a byte data array
* and an unsigned long value.
* That is because we must launch the message to the MIDI output device as an unsigned long quantity.
* This class could be also named ChannelVoiceMessage
* because objects of this class are actually of that kind.
*
*/
class MIDIMessage
{

typedef union
{
unsigned long dispatch;
byte data[4];
}Msg;

public:

/** Constructor without parameters */
MIDIMessage()
{
msg.data[0] = msg.data[1] = msg.data[2] = msg.data[3] = 0x00;
}

/**
* Constructor.
*
* @param status Status byte
@param data1 Data1 byte
* @param data2 Data2 byte
*
*/
MIDIMessage(byte status, byte data1, byte data2)
{
msg.data[0] = status;
msg.data[1] = data1;
msg.data[2] = data2;
msg.data[3] = 0x00;
}

/** Destructor */
~MIDIMessage() {}

/**
* Overloaded [] operator.
*
* @param int i Index to access the data array; it should be in the range 0..2
*
* @return byte value for the index passed as parameter
*/
byte operator[](int i) const
{
return msg.data[i];
}

/**
* Dispatchs the message to the MIDI output device.
*
* @return 32 bit value for this message
*/
unsigned long Dispatch() const
{
return msg.dispatch;
}

private:
Msg msg;
};

}

#endif
