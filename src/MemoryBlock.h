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
