#ifndef ASRRegister_H
#define ASRRegister_H

#include "ARMRegisters.h"
#include "getAndSetBits.h"
#include "StatusRegisters.h"
#include <stdint.h>

void ASRRegisterToRegister16bitsT1(uint32_t instruction);

#endif // ASRRegister_H
