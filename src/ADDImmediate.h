#ifndef ADDImmediate_H
#define ADDImmediate_H

#include "ARMRegisters.h"
#include "getBits.h"
#include "StatusRegisters.h"
#include <stdint.h>
#include "ModifiedImmediateConstant.h"

void ADDImmediateT1(uint32_t instruction);
void ADDImmediateT2(uint32_t instruction);
void executeADDImmediate(uint32_t Rn, uint32_t Rd, uint32_t immediate, uint32_t S);

#endif // ADDImmediate_H
