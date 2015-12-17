#ifndef MemoryMapping_H
#define MemoryMapping_H

#include <stdint.h>

#define DIR_SIZE      4096
#define PAGE_SIZE     1024
#define OFFSET_SIZE   1024

typedef enum {READ, WRITE} Operation;
typedef uint32_t (*page)(int RW, int sizeOfData, uint32_t address, uint32_t data);


uint32_t (*(*directory[DIR_SIZE]))(int RW, int sizeOfData, uint32_t address, uint32_t data);
// uint32_t (*page[PAGE_SIZE])(int RW, int sizeOfData, uint32_t address, uint32_t data);


void mapPageToDirectory(uint32_t (*(*dir[]))(int, int, uint32_t, uint32_t), uint32_t startAddress, uint32_t range);
void mapHandlerToPage(uint32_t (*page[])(int, int, uint32_t, uint32_t), uint32_t (*handler)(int, int, uint32_t, uint32_t), uint32_t startAddress, uint32_t range);
void initVirtualMemory();
void initDirectory();
void initPage();
void initOffset();

uint32_t memoryHandler(int RW, int sizeOfData, uint32_t address, uint32_t data);
uint32_t gpioHandler(int RW, int sizeOfData, uint32_t address, uint32_t data);


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
