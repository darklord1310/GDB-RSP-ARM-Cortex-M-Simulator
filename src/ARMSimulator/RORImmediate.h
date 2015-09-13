#ifndef RORImmediate_H
#define RORImmediate_H

#include <stdint.h>

void RORImmediateT1(uint32_t instruction);
void executeRORImmediate(uint32_t imm5, uint32_t Rm, uint32_t Rd, uint32_t S);

#endif // RORImmediate_H
