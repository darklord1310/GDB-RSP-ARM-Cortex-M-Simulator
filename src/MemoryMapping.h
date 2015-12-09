#ifndef MemoryMapping_H
#define MemoryMapping_H

#include <stdint.h>

#define DIR_SIZE      4096
#define PAGE_SIZE     1024
#define OFFSET_SIZE   1024

typedef enum {READ, WRITE} Operation;

uint32_t (*(*directory[DIR_SIZE]))();


uint32_t (*page[PAGE_SIZE])();


uint32_t (*offset[OFFSET_SIZE])();

void memoryMap(uint32_t startAddress, uint32_t range, void (*funcPtr)());
void initVirtualMemory();

void initDirectory();
void initPage();
void initOffset();

uint32_t handler(Operation readWrite, uint32_t data, uint32_t size);



// #define PAGE_TABLE_MAP          0xFFF00000
// #define ADDR_TO_PTE(addr)       (uint32_t *)(PAGE_TABLE_MAP + (((uint32_t) (addr) / 4096)))

// typedef struct PageTable PageTable;
// typedef struct Offset Offset;

// struct PageTable
// {
  // uint32_t pageEntry[PAGE_SIZE];
// };

// struct Offset
// {
  // uint8_t offsetData[OFFSET_SIZE];
// };

// void (**directory[DIR_SIZE])();
// void (*page[PAGE_SIZE])();
// uint32_t offset[OFFSET_SIZE];

// PageTable *createPage();

#endif // MemoryMapping_H
