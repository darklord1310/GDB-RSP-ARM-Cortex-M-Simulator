#ifndef LDRRegister_H
#define LDRRegister_H

#include <stdint.h>

void LDRRegisterT1(uint32_t instruction);
void LDRRegisterT2(uint32_t instruction);
void LDRTT1(uint32_t instruction);
void LDRHRegisterT1(uint32_t instruction);
void LDRBRegisterT1(uint32_t instruction);
void LDRSBRegisterT1(uint32_t instruction);
void LDRSHRegisterT1(uint32_t instruction);
void LDMRegisterT1(uint32_t instruction);
void loadMultipleRegisterFromMemory(uint32_t address, uint32_t registerList, uint32_t writeBack, uint32_t Rn, int sizeOfRegisterList);
int determineWriteBack(uint32_t Rn, uint32_t registerList);

#endif // LDRRegister_H
