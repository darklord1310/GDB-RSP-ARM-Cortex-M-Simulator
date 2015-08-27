#ifndef SUBImmediate_H
#define SUBImmediate_H

#include "ARMRegisters.h"
#include "getAndSetBits.h"
#include "StatusRegisters.h"
#include <stdint.h>
#include "ModifiedImmediateConstant.h"

void SUBImmediateT1(uint32_t instruction);
void SUBImmediateT2(uint32_t instruction);
void executeSUBImmediate(uint32_t Rn, uint32_t Rd, uint32_t immediate, uint32_t S);

#endif // SUBImmediate_H
