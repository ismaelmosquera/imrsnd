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

#ifndef ___ENDIANUTIL_H___
#define ___ENDIANUTIL_H___

namespace IMR
{

/**
* Class EndianUtil.
*
* This class is used to manage Endian conversions ( Big Endian and Little Endian )
* Mainly to read an write audio file headers.
*
* @see AudioFileHeader
*/
class EndianUtil
{

public:

/**
* Flips the bits for a 32 bit value.
*
* @param unsigned int Value to be convert
*
* @return converted value
*/
static unsigned int FlipInt(unsigned int);

/**
* Flips the bits for a 16 bits value.
*
* @param unsigned short Value to convert
*
* @return Converted value
*/
static unsigned short FlipShort(unsigned short);

};

}

#endif
