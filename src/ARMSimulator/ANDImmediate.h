#ifndef ANDImmediate_H
#define ANDImmediate_H

#include "ARMRegisters.h"
#include "getAndSetBits.h"
#include "StatusRegisters.h"
#include <stdint.h>
#include "ModifiedImmediateConstant.h"

void ANDImmediateT1(uint32_t instruction);
void executeANDImmediate(uint32_t immediate, uint32_t Rd, uint32_t Rn, uint32_t S);

#endif // ANDImmediate_H
