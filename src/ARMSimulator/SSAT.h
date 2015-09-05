#ifndef SSAT_H
#define SSAT_H

#include "ARMRegisters.h"
#include "getAndSetBits.h"
#include "ITandHints.h"
#include "ConditionalExecution.h"
#include <stdint.h>
#include <stdio.h>
#include <math.h>

void SSATT1(uint32_t instruction);
void executeSSAT(uint32_t Rd, uint32_t Rn, uint32_t immediate, uint32_t shiftDirection, uint32_t shiftImmediate);

#endif // SSAT_H
