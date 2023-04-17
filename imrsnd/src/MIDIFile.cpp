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

#include <stdio.h>
#include "FileUtil.h"
#include "MIDIEvent.h"
#include "MIDITrack.h"
#include "MIDIFile.h"

extern unsigned long BytesRead;
extern unsigned long BytesWritten;

namespace IMR
{

static int bytes_per_msg[7] = { 3,3,3,3,2,3,3 };

MIDIFile::MIDIFile()
{
}

MIDIFile::~MIDIFile()
{
}

bool MIDIFile::Load(MIDISong& song, const char* filename)
{
	song.Clear();
int type;
FILE* fpread = fopen(filename, "rb");
if(!fpread) return false;
if(!FileUtil::ReadChunk(fpread, "MThd"))
{
	fclose(fpread);
	return false;
}
unsigned int length;
unsigned short format;
unsigned short ntracks;

length = FileUtil::Read32bit(fpread);
if(length != 6)
{
	fclose(fpread);
	return false;
}
format = FileUtil::Read16bit(fpread);
if(format != 0 && format != 1)
{
	fclose(fpread);
	return false;
}
ntracks = FileUtil::Read16bit(fpread);
song.SetTicksPerQ((int)FileUtil::Read16bit(fpread));
for(int i = 0; i < ntracks; i++)
{
if(!FileUtil::ReadChunk(fpread, "MTrk"))
{
	fclose(fpread);
	return false;
}
unsigned int track_len = FileUtil::Read32bit(fpread);
byte runningStatus = 0;
unsigned long t = 0;
MIDITrack* track = new MIDITrack();

BytesRead = 0;
while(BytesRead != track_len)
{
unsigned int dt = FileUtil::ReadVarLen(fpread);
t += dt;
byte b = FileUtil::ReadChar(fpread);
if(b & 0x80)
{
	type = ((b>>4)&0x07);
if(type == 7)
{
if(b == 0xff)
{
byte meta_type = FileUtil::ReadChar(fpread);
length = FileUtil::ReadVarLen(fpread);
if(meta_type != 0x2f)
{
MIDIMetaEvent* ev = new MIDIMetaEvent(MIDIMessage(b, meta_type, 0), t, length);
for(int i = 0; i < length; i++) ev->_data[i] = FileUtil::ReadChar(fpread);
track->AddEvent(ev);
if(meta_type == 3)
{
	track->SetName(ev->_data, length);
}
}
}
else if(b == 0xf0 || b == 0xf7)
{
	length = FileUtil::ReadVarLen(fpread);
	MIDISysExEvent* sysev = new MIDISysExEvent(MIDIMessage(b, 0, 0), t, length+1);
for(int i = 0; i < length; i++) sysev->_data[i] = FileUtil::ReadChar(fpread);
track->AddEvent(sysev);
if(sysev->_data[length] != 0xf7)
{
	fclose(fpread);
	return false;
}
}
else
{
fclose(fpread);
return false;
}
runningStatus = 0;
}
else
{
	if(bytes_per_msg[type ]== 2)
	{
byte b1 = FileUtil::ReadChar(fpread);
track->AddEvent(new MIDIEvent(MIDIMessage(b, b1, 0), t));
	}
else
{
	byte b1 = FileUtil::ReadChar(fpread);
	byte b2 = FileUtil::ReadChar(fpread);
	track->AddEvent(new MIDIEvent(MIDIMessage(b, b1, b2), t));
}
runningStatus = b;
}
	}
else
{
	type = ((runningStatus >> 4) & 0x07);
if(bytes_per_msg[type] == 2)
{
	track->AddEvent(new MIDIEvent(MIDIMessage(runningStatus, b, 0), t));
}
else
{
	byte b2 = FileUtil::ReadChar(fpread);
	track->AddEvent(new MIDIEvent(MIDIMessage(runningStatus, b, b2), t));
}
}
}
song.AddTrack(track);
}
fclose(fpread);
return true;
}

bool MIDIFile::Store(const MIDISong& song, const char* filename)
{
	int type;
FILE* fpwrite = fopen(filename, "wb");
if(!fpwrite) return false;
FileUtil::WriteChunk(fpwrite, "MThd");
FileUtil::Write32bit(6, fpwrite);
int ntracks = song.GetNumTracks();
if(!ntracks)
{
	fclose(fpwrite);
	return false;
}
unsigned short format = (ntracks > 1) ? 1 : 0;
FileUtil::Write16bit(format, fpwrite);
FileUtil::Write16bit((unsigned short)ntracks, fpwrite);
FileUtil::Write16bit((unsigned short)song.GetTicksPerQ(), fpwrite);

long offset, endt;
unsigned long t0, t1;
for(int i = 0; i < ntracks; i++)
{
	FileUtil::WriteChunk(fpwrite, "MTrk");
	offset = ftell(fpwrite);
	FileUtil::Write32bit(0, fpwrite);
	BytesWritten = 0;
	t0 = t1 = 0;
	MIDITrack* track = song.GetTrack(i);
	MIDITrack::MIDITrackIterator it = track->BeginTrack();
	for(; it != track->EndTrack(); it++)
	{
const MIDIEvent& ev = **it;
t1 = ev.GetTicks();
type = ((ev[0] >> 4) & 0x07);
if(type == 7)
{
if(ev[0] == 0xff)
{
	FileUtil::WriteVarLen(t1-t0, fpwrite);
	for(int i = 0; i < 2; i++) FileUtil::WriteChar(ev[i], fpwrite);
	MIDIMetaEvent* e = (MIDIMetaEvent*)*it;
	FileUtil::WriteVarLen(e->_dataSize, fpwrite);
	for(int i = 0; i < e->_dataSize; i++) FileUtil::WriteChar(e->_data[i], fpwrite);
}
else if(ev[0] == 0xf0 || ev[0] == 0xf7)
{
	FileUtil::WriteVarLen(t1-t0, fpwrite);
	FileUtil::WriteChar(ev[0], fpwrite);
	MIDISysExEvent* e = (MIDISysExEvent*)*it;
	FileUtil::WriteVarLen(e->_dataSize, fpwrite);
	for(int i = 0; i < e->_dataSize; i++) FileUtil::WriteChar(e->_data[i], fpwrite);
}
}
else
{
	FileUtil::WriteVarLen(t1-t0, fpwrite);
	int msglen = bytes_per_msg[type];
	for(int i = 0; i < msglen; i++)
	{
FileUtil::WriteChar(ev[i], fpwrite);
	}
}
t0 = t1;
	}
	// Write end of track
	FileUtil::WriteChar(0, fpwrite);
	FileUtil::WriteChar(0xff, fpwrite);
	FileUtil::WriteChar(0x2f, fpwrite);
	FileUtil::WriteChar(0, fpwrite);
	endt = ftell(fpwrite);
	fseek(fpwrite, offset, 0);
	// Write track length
	FileUtil::Write32bit(BytesWritten, fpwrite);
	// retrieve position
	fseek(fpwrite, endt, 0);
}
fclose(fpwrite);
return true;
}

}

// END
