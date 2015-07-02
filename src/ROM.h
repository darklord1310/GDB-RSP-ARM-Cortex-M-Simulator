#ifndef ROM_H
#define ROM_H

#include <stdint.h>

typedef struct ROM ROM;
typedef struct ROMData ROMData;

// #define sizeOfROM       4294967296      
#define sizeOfROM       0xFFFFFFFF      


struct ROMData
{
  int data;
};

struct ROM
{
  // ROMData *address;     // pointer to pointer which point to the ROMData
  ROMData address[0xFFFFFFF];     // pointer to pointer which point to the ROMData
};

// ROM *rom;
ROMData address[0xFFFFFFF];


ROM *initROM();
void resetROM();
void destroyROM(ROM *rom);

#endif // ROM_H
