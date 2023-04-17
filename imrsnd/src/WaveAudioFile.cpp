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

#include "FileUtil.h"
#include "EndianUtil.h"
#include "WaveAudioFile.h"

namespace IMR
{

WaveAudioFile::WaveAudioFile()
{
}

WaveAudioFile::~WaveAudioFile()
{
}

bool WaveAudioFile::Load(Audio& audio, const char* filename)
{
_fpread = fopen(filename, "rb");
if(!_fpread) return false;

if(!ReadHeader()) return false;
audio.SetHeader(_header);
unsigned int dataSize = _header.GetDataSize();
int frame_size = (int)_header.GetByteRate();
int bytes_read = 0;
unsigned int total_bytes_read = 0;
char* frame = new char[frame_size];
while(total_bytes_read < dataSize)
{
if((total_bytes_read+frame_size) > dataSize)
{
delete[] frame;
frame_size = dataSize - total_bytes_read;
frame = new char[frame_size];
}
bytes_read = fread(frame, 1, frame_size, _fpread);
audio.SetFrame(frame, total_bytes_read, frame_size);
total_bytes_read += bytes_read;
}
delete[] frame;
fclose(_fpread);
_fpread = 0;
return true;
}

 bool WaveAudioFile::Store(const Audio& audio, const char* filename)
 {
 _fpwrite = fopen(filename, "wb");
if(!_fpwrite) return false;

_header = audio.GetHeader();
WriteHeader();
unsigned int dataSize = _header.GetDataSize();
const char* data = audio.GetDataPtr();
int frame_size = (int)_header.GetByteRate();
int bytes_written = 0;
unsigned int total_bytes_written = 0;
char* frame = new char[frame_size];
while(total_bytes_written < dataSize)
{
	if((total_bytes_written + bytes_written) > dataSize)
	{
delete[] frame;
frame_size = dataSize - total_bytes_written;
frame = new char[frame_size];
	}
	int j = total_bytes_written;
	for(int i = 0; i < frame_size; i++) frame[i] = data[j++];
bytes_written = fwrite(frame, 1, frame_size, _fpwrite);
total_bytes_written += bytes_written;
}
delete[] frame;
fclose(_fpwrite);
_fpwrite = 0;
return true;
}

bool WaveAudioFile::ReadHeader()
{
if(!FileUtil::ReadChunk(_fpread, "RIFF")) return false;
unsigned int riffSize = EndianUtil::FlipInt(FileUtil::Read32bit(_fpread));
if(!FileUtil::ReadChunk(_fpread, "WAVE")) return false;
if(!FileUtil::ReadChunk(_fpread, "fmt ")) return false;
unsigned int fmtSize = EndianUtil::FlipInt(FileUtil::Read32bit(_fpread));
unsigned short formatType = EndianUtil::FlipShort(FileUtil::Read16bit(_fpread));
unsigned short numChannels = EndianUtil::FlipShort(FileUtil::Read16bit(_fpread));
unsigned int sampleRate = EndianUtil::FlipInt(FileUtil::Read32bit(_fpread));
unsigned int byteRate = EndianUtil::FlipInt(FileUtil::Read32bit(_fpread));
unsigned short blockAlign = EndianUtil::FlipShort(FileUtil::Read16bit(_fpread));
unsigned short bitsPerSample = EndianUtil::FlipShort(FileUtil::Read16bit(_fpread));
if(!FileUtil::ReadChunk(_fpread, "data")) return false;
unsigned int dataSize = EndianUtil::FlipInt(FileUtil::Read32bit(_fpread));

_header.SetRiffSize(riffSize);
_header.SetFmtSize(fmtSize);
_header.SetFormatType(formatType);
_header.SetNumChannels(numChannels);
_header.SetSampleRate(sampleRate);
_header.SetByteRate(byteRate);
_header.SetBlockAlign(blockAlign);
_header.SetBitsPerSample(bitsPerSample);
_header.SetDataSize(dataSize);
return true;
}

void WaveAudioFile::WriteHeader()
{
unsigned int riffSize = EndianUtil::FlipInt(_header.GetRiffSize());
unsigned int fmtSize = EndianUtil::FlipInt(_header.GetFmtSize());
unsigned short formatType = EndianUtil::FlipShort(_header.GetFormatType());
unsigned short numChannels = EndianUtil::FlipShort(_header.GetNumChannels());
unsigned int sampleRate = EndianUtil::FlipInt(_header.GetSampleRate());
unsigned int byteRate = EndianUtil::FlipInt(_header.GetByteRate());
unsigned short blockAlign = EndianUtil::FlipShort(_header.GetBlockAlign());
unsigned short bitsPerSample = EndianUtil::FlipShort(_header.GetBitsPerSample());
unsigned int dataSize = EndianUtil::FlipInt(_header.GetDataSize());

FileUtil::WriteChunk(_fpwrite, "RIFF");
FileUtil::Write32bit(riffSize, _fpwrite);
FileUtil::WriteChunk(_fpwrite, "WAVE");
FileUtil::WriteChunk(_fpwrite, "fmt ");
FileUtil::Write32bit(fmtSize, _fpwrite);
FileUtil::Write16bit(formatType, _fpwrite);
FileUtil::Write16bit(numChannels, _fpwrite);
FileUtil::Write32bit(sampleRate, _fpwrite);
FileUtil::Write32bit(byteRate, _fpwrite);
FileUtil::Write16bit(blockAlign, _fpwrite);
FileUtil::Write16bit(bitsPerSample, _fpwrite);
FileUtil::WriteChunk(_fpwrite, "data");
FileUtil::Write32bit(dataSize, _fpwrite);
}

}

// END
