#ifndef SignedUnsignedLongMultiplyDivide_H
#define SignedUnsignedLongMultiplyDivide_H


#include <stdint.h>
#include <math.h>

void SMULLT1(uint32_t instruction);
void SDIVT1(uint32_t instruction);
void UMULLT1(uint32_t instruction);
void UDIVT1(uint32_t instruction);
void SMLALT1(uint32_t instruction);
void UMLALT1(uint32_t instruction);
long long int convertToUnsigned(uint64_t value, uint32_t numberOfBits);

#endif // SignedUnsignedLongMultiplyDivide_H
