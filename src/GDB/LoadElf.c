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
#include "FileOperation.h"

extern ElfData *elfData;
extern ElfSection *isr, *text, *initArray, *rodata, *data, *finiArray;
extern uint32_t entryAddress;
extern int fileStatus;

void loadElf(ElfData *elfData, uint32_t flashStartAddr, uint32_t flashSize)
{
  int i, j;
  uint32_t physAddr, loadSize = 0;
  char *sectionName;
  ElfSection *elfSection;

  for(i = 0; i < getTotalSectionHeader(elfData); i++)
  {
    physAddr = getSectionLma(elfData, i);

    if(isWithinRange(physAddr, flashStartAddr, flashSize))
    {
      sectionName = getSectionInfoNameUsingIndex(elfData, i);
      elfSection = getElfSectionInfo(elfData, sectionName);
      loadSize += elfSection->size;

      simulatorCopyBlock(physAddr, elfSection->dataAddress, elfSection->size);

      printf("Loading section %s, size 0x%x lma 0x%x\n", sectionName, elfSection->size, physAddr);
    }
  }

  closeElfSection(elfSection);
  writeToCoreRegisters(PC, getStartAddress(elfData));
  printf("Start address 0x%x, load size %d\n\n", coreReg[PC], loadSize);
}

uint32_t getSectionLma(ElfData *elfData, int sectionIndex)
{
  int i, totalProgramHeader = getTotalProgramHeader(elfData);
  // uint32_t sectionVirtAddr = getSectionVirtualAddress(elfData, sectionIndex);
  uint32_t sectionOffset = getSectionOffset(elfData, sectionIndex);
  uint32_t programOffset, programFileSz, programPhyAddr, programVirtAddr;

  for(i = 0; i < totalProgramHeader; i++)
  {
    programOffset = getProgramOffset(elfData, i);
    programFileSz = getProgramFileSizez(elfData, i);
    programPhyAddr = getProgramPhysicalAddress(elfData, i);
    // programVirtAddr = getProgramVirtualAddress(elfData, i);

    if(isWithinRange(sectionOffset, programOffset, programFileSz) && isProgramLoadType(elfData, i))
      return programPhyAddr + sectionOffset - programOffset;
    // if(isWithinRange(sectionVirtAddr, programVirtAddr, programFileSz) && isProgramLoadType(elfData, i))
      // return sectionVirtAddr - programVirtAddr - programPhyAddr;
  }

  return -1;
}

int isWithinRange(uint32_t address, uint32_t startAddr, uint32_t size)
{
  if(address < startAddr + size && address >= startAddr)
    return 1;

  return 0;
}

int isProgramLoadType(ElfData *elfData, int index)
{
  if(getProgramType(elfData, index) == PT_LOAD)
    return 1;

  return 0;
}