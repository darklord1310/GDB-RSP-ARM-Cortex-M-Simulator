#ifndef ASRImmediate_H
#define ASRImmediate_H

#include <stdint.h>

void ASRImmediateT1(uint32_t instruction);
void ASRImmediateT2(uint32_t instruction);
void executeASRImmediate(uint32_t imm5, uint32_t Rm, uint32_t Rd, uint32_t S);

#endif // ASRImmediate_H
