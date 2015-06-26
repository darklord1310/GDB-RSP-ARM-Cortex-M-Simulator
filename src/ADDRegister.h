#ifndef ADDRegister_H
#define ADDRegister_H


#include <stdint.h>


void ADDRegisterToRegisterT1(uint32_t instruction);
void ADDRegisterToRegisterT2(uint32_t instruction);
void executeADDRegister(uint32_t Rn, uint32_t Rd, uint32_t Rm, uint32_t S);

#endif // ADDRegister_H
