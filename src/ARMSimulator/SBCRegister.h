#ifndef SBCRegister_H
#define SBCRegister_H


#include <stdint.h>


void SBCRegisterT1(uint32_t instruction);
void SBCRegisterT2(uint32_t instruction);
void executeSBCRegister(uint32_t Rm, uint32_t Rd, uint32_t Rn, uint32_t S, uint32_t shiftType, uint32_t shiftImmediate);

#endif // SBCRegister_H
