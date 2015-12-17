#include <stdio.h>
#include "MemoryMapping.h"
#include "GPIOs.h"
#include <malloc.h>

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
 //int (*handler) (int,int,int,int)
// void memoryMap(uint32_t startAddress, uint32_t range, int (*funcPtr)(int,int,int,int))
// {
  // int i;
  // uint32_t directoryIndex = startAddress & DIR_MASK;    // get the first 12-bits
  // directoryIndex = directoryIndex >> 20;
  // uint32_t pageIndex = startAddress & PAGE_MASK;        // get the next 10-bits
  // pageIndex = pageIndex >> 8;
  // uint32_t offsetIndex = startAddress & OFFSET_MASK;    // get the last 10-bits
  
  // for(i = 0; i < range; i++)
  // {
    // directory[directoryIndex] = page;         // map page to the directory
    // page[pageIndex] = funcPtr;
    // directory[directoryIndex] = &(*page);
    // page[pageIndex] = funcPtr;
  // }
// }

// uint32_t *createPage(int size)
// {
  // uint32_t (*newPage)(int, int, uint32_t, uint32_t) = calloc(size, sizeof(*newPage) );
  // return newPage;
// }


void mapPageToDirectory(uint32_t (*(*dir[]))(int, int, uint32_t, uint32_t), uint32_t startAddress, uint32_t range)
{
  int i;
  uint32_t directoryIndex = startAddress & DIR_MASK;    // get the first 12-bits
  directoryIndex = directoryIndex >> 20;

  for(i = directoryIndex; i < directoryIndex+range ; i++)
  {
    page *ptr;                                        // pointer to function pointer
    ptr = malloc(100 * sizeof *ptr);
    (dir[i]) = ptr;
  }
}


void mapHandlerToPage(uint32_t (*page[])(int, int, uint32_t, uint32_t), uint32_t (*handler)(int, int, uint32_t, uint32_t), uint32_t startAddress, uint32_t range)
{
  int i;
  uint32_t pageIndex = startAddress & PAGE_MASK;        // get the next 10-bits
  pageIndex = pageIndex >> 8;
  
  for(i = pageIndex; i < pageIndex+range ; i++)
  {
    printf("i: %x\n", i);
    page[i] = handler;
  }
}

void initVirtualMemory()
{
  // memoryMap(0x40020000, 0x400203FF - 0x40020000, initGPIOs);
}

uint32_t memoryHandler(int RW, int sizeOfData, uint32_t address, uint32_t data)
{
  return 1;
}

uint32_t gpioHandler(int RW, int sizeOfData, uint32_t address, uint32_t data)
{
  return 1;
}


void initDirectory()
{
  int i;

  for(i = 0; i < DIR_SIZE; i++)
  {
    directory[i] = 0;
  }
}

// void initPage()
// {
  // int i;

  // for(i = 0; i < PAGE_SIZE; i++)
  // {
    // page[i] = 0;
  // }
// }

// void initOffset()
// {
  // int i;

  // for(i = 0; i < OFFSET_SIZE; i++)
  // {
    // offset[i] = 0;
  // }
// }
