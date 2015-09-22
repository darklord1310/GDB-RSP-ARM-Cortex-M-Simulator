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


#ifndef LoadAndWriteMemory_H
#define LoadAndWriteMemory_H

#include <stdint.h>

typedef enum {POSTINDEX,PREINDEX,OFFINDEX,UNDEFINED} IndexType;

void writeByteToMemory(uint32_t address, uint32_t valueToWrite, int numberOfByteToWrite);
uint32_t loadByteFromMemory(uint32_t address, int numberOfByteToRead);
void isWatchPointReachedForRead(uint32_t address, int size);
void isWatchPointReachedForWrite(uint32_t address, int size);
int isOffPostOrPreIndex(uint32_t index,uint32_t writeback);

#endif // LoadAndWriteMemory_H
