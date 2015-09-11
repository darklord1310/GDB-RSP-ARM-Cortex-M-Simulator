#ifndef TEQRegister_H
#define TEQRegister_H

#include <stdint.h>

void TEQRegisterT1(uint32_t instruction);
void executeTEQRegister(uint32_t Rm, uint32_t Rn, uint32_t shiftType, uint32_t shiftImmediate);

#endif // TEQRegister_H
