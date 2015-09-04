#ifndef EORImmediate_H
#define EORImmediate_H

#include "ARMRegisters.h"
#include "getAndSetBits.h"
#include "StatusRegisters.h"
#include <stdint.h>
#include "ModifiedImmediateConstant.h"

void EORImmediateT1(uint32_t instruction);
void executeEORImmediate(uint32_t immediate, uint32_t Rd, uint32_t Rn, uint32_t S);

#endif // EORImmediate_H
