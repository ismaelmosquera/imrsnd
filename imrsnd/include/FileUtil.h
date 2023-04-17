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

#ifndef ___FILEUTIL_H___
#define ___FILEUTIL_H___

#include <stdio.h>

namespace IMR
{

/**
* Class FileUtil.
*
* This class is used to read/write chunks of 16/32 bits values to and from a file.
* The functionality from this class is useful to read/write audio file headers and MIDI files.
*
* @see AudioFileHeader
* @see AudioFile
* @see MIDIFile
*/
class FileUtil
{

	public:

/**
* Reads a chunk from a file.
*
* @param FILE* pointer to a file
* @param const char* Chunk to read
*
* @return true if the chunk is ok, false otherwise
*/
static bool ReadChunk(FILE*, const char*);

/**
* Reads a char from a file.
*
* @param FILE* pointer to a file
*
* @return read byte
*/
static unsigned char ReadChar(FILE*);

/**
* Read a 32 bit value from a file.
*
* @param FILE* pointer to a file
*
* @return a 32 bit value read from a file
*/
static unsigned int Read32bit(FILE*);

/**
* Read a 16 bit value from a file.
*
* @param FILE* pointer to a file
*
* @return a 16 bit value read from a file
*/
static unsigned short Read16bit(FILE*);

/**
* Read a VarLen value from a file.
*
* This static method is use to read variable length quantities from a SMF ( Standard MIDI File ).
*
* @param FILE* pointer to a file
*
* @return a variable length quantity read from a file
*/
static unsigned int ReadVarLen(FILE*);

/**
* Write a chunk to a file.
*
* This static method is used to write chunks from an Audio or MIDI file.
*
* @param FILE* a pointer to a file
* @param const char* an audio or MIDI chunk
*
*/
static void WriteChunk(FILE*, const char*);

/**
* Write a char to a file.
*
* @param char Character to write
* @param FILE* a pointer to a file
*
*/
static void WriteChar(char, FILE*);

/**
* Write a 32 bit value to a file.
*
* @param unsigned int Value to write
* @param FILE* a pointer to a file
*
*/
static void Write32bit(unsigned int, FILE*);

/**
* Write a 16 bit value to a file.
*
* @param unsigned short Value to write
* @param FILE* a pointer to a file
*
*/
static void Write16bit(unsigned short, FILE*);

/**
* Write a variable length quantity to a file.
*
* This static method is used to write variable length quantities to a SMF ( Standard MIDI File ).
*
* @param unsigned long Value to write
* @param FILE* pointer to a file
*
*/
static void WriteVarLen(register unsigned long, FILE*);

};

}

#endif
