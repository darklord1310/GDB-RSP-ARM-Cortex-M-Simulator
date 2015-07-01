#ifndef ROM_H
#define ROM_H

#include <stdint.h>

typedef struct ROM ROM;
typedef struct ROMData ROMData;

#define sizeOfROM         4294967296      


struct ROMData
{
  uint32_t data;
  
};

struct ROM
{
  ROMData *address;     // pointer to pointer which point to the ROMData
};

ROM *rom;


void resetROM();
ROM *initROM();
void destroyROM();

#endif // ROM_H
