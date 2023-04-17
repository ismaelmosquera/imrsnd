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

unsigned long BytesRead;
unsigned long BytesWritten;

namespace IMR
{

bool FileUtil::ReadChunk(FILE* fp, const char* str)
{
	for(int i = 0; i < 4; i++)
	{
		if(str[i] != ReadChar(fp)) return false;
	}
	return true;
}

unsigned char FileUtil::ReadChar(FILE* fpread)
{
	BytesRead++;
return fgetc(fpread);
}

unsigned int FileUtil::Read32bit(FILE* fpread)
{
unsigned int val;
val = ReadChar(fpread);
val <<= 8;
val |= ReadChar(fpread);
val <<= 8;
val |= ReadChar(fpread);
val <<= 8;
val |= ReadChar(fpread);
return val;
}

unsigned short FileUtil::Read16bit(FILE* fpread)
{
unsigned short val;
val = ReadChar(fpread);
val <<= 8;
val |= ReadChar(fpread);
return val;
}

unsigned int FileUtil::ReadVarLen(FILE* fpread)
{
unsigned int ret = 0;
unsigned char tmp;
tmp = ReadChar(fpread);
ret = tmp & 0x7f;
while(tmp & 0x80)
{
tmp = ReadChar(fpread);
ret <<= 7;
ret |= (tmp & 0x7f);
}
return ret;
}


void FileUtil::WriteChunk(FILE* fp, const char* str)
{
	for(int i = 0; i < 4; i++) WriteChar(str[i], fp);
}

void FileUtil::WriteChar(char c, FILE* fpwrite)
{
fputc(c, fpwrite);
BytesWritten++;
}

void FileUtil::Write32bit(unsigned int data, FILE* fpwrite)
{
WriteChar((unsigned)((data >> 24) & 0xff), fpwrite);
		WriteChar((unsigned)((data >> 16) & 0xff), fpwrite);
		WriteChar((unsigned)((data >> 8 ) & 0xff), fpwrite);
		WriteChar((unsigned)(data & 0xff), fpwrite);
}

void FileUtil::Write16bit(unsigned short data, FILE* fpwrite)
{
WriteChar((unsigned)((data & 0xff00) >> 8), fpwrite);
		WriteChar((unsigned)(data & 0xff), fpwrite);
	}

void FileUtil::WriteVarLen(register unsigned long value, FILE* fpwrite)
{
register unsigned long buffer;
		buffer = value & 0x7F;

		while( (value >>= 7) )
		{
			buffer <<= 8;
			buffer |= ((value & 0x7F) | 0x80);
		}

		while(1)
		{
			WriteChar(buffer, fpwrite);
			if (buffer & 0x80)
				buffer >>= 8;
			else
				break;
		}
}

}

// END
