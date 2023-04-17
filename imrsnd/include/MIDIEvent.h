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

#ifndef ___MIDIEVENT_H___
#define ___MIDIEVENT_H___

#include "MIDIMessage.h"

namespace IMR
{

/**
* Class MIDIEvent.
*
* A MIDI event has a MIDI message an a timestamp expressed in ticks.
*
*/
class MIDIEvent
{

public:

/** constructor without parameters */
MIDIEvent()
{
	_ticks = 0;
	_isShort = true;
}

/**
* Constructor.
*
* @param const MIDIMessage& msg A MIDIMessage
* @param unsigned long ticks Timestamp in ticks
*
*/
MIDIEvent(const MIDIMessage& msg, unsigned long ticks) : _msg(msg), _ticks(ticks)
{
	_isShort = true;
}

/** Destructor */
~MIDIEvent()
{
}

/**
* Overloaded [] operator.
* @param int i Index
*
* @return The byte value for the MIDIMessage index passed as parameter
*/
byte operator[](int i) const
{
return _msg[i];
}

/**
* Gets the timestamp in ticks for this event.
*
* @return Timestamp in ticks
*/
unsigned long GetTicks() const
{
return _ticks;
}

/**
* Gets the MIDIMessage for this event.
*
* Note that the returned message cannot be modified.
*
* @return The MIDIMessage for this event
*/
const MIDIMessage& GetMessage() const
{
return _msg;
}

/**
* This method tell us if this event has just a MIDIMessage an a timestamp.
*
* @see MIDIMetaEvent
* @see MIDISysExEvent
*
* @return true if it is a short event and false otherwise
*/
bool IsShortEvent() const
{
return _isShort;
}

/**
* This method tell us if this event is a tempo event.
*
* @see MIDIMetaEvent
* @see MIDISysExEvent
*
* @return true if it is a tempo event and false otherwise
*/
bool IsTempoEvent() const
{
	return ((_msg[0] == 0xff) && (_msg[1] == 0x51)) ? true : false;
}


protected:
bool _isShort;

private:
MIDIMessage _msg;
unsigned long _ticks;
};


/**
* Class MIDIMetaEvent.
*
* A MIDIMetaEvent has a MIDIEvent plus some extra data.
* This class inherits from the MIDIEvent class
*
*/
class MIDIMetaEvent : public MIDIEvent
{

	public:

/**
* Constructor.
*
* @param msg MIDIMessage
* @param ticks Ticks
* @param int Size for the extra data buffer
*
*/
	MIDIMetaEvent(const MIDIMessage& msg, unsigned long ticks, int data_size) : MIDIEvent(msg, ticks)
	{
		_data = new byte[data_size];
		_isShort = false;
		_dataSize = data_size;
	}

/** Destructor */
	~MIDIMetaEvent()
	{
	if(_data) delete[] _data;
	}

	byte* _data;
	int _dataSize;
};

/**
* Class MIDISysExEvent.
*
* A MIDISysExEvent has a MIDIEvent plus some extra data.
* This class inherits from the MIDIEvent class
*
*/
class MIDISysExEvent : public MIDIEvent
{

	public:

/**
* Constructor.
*
* @param msg MIDIMessage
* @param ticks Ticks
* @param int Size for the extra data buffer
*
*/
	MIDISysExEvent(const MIDIMessage& msg, unsigned long ticks, int data_size) : MIDIEvent(msg, ticks)
	{
		_data = new byte[data_size];
		_isShort = false;
		_dataSize = data_size;
	}

/** Destructor */
	~MIDISysExEvent()
	{
	if(_data) delete[] _data;
	}

	byte* _data;
	int _dataSize;
};

}

#endif
