#ifndef SignedAndUnsignedExtend_H
#define SignedAndUnsignedExtend_H

#include <stdint.h>

void UXTHT1(uint32_t instruction);
void UXTBT1(uint32_t instruction);
void SXTHT1(uint32_t instruction);
void SXTBT1(uint32_t instruction);

void SXTHT2(uint32_t instruction);
void UXTHT2(uint32_t instruction);

#endif // SignedAndUnsignedExtend_H
