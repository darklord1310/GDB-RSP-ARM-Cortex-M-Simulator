#ifndef LSLImmediate_H
#define LSLImmediate_H


#include "ARMRegisters.h"
#include "getAndSetBits.h"
#include "StatusRegisters.h"
#include <stdint.h>
#include "MOVRegister.h"
#include "ITandHints.h"
#include "ConditionalExecution.h"

void LSLImmediateT1(uint32_t instruction);
void executeLSLImmediate(uint32_t immediate, uint32_t Rm, uint32_t Rd, uint32_t S);

#endif // LSLImmediate_H
