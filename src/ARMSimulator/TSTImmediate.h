#ifndef TSTImmediate_H
#define TSTImmediate_H

#include "ARMRegisters.h"
#include "getAndSetBits.h"
#include "StatusRegisters.h"
#include <stdint.h>
#include "ModifiedImmediateConstant.h"

void TSTImmediateT1(uint32_t instruction);
void executeTSTImmediate(uint32_t immediate, uint32_t Rn);

#endif // TSTImmediate_H
