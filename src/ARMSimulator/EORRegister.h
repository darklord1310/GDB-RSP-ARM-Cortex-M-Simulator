#ifndef EORRegister_H
#define LEORRegister_H


#include <stdint.h>

void EORRegisterT1(uint32_t instruction);
void executeEORRegister(uint32_t Rm, uint32_t Rdn, uint32_t S, uint32_t shiftType);

#endif // EORRegister_H
