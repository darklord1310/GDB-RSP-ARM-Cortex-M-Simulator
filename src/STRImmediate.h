#ifndef STRImmediate_H
#define STRImmediate_H

#include <stdint.h>

void STRImmediateT1(uint32_t instruction);
void STRBImmediateT1(uint32_t instruction);
void STRHImmediateT1(uint32_t instruction);
void STRImmediateT2(uint32_t instruction);
void writeByteToMemory(uint32_t address, uint32_t valueToWrite, int numberOfByteToWrite);

#endif // STRImmediate_H
