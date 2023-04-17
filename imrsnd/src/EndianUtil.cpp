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

#include "EndianUtil.h"

namespace IMR
{

unsigned int EndianUtil::FlipInt(unsigned int value)
{
unsigned int retval = value >> 24;
retval |= (value >> 8) & 0x0000ff00;
retval |= (value << 8) & 0x00ff0000;
return retval | (value << 24);
}

unsigned short EndianUtil::FlipShort(unsigned short value)
{
unsigned short retval = value >> 8;
return retval | (value << 8);
}

}

// END
