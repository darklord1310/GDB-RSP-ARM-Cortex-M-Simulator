#ifndef CMPImmediate_H
#define CMPImmediate_H

#include "ARMRegisters.h"
#include "getBits.h"
#include "StatusRegisters.h"
#include "ModifiedImmediateConstant.h"
#include <stdint.h>

void CMPImmediateT1(uint32_t instruction);
void CMPImmediateT2(uint32_t instruction);
void executeCMP(uint32_t value, uint32_t Rn );

#endif // CMPImmediate_H
