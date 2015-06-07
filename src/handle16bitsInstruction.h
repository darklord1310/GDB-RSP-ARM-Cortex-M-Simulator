#ifndef handle16bitsInstruction_H
#define handle16bitsInstruction_H

#include "getMask.h"
#include "getBits.h"

void handleOpcode1Equal00(unsigned int instruction);
void handleOpcode1Equal01(unsigned int instruction);
void handleOpcode1Equal10(unsigned int instruction);
void handleOpcode1Equal11(unsigned int instruction);

#endif // handle16bitsInstruction_H
