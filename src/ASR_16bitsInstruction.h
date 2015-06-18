#ifndef ASR_16bitsInstruction_H
#define ASR_16bitsInstruction_H

#include "ARMRegisters.h"
#include "getBits.h"
#include "StatusRegisters.h"
#include <stdint.h>

void ASRImmediate16bitsT1(uint32_t instruction);
void ASRRegisterToRegister16bitsT1(uint32_t instruction);

#endif // ASR_16bitsInstruction_H
