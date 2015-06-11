#ifndef MOV_32bitsInstruction_H
#define MOV_32bitsInstruction_H

#include "ARMRegisters.h"
#include "getBits.h"

void MOVImmediate32bitsT2(unsigned int instruction, CoreRegister *coreReg);

#endif // MOV_32bitsInstruction_H
