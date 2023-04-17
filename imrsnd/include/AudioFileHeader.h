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

#ifndef ___AUDIOFILEHEADER_H___
#define ___AUDIOFILEHEADER_H___

namespace IMR
{

/**
* Class AudioFileHeader
*
* An audio file header encapsulates information about the audio data loaded from an audio file.
*
* @see Audio
*/
class AudioFileHeader
{

public:

/** constructor */
AudioFileHeader();

/** destructor */
~AudioFileHeader();

/**
* Sets the RIFF size for this AudioFileHeader.
*
* @param unsigned int The RIFF size.
*/
void SetRiffSize(unsigned int);

/**
* Gets the RIFF size from this AudioFileHeader.
*
* @return The RIFF size.
*/
unsigned int GetRiffSize() const;

/**
* Sets the FMT size for this AudioFileHeader.
*
* @param unsigned int The FMT size.
*
*/
void SetFmtSize(unsigned int);

/**
* Gets the FMT size from this AudioFileHeader.
*
* @return The FMT size.
*/
unsigned int GetFmtSize() const;

/**
* Sets the format for this AudioFileHeader.
*
* @param unsigned short Format type
*
*/
void SetFormatType(unsigned short);

/**
* Gets the format type from this AudioFileHeader.
*
* @return The format type
*/
unsigned short GetFormatType() const;

/**
* Sets the number of channels for this AudioFileHeader.
*
* @param unsigned short The number of channels
*
*/
void SetNumChannels(unsigned short);

/**
* Gets the number of channels from this AudioFileHeader.
*
* @return The number of channels
*/
unsigned short GetNumChannels() const;

/**
* Sets the sample rate for this AudioFileHeader.
*
* @param unsigned int Sample rate
*
*/
void SetSampleRate(unsigned int);

/**
* Gets the sample rate from this AudioFileHeader.
*
* @return Sample rate
*/
unsigned int GetSampleRate() const;

/**
* Sets the byte rate for this AudioFileHeader.
*
* @param unsigned int Byte rate
*
*/
void SetByteRate(unsigned int);

/**
* Gets the byte rate from this AudioFileHeader.
*
* @return Byte rate
*/
unsigned int GetByteRate() const;

/**
* Sets the block align for this AudioFileHeader.
*
* @param unsigned short Block align
*
*/
void SetBlockAlign(unsigned short);

/**
* Gets the block align from this AudioFileHeader.
*
* @return Block align
*/
unsigned short GetBlockAlign() const;

/**
* Sets the number of bits per sample for this AudioFileHeader.
*
* @param unsigned short Number of bits per sample
*
*/
void SetBitsPerSample(unsigned short);

/**
* Gets the number of bits per sample from this AudioFileHeader.
*
* @return Number of bits per sample
*/
unsigned short GetBitsPerSample() const;

/**
* Sets the data size for this AudioFileHeader.
*
* @param unsigned int Data size
*
*/
void SetDataSize(unsigned int);

/**
* Gets the data size from this AudioFileHeader.
*
* @return Data size
*/
unsigned int GetDataSize() const;

/**
* Overloaded asignment operator for AudioFileHeader objects.
*
* @param An AudioFileHeader object
*
* @return A copy of the AudioFileHeader passed as parameter
*/
AudioFileHeader& operator=(const AudioFileHeader&);

private:
unsigned int _riffSize;
unsigned int _fmtSize;
unsigned short _formatType;
unsigned short _numChannels;
unsigned int _sampleRate;
unsigned int _byteRate;
unsigned short _blockAlign;
unsigned short _bitsPerSample;
unsigned int _dataSize;

};

}

#endif
