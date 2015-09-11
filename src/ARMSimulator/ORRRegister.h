#ifndef ORRegister_H
#define ORRegister_H


#include <stdint.h>

void ORRRegisterT1(uint32_t instruction);
void ORRRegisterT2(uint32_t instruction);
void executeORRRegister(uint32_t Rm, uint32_t Rd, uint32_t Rn, uint32_t S, uint32_t shiftType, uint32_t shiftImmediate);

#endif // ORRegister_H
