#ifndef ORRegister_H
#define ORRegister_H


#include <stdint.h>

void ORRRegisterT1(uint32_t instruction);
void executeORRRegister(uint32_t Rm, uint32_t Rdn, uint32_t S, uint32_t shiftType);

#endif // ORRegister_H
