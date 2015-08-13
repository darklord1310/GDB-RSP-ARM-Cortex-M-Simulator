#ifndef MVNRegister_H
#define MVNRegister_H

#include <stdint.h>


void MVNRegisterT1(uint32_t instruction);
void MVNRegisterT2(uint32_t instruction);
void executeMVNRegister(uint32_t Rm, uint32_t Rd, uint32_t S, uint32_t shiftType);

#endif // MVNRegister_H
