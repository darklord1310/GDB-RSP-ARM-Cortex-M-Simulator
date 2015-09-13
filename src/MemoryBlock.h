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


#ifndef MemoryBlock_H
#define MemoryBlock_H

#include <stdint.h>

#define KILO_BYTE               1024
#define ROM_BASE_ADDR           0x00000    //500kb of virtual memory
#define RAM_BASE_ADDR           0x80000    //500kb of virtual memory

uint8_t memoryBlock[KILO_BYTE * KILO_BYTE];

void resetMemoryBlock();
uint32_t virtualMemToPhysicalMem(uint32_t mem);

#endif // MemoryBlock_H
