#ifndef ANDRegister_H
#define ANDRegister_H

#include <stdint.h>

void ANDRegisterT1(uint32_t instruction);
void executeANDRegister(uint32_t Rm, uint32_t Rdn, uint32_t S, int shiftOrNoShift);

#endif // ANDRegister_H
