#ifndef LSLImmediate_H
#define LSLImmediate_H


#include "ARMRegisters.h"
#include "getBits.h"
#include "StatusRegisters.h"
#include <stdint.h>
#include "MOVRegister.h"

void LSLImmediateT1(uint32_t instruction);
void executeLSLImmediate(uint32_t immediate, uint32_t Rm, uint32_t Rd, uint32_t S);

#endif // LSLImmediate_H
