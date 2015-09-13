/*  
    Program Name       : GDB RSP and ARM Simulator
    Author             : Wong Yan Yin, Jackson Teh Ka Sing 
    Copyright (C) 2015 TARUC

    This file is part of GDB RSP and ARM Simulator.

    GDB RSP and ARM Simulator is free software, you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    GDB RSP and ARM Simulator is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY, without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with GDB RSP and ARM Simulator.  If not, see <http://www.gnu.org/licenses/>.

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
