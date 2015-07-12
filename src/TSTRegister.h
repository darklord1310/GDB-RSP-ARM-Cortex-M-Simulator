#ifndef TSTRegister_H
#define TSTRegister_H


#include <stdint.h>


void TSTRegisterT1(uint32_t instruction);
void executeTSTRegister(uint32_t Rn, uint32_t Rd, uint32_t Rm, uint32_t S);

#endif // TSTRegister_H
