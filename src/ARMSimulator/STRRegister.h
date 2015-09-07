#ifndef STRRegister_H
#define STRRegister_H

#include <stdint.h>

void STRRegisterT1(uint32_t instruction);
void STRHRegisterT1(uint32_t instruction);
void STRBRegisterT1(uint32_t instruction);
void STMRegisterT1(uint32_t instruction);
void STMRegisterT2(uint32_t instruction);
void writeMultipleRegisterToMemory(uint32_t address, uint32_t registerList, sizeOfRegisterList, uint32_t writeBack, uint32_t Rn);


#endif // STRRegister_H
