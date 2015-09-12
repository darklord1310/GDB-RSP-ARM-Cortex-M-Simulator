#ifndef LSRRegister_H
#define LSRRegister_H
  
#include <stdint.h>

void LSRRegisterToRegisterT1(uint32_t instruction);
void LSRRegisterT2(uint32_t instruction);
void executeLSRRegister(uint32_t Rm, uint32_t Rd, uint32_t Rn, uint32_t S);

#endif // LSRRegister_H
