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

#ifndef ___WAVEAUDIOFILE_H___
#define ___WAVEAUDIOFILE_H___

#include "AudioFile.h"

namespace IMR
{

/**
* Class WaveAudioFile.
*
* this class implements functionality to load and store wave audio files.
*
* This class inherits from AudioFile.
*
* @see AudioFile
*/
class WaveAudioFile : public AudioFile
{

public:

/** Constructor */
WaveAudioFile();
/** Destructor */
~WaveAudioFile();

/**
* Loads a wave audio file.
*
* @param Audio& An Audio object to store the information loaded from a wave audio file
* @param const char* Filename
*
* @return true if success, false otherwise
*/
bool Load(Audio&, const char*);

/**
* Stores a wave audio file.
*
* @param const Audio& audio information to be stored
* @param const char* Filename
*
* @return true if success, false otherwise
*/
bool Store(const Audio&, const char*);

protected:
bool ReadHeader();
void WriteHeader();
};

}

#endif
