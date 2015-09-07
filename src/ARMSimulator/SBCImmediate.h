#ifndef SBCImmediate_H
#define SBCImmediate_H

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

void SBCImmediateT1(uint32_t instruction);
void executeSBCImmediate(uint32_t Rn, uint32_t Rd, uint32_t immediate, uint32_t S);

#endif // SBCImmediate_H
