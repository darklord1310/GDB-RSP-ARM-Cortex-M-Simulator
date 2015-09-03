#ifndef BICImmediate_H
#define BICImmediate_H

#include "ARMRegisters.h"
#include "getAndSetBits.h"
#include "StatusRegisters.h"
#include <stdint.h>
#include "ModifiedImmediateConstant.h"

void BICImmediateT1(uint32_t instruction);
void executeBICImmediate(uint32_t immediate, uint32_t Rd, uint32_t Rn, uint32_t S);

#endif // BICImmediate_H
