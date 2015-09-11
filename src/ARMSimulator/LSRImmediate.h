#ifndef LSRImmediate_H
#define LSRImmediate_H

#include "ARMRegisters.h"
#include "getAndSetBits.h"
#include "StatusRegisters.h"
#include <stdint.h>
#include "ITandHints.h"
#include "ConditionalExecution.h"

void LSRImmediateT1(uint32_t instruction);
void LSRImmediateT2(uint32_t instruction);
void executeLSRImmediate(uint32_t immediate, uint32_t Rm, uint32_t Rd, uint32_t S);

#endif // LSRImmediate_H
