#ifndef ORNImmediate_H
#define ORNImmediate_H


#include "ARMRegisters.h"
#include "getAndSetBits.h"
#include "StatusRegisters.h"
#include <stdint.h>
#include "ModifiedImmediateConstant.h"

void ORNImmediateT1(uint32_t instruction);
void executeORNImmediate(uint32_t immediate, uint32_t Rd, uint32_t Rn, uint32_t S);

#endif // ORNImmediate_H
