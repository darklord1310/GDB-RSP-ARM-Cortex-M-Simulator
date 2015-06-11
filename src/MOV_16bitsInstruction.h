#ifndef MOV_16bitsInstruction_H
#define MOV_16bitsInstruction_H

#include "ARMRegisters.h"
#include "getBits.h"

void MOVImmediate16bitsT1(unsigned int instruction, CoreRegister *coreReg);
void MOVRegisterToRegister16bitsT2(unsigned int instruction, CoreRegister *coreReg);
void MOVRegisterToRegister16bitsT1(unsigned int instruction, CoreRegister *coreReg);

#endif // MOVImmediate_16bitsInstruction_H
