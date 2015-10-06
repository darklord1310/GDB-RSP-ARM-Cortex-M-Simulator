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


#include <stdio.h>
#include <malloc.h>
#include "LoadElf.h"
#include "ARMRegisters.h"
#include "MemoryBlock.h"
#include "ProgramElf.h"
#include "GetHeaders.h"
#include "Relocator.h"
#include "Read_File.h"
#include "elf.h"
#include "CException.h"
#include "ErrorCode.h"

#define getStartAddress(elfdata)    (elfData->eh->e_entry) & 0xfffffffe

extern ElfData *elfData;
extern ElfSection *isr, *text, *initArray, *rodata, *data, *finiArray;
extern uint32_t entryAddress;
extern int fileStatus;

void loadElf(ElfData *elfData)
{
  int i, j, flashStartAddr = 0x08000000, flashSize = 2048 * 1024;
  uint32_t physAddr, loadSize = 0;
  char *sectionName;
  ElfSection *elfSection;

  // getElfSection(ELF_FILE);
  // Start address 0x8000764, load size 3008

  for(i = 0; i < elfData->eh->e_shnum; i++)
  {
    physAddr = getSectionLma(elfData, i);

    if(isWithinRange(physAddr, flashStartAddr, flashSize))
    {
      sectionName = getSectionInfoNameUsingIndex(elfData, i);

      // printf("Section Name: %s\n", sectionName);
      elfSection = getElfSectionInfo(elfData, sectionName);
      loadSize += elfSection->size;
      // printf("Section data: 0x%x\n", *(elfSection->dataAddress));

      simulatorCopyBlock(physAddr, elfSection->dataAddress, elfSection->size);

      printf("Loading section %s, size 0x%x lma 0x%x\n", sectionName, elfSection->size, physAddr);
    }
  }
  
  coreReg[PC] = getStartAddress(elfData);
  printf("Start address 0x%x, load size %d\n\n", coreReg[PC], loadSize);
}

uint32_t getSectionLma(ElfData *elfData, int index)
{
  int i;

  for(i = 0; i < elfData->eh->e_phnum; i++)
  {
    if(elfData->sh[index].sh_offset < elfData->ph[i].p_offset + elfData->ph[i].p_filesz && elfData->sh[index].sh_addr >= elfData->ph[i].p_vaddr)
      return elfData->ph[i].p_paddr + elfData->sh[index].sh_offset - elfData->ph[i].p_offset;
  }

  return -1;
}

int isWithinRange(uint32_t address, uint32_t startAddr, uint32_t size)
{
  if(address <= startAddr + size && address >= startAddr)
    return 1;

  return 0;
}