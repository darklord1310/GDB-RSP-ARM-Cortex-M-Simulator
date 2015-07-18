#ifndef TSTRegister_H
#define TSTRegister_H


#include <stdint.h>


void TSTRegisterT1(uint32_t instruction);
void executeTSTRegister(uint32_t Rn, uint32_t Rm);

#endif // TSTRegister_H
