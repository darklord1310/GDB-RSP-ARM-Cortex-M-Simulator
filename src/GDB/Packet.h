/*  
    GDB RSP and ARM Simulator

    Copyright (C) 2015 Wong Yan Yin, <jet_wong@hotmail.com>,
    Jackson Teh Ka Sing, <jackson_dmc69@hotmail.com>

    This file is part of GDB RSP and ARM Simulator.

    This program is free software, you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY, without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with This program.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef Packet_H
#define Packet_H

#include <stdint.h>

char *gdbCreateMsgPacket(char *data);
void destroyPacket(char *packet);

// char *createdHexToString(unsigned long long int regVal, int bytes);
// void destroyHexToString(char *asciiString);

uint32_t decodeTwoByte(uint32_t byteData);
uint32_t decodeFourByte(uint32_t byteData);
uint64_t decodeEightByte(uint64_t byteData);

int verifyPacket(char *data);

#endif // Packet_H
