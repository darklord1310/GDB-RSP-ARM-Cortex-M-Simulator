#ifndef SignedUnsignedLongMultiplyDivide_H
#define SignedUnsignedLongMultiplyDivide_H


#include <stdint.h>


void SMULLT1(uint32_t instruction);
void SDIVT1(uint32_t instruction);
void UMULLT1(uint32_t instruction);
void UDIVT1(uint32_t instruction);
void SMLALT1(uint32_t instruction);
void UMLALT1(uint32_t instruction);

#endif // SignedUnsignedLongMultiplyDivide_H
