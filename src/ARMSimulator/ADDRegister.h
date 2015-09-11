#ifndef ADDRegister_H
#define ADDRegister_H


#include <stdint.h>


void ADDRegisterToRegisterT1(uint32_t instruction);
void ADDRegisterToRegisterT2(uint32_t instruction);
void ADDRegisterT3(uint32_t instruction);
void executeADDRegister(uint32_t Rm, uint32_t Rd, uint32_t Rn, uint32_t S, uint32_t shiftType, uint32_t shiftImmediate);

#endif // ADDRegister_H
