#ifndef LSLRegister_H
#define LSLRegister_H

#include "ARMRegisters.h"
#include "getAndSetBits.h"
#include "StatusRegisters.h"
#include <stdint.h>

void LSLRegisterToRegisterT1(uint32_t instruction);

#endif // LSLRegister_H
