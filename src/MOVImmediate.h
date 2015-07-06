#ifndef MOVImmediate_H
#define MOVImmediate_H

#include "ARMRegisters.h"
#include "getAndSetBits.h"
#include "StatusRegisters.h"
#include <stdint.h>
#include "ModifiedImmediateConstant.h"

void MOVImmediateT1(uint32_t instruction);
void MOVImmediateT2(uint32_t instruction);
void MOVImmediateT3(uint32_t instruction);
void executeMOVImmediate(uint32_t immediate, uint32_t Rd, uint32_t S, uint32_t affectCarry);

#endif // MOVImmediate_H
