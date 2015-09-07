#ifndef MOVT_H
#define MOVT_H

#include "ARMRegisters.h"
#include "getAndSetBits.h"
#include "ITandHints.h"
#include "ConditionalExecution.h"
#include <stdint.h>

void MOVTT1(uint32_t instruction);
void executeMOVT(uint32_t Rd, uint32_t immediate);

#endif // MOVT_H
