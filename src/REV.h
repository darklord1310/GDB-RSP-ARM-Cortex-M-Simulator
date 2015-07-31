#ifndef REV_H
#define REV_H

#include <stdint.h>

void REVT1(uint32_t instruction);
void executeREV(uint32_t Rm, uint32_t Rd);
void REV16T1(uint32_t instruction);
void executeREV16(uint32_t Rm, uint32_t Rd);
void REVSHT1(uint32_t instruction);
void executeREVSH(uint32_t Rm, uint32_t Rd);

#endif // REV_H
