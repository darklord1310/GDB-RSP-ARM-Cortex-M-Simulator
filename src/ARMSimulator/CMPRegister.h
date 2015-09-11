#ifndef CMPRegister_H
#define CMPRegister_H

#include <stdint.h>

void CMPRegisterT1(uint32_t instruction);
void CMPRegisterT2(uint32_t instruction);
void CMPRegisterT3(uint32_t instruction);
void executeCMPRegister(uint32_t Rm, uint32_t Rn, uint32_t shiftType, uint32_t shiftImmediate);

#endif // CMPRegister_H
