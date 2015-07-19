#ifndef SBCRegister_H
#define SBCRegister_H


#include <stdint.h>


void SBCRegisterT1(uint32_t instruction);
void executeSBCRegister(uint32_t Rn, uint32_t Rd, uint32_t Rm, uint32_t S);

#endif // SBCRegister_H
