#ifndef ROM_H
#define ROM_H

#include <stdint.h>

typedef struct ROM ROM;
typedef struct ROMData ROMData;

#define KILO_BYTE               1024
#define TWO_HUND_FIFTY_SIX_KB   256 * KILO_BYTE
#define ROM_BASE_ADDR           0x000000    //256kb of virtual memory
#define RAM_BASE_ADDR           0x400001    //256kb of virtual memory
// #define sizeOfROM               0xFFFFFFFF

struct ROMData
{
  uint32_t data;
};

struct ROM
{
  ROMData *address;     // pointer to pointer which point to the ROMData
};

ROM *rom;
// ROMData address[0xFFFFFFF];
// ROMData rom[TWO_HUND_FIFTY_SIX_KB];
// ROMData ram[TWO_HUND_FIFTY_SIX_KB];


void createROM();
void resetROM();
void destroyROM();
uint32_t virtualMemToPhysicalMem(uint32_t mem);

#endif // ROM_H
