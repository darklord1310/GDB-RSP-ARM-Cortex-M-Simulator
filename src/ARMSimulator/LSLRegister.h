#ifndef LSLRegister_H
#define LSLRegister_H


#include <stdint.h>

void LSLRegisterToRegisterT1(uint32_t instruction);
void executeLSLRegister(uint32_t Rm, uint32_t Rdn, uint32_t S);

#endif // LSLRegister_H
