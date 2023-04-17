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

#include "Audio.h"

namespace IMR
{

Audio::Audio() : _data(0), _duration(0), _size(0)
{
}

Audio::Audio(const Audio& audio)
{
	*this = audio;
}

Audio::~Audio()
{
	if(_data) delete[] _data;
}

Audio& Audio::operator=(const Audio& audio)
{
this->SetHeader(audio.GetHeader());
	const char* data_ptr = audio.GetDataPtr();
		unsigned int data_size = _header.GetDataSize();
			for(unsigned int i = 0; i < data_size; i++) _data[i] = data_ptr[i];
			return *this;
}

void Audio::SetHeader(const AudioFileHeader& header)
{
	_header = header;
	if(_data) delete[] _data;
	unsigned int data_size = _header.GetDataSize();
	_data = new char[data_size];
	_duration = (unsigned int)(data_size / _header.GetByteRate());
	_size = data_size + 44;
}

const AudioFileHeader& Audio::GetHeader() const
{
	return _header;
}

void Audio::SetFrame(char* frame, int index, int frameSize)
{
int j = index;
for(int i = 0; i < frameSize; i++) _data[j++] = frame[i];
}

const char* Audio::GetDataPtr() const
{
return _data;
}

unsigned int Audio::GetDuration() const
{
	return _duration;
}

unsigned long Audio::GetSize() const
{
	return _size;
}

}

// END
