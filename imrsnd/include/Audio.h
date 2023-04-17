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

#ifndef ___AUDIO_H___
#define ___AUDIO_H___

#include "AudioFileHeader.h"

namespace IMR
{

/**
* Class Audio.
*
* An Audio object encapsulates an AudioFileHeader
* and a byte data buffer.

* In addition, it has methods to retrieve its duration and so on.
*
* @see AudioFileHeader
*/
class Audio
{

public:
/**
* Constructors.
*
*/

/**
* Constructor without parameters.
*
*/
Audio();

/**
* Copy constructor.
*
* @param const Audio& An Audio object.
*
*/
Audio(const Audio&);

/**
* Destructor.
*
*/
~Audio();

/**
* Overloaded asignment operator
*
* @param const Audio& An Audio object to be asign.
*
* @return A copy of the Audio object passed as parameter.
*
*/
Audio& operator=(const Audio&);

/**
* Sets an AudioFileHeader to this Audio object.
*
* An AudioFileHeader object encapsulates information about the audio data.
* For example: sample rate, number of channels, etc.
*
* @param const AudioFileHeader& An AudioFileHeader object.
*
* @see AudioFileHeader
*
*/
void SetHeader(const AudioFileHeader&);

/**
* Gets the AudioFileHeader for this Audio object.
*
* @return The AudioFileHeader for this Audio object.
* @see AudioFileHeader
*
*/
const AudioFileHeader& GetHeader() const;

/**
* Sets a frame to the byte data buffer in this Audio object.
*
* @param char* data
* @param int first index in the data buffer to put the data frame
* @param int length of the data frame to be added
*
*/
void SetFrame(char*, int, int);

/**
* Gets a const data ptr from this Audio object.
*
* The data ptr is actually the byte data buffer, but it cannot be modified.
*
* @return The const byte data ptr buffer of this Audio object.
*
*/
const char* GetDataPtr() const;

/**
* Gets the duration in seconds of this Audio object.
*
* @return The duration in seconds for this Audio object.
*
*/
unsigned int GetDuration() const;

/**
* Gets the size in bytes for this Audio object.
*
* The returned value also adds the size of the AudioFileHeader.
* The information for only the audio data size is contained in the AudioFileHeader.
*
* @return Size of the Audio object, include the header ( size of the entire file )
* @see AudioFileHeader
*
*/
unsigned long GetSize() const;

private:
unsigned long _size; // in bytes
unsigned int _duration; // seconds
char* _data;
AudioFileHeader _header;
};

}

#endif
