#ifndef ORRImmediate_H
#define ORRImmediate_H

#include "ARMRegisters.h"
#include "getAndSetBits.h"
#include "StatusRegisters.h"
#include <stdint.h>
#include "ModifiedImmediateConstant.h"

void ORRImmediateT1(uint32_t instruction);
void executeORRImmediate(uint32_t immediate, uint32_t Rd, uint32_t Rn, uint32_t S);

#endif // ORRImmediate_H
