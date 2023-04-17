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

#ifndef ___AUDIOFILE_H___
#define ___AUDIOFILE_H___

#include <stdio.h>
#include "Audio.h"
#include "AudioFileHeader.h"

namespace IMR
{

/**
* Class AudioFile.
*
* This is an abstract class which acts as an interface to load and store audio files.
*
* Concrete audio file formats must inherit from this class and implement its pure virtual methods.
*
* @see WaveAudioFile
*/
class AudioFile
{

public:

/** constructor */
AudioFile() : _fpread(0), _fpwrite(0)
{}

/** virtual destructor */
virtual ~AudioFile()
{
	if(_fpread) fclose(_fpread);
	if(_fpwrite) fclose(_fpwrite);
	}

/**
* Virtual methods to be implemented for the concrete subclasses.
*
*/

virtual bool Load(Audio&, const char*) = 0;
virtual bool Store(const Audio&, const char*) = 0;

protected:
FILE* _fpread;
FILE* _fpwrite;
AudioFileHeader _header;

virtual bool ReadHeader() = 0;
virtual void WriteHeader() = 0;

};

}

#endif
