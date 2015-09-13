#ifndef RRX_H
#define RRX_H

#include "ARMRegisters.h"
#include "getAndSetBits.h"
#include "StatusRegisters.h"
#include "ITandHints.h"
#include "ConditionalExecution.h"
#include <stdio.h>
#include <stdint.h>
#include "ModifiedImmediateConstant.h"

void RRXT1(uint32_t instruction);
void executeRRXT1(uint32_t Rm, uint32_t Rd, uint32_t S);

#endif // RRX_H
