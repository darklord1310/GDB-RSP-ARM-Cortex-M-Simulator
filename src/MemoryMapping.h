#ifndef MemoryMapping_H
#define MemoryMapping_H

#include <stdint.h>

void (*dir[1024])();
void (*page[1024])();
void (*offset[4096])();

void memoryMap(uint32_t startAddress, uint32_t range, void (*funcPointer)());

#endif // MemoryMapping_H
