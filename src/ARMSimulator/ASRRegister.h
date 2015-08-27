#ifndef ASRRegister_H
#define ASRRegister_H

#include "ARMRegisters.h"
#include "getAndSetBits.h"
#include "StatusRegisters.h"
#include <stdint.h>

void ASRRegisterToRegisterT1(uint32_t instruction);
void executeASRRegister(uint32_t Rm, uint32_t Rd, uint32_t Rn, uint32_t S);

#endif // ASRRegister_H
