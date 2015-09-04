#ifndef ADCImmediate_H
#define ADCImmediate_H

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

void ADCImmediateT1(uint32_t instruction);
void executeADCImmediate(uint32_t Rn, uint32_t Rd, uint32_t immediate, uint32_t S);

#endif // ADCImmediate_H
