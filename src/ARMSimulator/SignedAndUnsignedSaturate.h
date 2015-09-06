#ifndef SignedAndUnsignedSaturate_H
#define SignedAndUnsignedSaturate_H

#include "ARMRegisters.h"
#include "getAndSetBits.h"
#include "ITandHints.h"
#include "ConditionalExecution.h"
#include "ShiftOperation.h"
#include <stdint.h>
#include <stdio.h>
#include <math.h>
#include <assert.h>

void SSATT1(uint32_t instruction);
void USATT1(uint32_t instruction);
void executeSSAT(uint32_t Rd, uint32_t Rn, uint32_t immediate, uint32_t shiftDirection, uint32_t shiftImmediate);
void executeUSAT(uint32_t Rd, uint32_t Rn, uint32_t immediate, uint32_t shiftDirection, uint32_t shiftImmediate);

#endif // SignedAndUnsignedSaturate_H
