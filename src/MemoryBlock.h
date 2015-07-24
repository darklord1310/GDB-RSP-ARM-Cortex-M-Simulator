#ifndef MemoryBlock_H
#define MemoryBlock_H

#include <stdint.h>

// typedef struct ROM ROM;
// typedef struct ROMData ROMData;

#define KILO_BYTE               1024
// #define TWO_HUND_FIFTY_SIX_KB   256 * KILO_BYTE
#define ROM_BASE_ADDR           0x00000    //500kb of virtual memory
#define RAM_BASE_ADDR           0x80000    //500kb of virtual memory

/* struct ROMData
{
  uint8_t data;
};

struct ROM
{
  ROMData *address;     // pointer to pointer which point to the ROMData
};

ROM *rom; */

uint8_t memoryBlock[KILO_BYTE * KILO_BYTE];

// void createROM();
// void resetROM();
// void destroyROM();
void resetMemoryBlock();
uint32_t virtualMemToPhysicalMem(uint32_t mem);

#endif // MemoryBlock_H
