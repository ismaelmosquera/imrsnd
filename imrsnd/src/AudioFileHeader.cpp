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

#include "AudioFileHeader.h"

namespace IMR
{

AudioFileHeader::AudioFileHeader()
{
_riffSize = 0;
_fmtSize = 0;
_formatType = 0;
_numChannels = 0;
_sampleRate = 0;
_byteRate = 0;
_blockAlign = 0;
_bitsPerSample = 0;
_dataSize = 0;
}

AudioFileHeader::~AudioFileHeader()
{
}

void AudioFileHeader::SetRiffSize(unsigned int value)
{
	_riffSize = value;
}

unsigned int AudioFileHeader::GetRiffSize() const
{
	return _riffSize;
}

void AudioFileHeader::SetFmtSize(unsigned int value)
{
	_fmtSize = value;
}

unsigned int AudioFileHeader::GetFmtSize() const
{
	return _fmtSize;
}

void AudioFileHeader::SetFormatType(unsigned short value)
{
	_formatType = value;
}

unsigned short AudioFileHeader::GetFormatType() const
{
	return _formatType;
}

void AudioFileHeader::SetNumChannels(unsigned short value)
{
	_numChannels = value;
}

unsigned short AudioFileHeader::GetNumChannels() const
{
	return _numChannels;
}

void AudioFileHeader::SetSampleRate(unsigned int value)
{
	_sampleRate = value;
}

unsigned int AudioFileHeader::GetSampleRate() const
{
	return _sampleRate;
}

void AudioFileHeader::SetByteRate(unsigned int value)
{
	_byteRate = value;
}

unsigned int AudioFileHeader::GetByteRate() const
{
	return _byteRate;
}

void AudioFileHeader::SetBlockAlign(unsigned short value)
{
	_blockAlign = value;
}

unsigned short AudioFileHeader::GetBlockAlign() const
{
	return _blockAlign;
}

void AudioFileHeader::SetBitsPerSample(unsigned short value)
{
	_bitsPerSample = value;
}

unsigned short AudioFileHeader::GetBitsPerSample() const
{
	return _bitsPerSample;
}

void AudioFileHeader::SetDataSize(unsigned int value)
{
	_dataSize = value;
}

unsigned int AudioFileHeader::GetDataSize() const
{
	return _dataSize;
}

AudioFileHeader& AudioFileHeader::operator=(const AudioFileHeader& header)
{
_riffSize = header.GetRiffSize();
_fmtSize = header.GetFmtSize();
_formatType = header.GetFormatType();
_numChannels = header.GetNumChannels();
_sampleRate = header.GetSampleRate();
_byteRate = header.GetByteRate();
_blockAlign = header.GetBlockAlign();
_bitsPerSample = header.GetBitsPerSample();
_dataSize = header.GetDataSize();
return *this;
}

}

// END
