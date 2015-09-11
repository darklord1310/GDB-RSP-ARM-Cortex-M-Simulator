#ifndef RSBRegister_H
#define RSBRegister_H

#include "ARMRegisters.h"
#include "getAndSetBits.h"
#include "StatusRegisters.h"
#include <stdint.h>

void RSBRegisterT1(uint32_t instruction);
void executeRSBRegister(uint32_t Rm, uint32_t Rd, uint32_t Rn, uint32_t S, uint32_t shiftType, uint32_t shiftImmediate);

#endif // RSBRegister_H
