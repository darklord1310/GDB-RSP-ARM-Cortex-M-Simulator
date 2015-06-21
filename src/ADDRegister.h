#ifndef ADDRegister_H
#define ADDRegister_H

#include "ARMRegisters.h"
#include "getBits.h"
#include "StatusRegisters.h"
#include <stdint.h>
#include "ModifiedImmediateConstant.h"
#include "ADDSPRegister.h"

void ADDRegisterToRegisterT1(uint32_t instruction);
void ADDRegisterToRegisterT2(uint32_t instruction);
void executeADDRegister(uint32_t Rn, uint32_t Rd, uint32_t Rm, uint32_t S);

#endif // ADDRegister_H
