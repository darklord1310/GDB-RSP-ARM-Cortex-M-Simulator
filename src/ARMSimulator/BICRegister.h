#ifndef BICRegister_H
#define BICRegister_H

#include <stdint.h>


void BICRegisterT1(uint32_t instruction);
void BICRegisterT2(uint32_t instruction);
void executeBICRegister(uint32_t Rm, uint32_t Rd, uint32_t Rn, uint32_t S, uint32_t shiftType, uint32_t shiftImmediate);

#endif // MVNRegister_H
