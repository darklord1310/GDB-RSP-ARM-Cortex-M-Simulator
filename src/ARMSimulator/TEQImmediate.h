#ifndef TEQImmediate_H
#define TEQImmediate_H

#include "ARMRegisters.h"
#include "getAndSetBits.h"
#include "StatusRegisters.h"
#include <stdint.h>
#include "ModifiedImmediateConstant.h"

void TEQImmediateT1(uint32_t instruction);
void executeTEQImmediate(uint32_t immediate, uint32_t Rn);

#endif // TEQImmediate_H
