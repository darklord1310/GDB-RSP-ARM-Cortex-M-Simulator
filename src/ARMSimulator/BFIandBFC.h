#ifndef BFIandBFC_H
#define BFIandBFC_H

#include "ARMRegisters.h"
#include "getAndSetBits.h"
#include "ITandHints.h"
#include "ConditionalExecution.h"
#include <stdint.h>
#include <stdio.h>

void BFIT1(uint32_t instruction);
void BFCT1(uint32_t instruction);

#endif // BFIandBFC_H
