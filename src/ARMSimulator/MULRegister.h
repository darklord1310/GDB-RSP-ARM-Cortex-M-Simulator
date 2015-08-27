#ifndef MULRegister_H
#define MULRegister_H

#include <stdint.h>


void MULRegisterT1(uint32_t instruction);
void executeMULRegister(uint32_t Rm, uint32_t Rd, uint32_t Rn, uint32_t S);

#endif // MULRegister_H
