#ifndef CLZ_H
#define CLZ_H

#include <stdint.h>

void CLZT1(uint32_t instruction);
void executeCLZ(uint32_t Rm, uint32_t Rd);

uint32_t highestSetBit(uint32_t value);

#endif // CLZ_H
