#include <stdio.h>
#include "MemoryMapping.h"
#include "GPIOs.h"


#define   DIR_MASK      0xfff00000
#define   PAGE_MASK     0xffc00
#define   OFFSET_MASK   0x2ff

/*
 *
 *  ==========================================================
 * |      Directory      |       Page      |      Offset     |
 * ===========================================================
 * |<------12 bits------>|<----10 bits---->|<----10 bits---->|
 *
 */
void memoryMap(uint32_t startAddress, uint32_t range, void (*funcPtr)())
{
  int i;
  uint32_t directoryIndex = startAddress & DIR_MASK;    // get the first 12-bits
  directoryIndex = directoryIndex >> 20;
  uint32_t pageIndex = startAddress & PAGE_MASK;        // get the next 10-bits
  pageIndex = pageIndex >> 8;
  uint32_t offsetIndex = startAddress & OFFSET_MASK;    // get the last 10-bits

  // for(i = 0; i < range; i++)
  // {
    directory[directoryIndex] = (uint32_t)page;         // map page to the directory
    page[pageIndex] = (uint32_t)funcPtr;
    // directory[directoryIndex] = &(*page);
    // page[pageIndex] = funcPtr;
  // }
}

void initVirtualMemory()
{
  // memoryMap(0x40020000, 0x400203FF - 0x40020000, initGPIOs);
}

uint32_t handler(readWrite, data, size)
{
  
}

void initDirectory()
{
  int i;

  for(i = 0; i < DIR_SIZE; i++)
  {
    directory[i] = 0;
  }
}

void initPage()
{
  int i;

  for(i = 0; i < PAGE_SIZE; i++)
  {
    page[i] = 0;
  }
}

void initOffset()
{
  int i;

  for(i = 0; i < OFFSET_SIZE; i++)
  {
    offset[i] = 0;
  }
}
