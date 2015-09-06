#ifndef SignedAndUnsignedBitFieldExtract_H
#define SignedAndUnsignedBitFieldExtract_H

#include "ARMRegisters.h"
#include "getAndSetBits.h"
#include "ITandHints.h"
#include "ConditionalExecution.h"
#include <stdint.h>
#include <stdio.h>

void SBFXT1(uint32_t instruction);
void UBFXT1(uint32_t instruction);

#endif // SignedAndUnsignedBitFieldExtract_H
