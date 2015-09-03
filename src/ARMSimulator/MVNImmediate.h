#ifndef MVNImmediate_H
#define MVNImmediate_H

#include "ARMRegisters.h"
#include "getAndSetBits.h"
#include "StatusRegisters.h"
#include <stdint.h>
#include "ModifiedImmediateConstant.h"

void MVNImmediateT1(uint32_t instruction);
void executeMVNImmediate(uint32_t immediate, uint32_t Rd, uint32_t S);

#endif // MVNImmediate_H
