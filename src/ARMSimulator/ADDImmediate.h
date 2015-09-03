#ifndef ADDImmediate_H
#define ADDImmediate_H

#include <stdint.h>
#include "ModifiedImmediateConstant.h"
#include "ConditionalExecution.h"
#include "ITandHints.h"
#include "StatusRegisters.h"
#include "ARMRegisters.h"
#include "getAndSetBits.h"
#include "getMask.h"
#include <assert.h>
#include <stdio.h>

void ADDImmediateT1(uint32_t instruction);
void ADDImmediateT2(uint32_t instruction);
void ADDImmediateT3(uint32_t instruction);
void ADDImmediateT4(uint32_t instruction);
void executeADDImmediate(uint32_t Rn, uint32_t Rd, uint32_t immediate, uint32_t S);

#endif // ADDImmediate_H
