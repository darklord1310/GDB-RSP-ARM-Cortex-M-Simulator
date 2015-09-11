#ifndef ORNRegister_H
#define ORNRegister_H

#include <stdint.h>

void ORNRegisterT1(uint32_t instruction);
void executeORNRegister(uint32_t Rm, uint32_t Rd, uint32_t Rn, uint32_t S, uint32_t shiftType, uint32_t shiftImmediate);

#endif // ORNRegister_H
