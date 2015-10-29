#ifndef MemoryMapping_H
#define MemoryMapping_H

#include <stdint.h>

// typedef struct PageInfo PageInfo;

// struct PageInfo
// {
  // uint32_t *page;
// };

// uint32_t directory[4096] = {0};
// uint32_t page[1024] = {0};
// uint32_t offset[1024] = {0};

void memoryMap(uint32_t startAddress, uint32_t range, void (*funcPointer)());
void initVirtualMemory();

// PageInfo *createPage();

#endif // MemoryMapping_H
