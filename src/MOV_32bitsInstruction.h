#ifndef MOV_32bitsInstruction_H
#define MOV_32bitsInstruction_H

#include "ARMRegisters.h"
#include "getBits.h"
#include "ModifiedImmediateConstant.h"
#include <stdint.h>

void MOVImmediate32bitsT2(uint32_t instruction, CoreRegister *coreReg);
void MOVImmediate32bitsT3(uint32_t instruction, CoreRegister *coreReg);
void MOVRegisterToRegister32bitsT3(uint32_t instruction, CoreRegister *coreReg);

#endif // MOV_32bitsInstruction_H
