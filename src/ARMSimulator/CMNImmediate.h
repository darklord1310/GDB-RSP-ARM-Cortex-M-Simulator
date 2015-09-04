#ifndef CMNImmediate_H
#define CMNImmediate_H

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

void CMNImmediateT1(uint32_t instruction);
void executeCMNImmediate(uint32_t Rn, uint32_t immediate);

#endif // CMNImmediate_H
