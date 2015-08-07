#ifndef PUSH_H
#define PUSH_H

#include <stdint.h>

void PUSHT1(uint32_t instruction);
void pushMultipleRegisterToMemory(uint32_t address, uint32_t registerList);
int bitCount(uint32_t value);


#endif // PUSH_H
