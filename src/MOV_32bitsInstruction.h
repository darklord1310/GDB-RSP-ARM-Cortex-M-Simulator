#ifndef MOV_32bitsInstruction_H
#define MOV_32bitsInstruction_H

#include "ARMRegisters.h"
#include "getBits.h"
#include "ModifiedImmediateConstant.h"
#include <stdint.h>
#include "StatusRegisters.h"

void MOVImmediate32bitsT2(uint32_t instruction);
void MOVImmediate32bitsT3(uint32_t instruction);
void MOVRegisterToRegister32bitsT3(uint32_t instruction);

#endif // MOV_32bitsInstruction_H
