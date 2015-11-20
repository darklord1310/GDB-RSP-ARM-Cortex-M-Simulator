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


#ifndef MemoryBlock_H
#define MemoryBlock_H

#include <stdint.h>

#define KILO_BYTE               1024
#define MEM_SIZE                KILO_BYTE * KILO_BYTE * 2
#define ROM_BASE_ADDR           0x00000    //500kb of virtual memory
#define RAM_BASE_ADDR           0x80000    //500kb of virtual memory
#define PBP_BASE_ADDR           0x100000   //500kb of virtual memory

uint8_t memoryBlock[MEM_SIZE];

void resetMemoryBlock();
uint32_t virtualMemToPhysicalMem(uint32_t virtualMem);
void simulatorCopyBlock(uint32_t sourceAddr, uint8_t *destAddr, uint32_t size);

void simulatorWriteMemory(uint32_t data, uint32_t addr);
int simulatorReadMemory(uint32_t addr);

#endif // MemoryBlock_H
