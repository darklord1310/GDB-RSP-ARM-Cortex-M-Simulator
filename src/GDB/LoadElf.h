#ifndef LoadElf_H
#define LoadElf_H

#include <stdint.h>
#include "GetHeaders.h"

#define ELF_FILE    "C:/Users/user06D/Desktop/GDB-RSP-ARM-Cortex-M-Simulator/data/Ccode.elf"
#define COIDE_ELF_FILE    "C:/Users/user06D/Desktop/ARM-BlinkyLED/Test01/Debug/bin/Test01.elf"
#define getSectionVma(elfData, i)     getSectionVirtualAddress(elfData, i)

void loadElf(ElfData *elfData);
uint32_t getSectionLma(ElfData *elfData, int index);
int isWithinRange(uint32_t address, uint32_t startAddr, uint32_t size);

#endif // LoadElf_H
