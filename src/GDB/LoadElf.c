#include <stdio.h>
#include <malloc.h>
#include "LoadElf.h"
// #include "ARMRegisters.h"
// #include "MemoryBlock.h"
#include "ProgramElf.h"
#include "GetHeaders.h"
#include "Relocator.h"
#include "Read_File.h"
#include "elf.h"
#include "CException.h"
#include "ErrorCode.h"

#define ELF_FILE    "C:/Users/user06D/Desktop/GDB-RSP-ARM-Cortex-M-Simulator/data/Ccode.elf"

extern ElfData *elfData;
extern ElfSection *isr, *text, *initArray, *rodata, *data, *finiArray;
extern uint32_t entryAddress;
extern int fileStatus;

void loadElf()
{
  getElfSection(ELF_FILE);
/*Loading section .isr_vector, size 0x1ac lma 0x8000000
  Loading section .text, size 0x5d8 lma 0x80001b0
  Loading section .rodata, size 0x8 lma 0x8000788
  Loading section .init_array, size 0x8 lma 0x8000790
  Loading section .fini_array, size 0x4 lma 0x8000798
  Loading section .data, size 0x428 lma 0x800079c
  Start address 0x8000764, load size 3008 */

  printf("Loading section .isr_vector, size 0x%x lma 0x%x\n", isr->size, isr->destAddress);
  printf("Loading section .text, size 0x%x lma 0x%x\n", text->size, text->destAddress);
  printf("Loading section .rodata, size 0x%x lma 0x%x\n", rodata->size, rodata->destAddress);
  printf("Loading section .init_array, size 0x%x lma 0x%x\n", initArray->size, initArray->destAddress);
  printf("Loading section .fini_array, size 0x%x lma 0x%x\n", finiArray->size, finiArray->destAddress);
  printf("Loading section .data, size 0x%x lma 0x%x\n", data->size, data->destAddress);


}

uint32_t mappingVirtAddress(int index)
{
  int i;
  elfData = openElfFile(ELF_FILE);
  
  for(i = 0; i < elfData->eh->e_phnum; i++)
  {
    if(elfData->sh[index].sh_addr <= elfData->ph[i].p_vaddr + elfData->ph[i].p_memsz)
      return elfData->ph[i].p_paddr + elfData->sh[index].sh_offset - elfData->ph[i].p_offset;
  }
}