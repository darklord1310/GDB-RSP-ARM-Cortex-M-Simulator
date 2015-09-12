#ifndef PUSH_H
#define PUSH_H

#include <stdint.h>

void PUSHT1(uint32_t instruction);
void PUSHT2(uint32_t instruction);
int bitCount(uint32_t value);
void pushMultipleRegisterToMemory(uint32_t address, uint32_t registerList, int sizeOfRegisterList);

#endif // PUSH_H
