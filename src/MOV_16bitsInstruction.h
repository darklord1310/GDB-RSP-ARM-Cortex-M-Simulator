#ifndef MOV_16bitsInstruction_H
#define MOV_16bitsInstruction_H

#include "ARMRegisters.h"
#include "getBits.h"
#include <stdint.h>

void MOVImmediate16bitsT1(uint32_t instruction);
void MOVRegisterToRegister16bitsT2(uint32_t instruction);
void MOVRegisterToRegister16bitsT1(uint32_t instruction);

#endif // MOVImmediate_16bitsInstruction_H
