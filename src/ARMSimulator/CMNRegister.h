#ifndef CMNRegister_H
#define CMNRegister_H

#include <stdint.h>

void CMNRegisterT1(uint32_t instruction);
void executeCMNRegister(uint32_t Rm, uint32_t Rn, uint32_t shiftType);

#endif // CMNRegister_H
