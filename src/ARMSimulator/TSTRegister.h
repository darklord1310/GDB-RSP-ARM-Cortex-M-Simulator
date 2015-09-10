#ifndef TSTRegister_H
#define TSTRegister_H


#include <stdint.h>


void TSTRegisterT1(uint32_t instruction);
void TSTRegisterT2(uint32_t instruction);
void executeTSTRegister(uint32_t Rn, uint32_t Rm, uint32_t shiftType, uint32_t shiftImmediate);

#endif // TSTRegister_H
