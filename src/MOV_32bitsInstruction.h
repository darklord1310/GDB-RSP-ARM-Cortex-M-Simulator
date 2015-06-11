#ifndef MOV_32bitsInstruction_H
#define MOV_32bitsInstruction_H

#include "ARMRegisters.h"
#include "getBits.h"
#include "ModifiedImmediateConstant.h"

void MOVImmediate32bitsT2(unsigned int instruction, CoreRegister *coreReg);
void MOVImmediate32bitsT3(unsigned int instruction, CoreRegister *coreReg);

#endif // MOV_32bitsInstruction_H
