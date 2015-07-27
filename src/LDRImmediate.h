#ifndef LDRImmediate_H
#define LDRImmediate_H

#include <stdint.h>

void LDRImmediateT1(uint32_t instruction);
void LDRImmediateT2(uint32_t instruction);
void LDRBImmediateT1(uint32_t instruction);
void LDRHImmediateT1(uint32_t instruction);
uint32_t loadWordFromMemory(uint32_t address);

#endif // LDRImmediate_H
