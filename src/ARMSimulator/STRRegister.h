#ifndef STRRegister_H
#define STRRegister_H

#include <stdint.h>

void STRRegisterT1(uint32_t instruction);
void STRHRegisterT1(uint32_t instruction);
void STRBRegisterT1(uint32_t instruction);
void STMRegisterT1(uint32_t instruction);
void STMRegisterT2(uint32_t instruction);
void STMDB(uint32_t instruction);
int getBitCount(uint32_t value, int bitSize);
void writeMultipleRegisterToMemory(uint32_t address, uint32_t registerList, uint32_t sizeOfRegisterList, uint32_t writeBack, uint32_t Rn);


#endif // STRRegister_H
