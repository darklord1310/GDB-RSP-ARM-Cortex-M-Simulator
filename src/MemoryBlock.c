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

#include "MemoryBlock.h"
#include <malloc.h>
#include <stdio.h>

/*
Address range               Memory region       Memory type[a]      Execute Never (XN)[a]   Description

0x00000000- 0x1FFFFFFF      Code                Normal              -                       Executable region for program code.
                                                                                            You can also put data here.

0x20000000- 0x3FFFFFFF      SRAM                Normal              -                       Executable region for data. You can also put code here.
                                                                                            This region includes bit band and bit band alias areas,
                                                                                            see Table 2.13.

0x40000000- 0x5FFFFFFF      Peripheral          Device              XN                      This region includes bit band and bit band alias areas, see Table 2.14.

0x60000000- 0x9FFFFFFF      External RAM        Normal              -                       Executable region for data.

0xA0000000- 0xDFFFFFFF      External device     Device              XN                      External Device memory.

0xE0000000- 0xE00FFFFF      Private Peripheral  Strongly-           XN                      This region includes the NVIC, System timer,
                            Bus                 ordered                                     and system control block.

0xE0100000- 0xFFFFFFFF      Device              Device              XN                      Implementation-specific.

*/

void resetMemoryBlock()
{
    int i;

    for(i = 0; i < sizeof(memoryBlock); i++)
    {
        memoryBlock[i] = 0;
    }
}

uint32_t virtualMemToPhysicalMem(uint32_t virtualMem)
{
    uint32_t virtualAddr = 0xffffffff;

    if(virtualMem < 0x20000000)
    {
        if(virtualMem >= 0x8000000)
            virtualAddr = ((virtualMem - 0x20000000) & 0x000fffff) + ROM_BASE_ADDR + 0x10000;
        else if(virtualMem < 0x10000)
            virtualAddr = virtualMem;
        // else
            // printf("Code space not enough\n");
    }
    else if(virtualMem < 0x40000000)
        virtualAddr = ((virtualMem - 0x40000000) & 0x000fffff) + RAM_BASE_ADDR;
    else if(virtualMem < 0xe00fffff && virtualMem >= 0xe0000000)
        virtualAddr = ((virtualMem - 0xe00fffff) & 0x000fffff) + PBP_BASE_ADDR;
    else
        printf("Memory exceeded\n");

    return virtualAddr;
}

void simulatorCopyBlock(uint32_t sourceAddr, uint8_t *destAddr, uint32_t size)
{
  int i = 0;

  for(i = 0; i < size; i++)
  {
    memoryBlock[virtualMemToPhysicalMem(sourceAddr + i)] = destAddr[i];
  }
}

void simulatorWriteMemory(uint32_t data, uint32_t addr)
{

}

int simulatorReadMemory(uint32_t addr)
{
  return memoryBlock[virtualMemToPhysicalMem(addr)];
}
