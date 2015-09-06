#ifndef ANDRegister_H
#define ANDRegister_H

#include <stdint.h>

void ANDRegisterT1(uint32_t instruction);
void ANDRegisterT2(uint32_t instruction);
void executeANDRegister(uint32_t Rm, uint32_t Rd, uint32_t Rn, uint32_t S, uint32_t shiftType, uint32_t shiftImmediate);

#endif // ANDRegister_H
