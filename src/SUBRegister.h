#ifndef SUBRegister_H
#define SUBRegister_H

#include "ARMRegisters.h"
#include "getBits.h"
#include "StatusRegisters.h"
#include <stdint.h>
#include "ModifiedImmediateConstant.h"

void SUBRegisterToRegisterT1(uint32_t instruction);
void executeSUBRegister(uint32_t Rn, uint32_t Rd, uint32_t Rm, uint32_t S);

#endif // SUBRegister_H
