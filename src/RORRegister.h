#ifndef RORRegister_H
#define RORRegister_H
  
#include <stdint.h>

void RORRegisterT1(uint32_t instruction);
void executeRORRegister(uint32_t Rd, uint32_t Rn, uint32_t Rm, uint32_t S);

#endif // RORRegister_H
