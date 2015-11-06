#ifndef MemoryMapping_H
#define MemoryMapping_H

#include <stdint.h>

#define DIR_SIZE      4096
#define PAGE_SIZE     1024
#define OFFSET_SIZE   1024

// typedef struct PageTable PageTable;

// struct PageTable
// {
  // uint32_t pageEntry[PAGE_SIZE];
// };

uint32_t directory[DIR_SIZE]; //__attribute__((aligned(4096)));
uint32_t page[PAGE_SIZE]; //__attribute__((aligned(4096)));
uint32_t offset[OFFSET_SIZE]; //__attribute__((aligned(4096)));

void memoryMap(uint32_t startAddress, uint32_t range, void (*funcPointer)());
void initVirtualMemory();

void initDirectory();
void initPage();
void initOffset();

// PageTable *createPage();

#endif // MemoryMapping_H
