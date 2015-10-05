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