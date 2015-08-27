#ifndef LoadAndWriteMemory_H
#define LoadAndWriteMemory_H

#include <stdint.h>

void writeByteToMemory(uint32_t address, uint32_t valueToWrite, int numberOfByteToWrite);
uint32_t loadByteFromMemory(uint32_t address, int numberOfByteToRead);
void isWatchPointReachedForRead(uint32_t address, int size);
void isWatchPointReachedForWrite(uint32_t address, int size);

#endif // LoadAndWriteMemory_H
