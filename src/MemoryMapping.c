#include "MemoryMapping.h"
#include "GPIOs.h"


/*
 *
 *  ==========================================================
 * |      Directory      |       Page      |      Offset     |
 * ===========================================================
 * |<------12 bits------>|<----10 bits---->|<----10 bits---->|
 *
 */
void memoryMap(uint32_t startAddress, uint32_t range, void (*funcPointer)())
{
  // uint32_t dirNum = startAddress / 0x400000 ;
  // uint32_t *page = (uint32_t *) directory[dirNum];
  // page = funcPointer;
  
  // page[0] = funcPointer;
}

void initVirtualMemory()
{
  
}
