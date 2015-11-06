#include <stdio.h>
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
  int i;

  // for(i = 0; i < range; i++)
  // {
    uint32_t directoryIndex = startAddress & 0xfff00000;    // get the first 12-bits
    directoryIndex = directoryIndex >> 20;
    directory[directoryIndex] = (uint32_t)page;

    uint32_t pageIndex = startAddress & 0xffc00;
    pageIndex = pageIndex >> 8;
    page[pageIndex] = (uint32_t)funcPointer;
  // }
}

void initVirtualMemory()
{
  // memoryMap(0x40020000, 0x400203FF - 0x40020000, initGPIOs);
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
