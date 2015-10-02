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


#include "LoadElfToMemory.h"
#include "GetHeaders.h"
#include "MemoryBlock.h"
#include "ARMRegisters.h"


#define ELF_FILE_DESTINATION  "C:/Users/Asus/Desktop/TDD/Project/GDB-RSP-ARM-Cortex-M-Simulator/data/Ccode.elf"
#define COIDE_ELF_FILE        "C:/Users/Asus/Desktop/CoIDE/workspace/BlinkyLED/Test01/Debug/bin/Test01.elf"

extern ElfData *elfData;
extern ElfSection *isr, *text, *rodata;
extern uint32_t entryAddress;
extern int fileStatus;

void loadElf()
{
  int i;

  getElfSection(COIDE_ELF_FILE);
  
  // .isr_vector section
  printf("\nLoading section .isr_vector, size 0x%x lma 0x%x\n", isr->size, isr->destAddress);
  for(i = 0; i < isr->size; i++)
    memoryBlock[virtualMemToPhysicalMem(isr->destAddress + i)] = *(isr->dataAddress + i);

  // .text section
  printf("Loading section .text, size 0x%x lma 0x%x\n", text->size, text->destAddress);
  for(i = 0; i < text->size; i++)
    memoryBlock[virtualMemToPhysicalMem(text->destAddress + i)] = *(text->dataAddress + i);

  // .rodata section
  printf("Loading section .rodata, size 0x%x lma 0x%x\n", rodata->size, rodata->destAddress);
  for(i = 0; i < text->size; i++)
    memoryBlock[virtualMemToPhysicalMem(rodata->destAddress + i)] = *(rodata->dataAddress + i);

  printf("Start address 0x%x, load size %d\n", elfData->eh->e_entry - 1, text->size + isr->size + rodata->size);
  coreReg[PC] = elfData->eh->e_entry - 1;
}