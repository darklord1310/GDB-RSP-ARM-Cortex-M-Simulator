#ifndef LSRRegister_H
#define LSRRegister_H

#include "ARMRegisters.h"
#include "getBits.h"
#include "StatusRegisters.h"
#include <stdint.h>

void LSRRegisterToRegister16bitsT1(uint32_t instruction);

#endif // LSRRegister_H
