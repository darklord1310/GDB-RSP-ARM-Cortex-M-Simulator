#ifndef getAndSetBits_H
#define getAndSetBits_H

#include "getMask.h"
#include <stdint.h>

uint32_t getBits(uint32_t instruction, int higherRange, int lowerRange);
uint32_t setBits(uint32_t setTarget, uint32_t input_value, int higherRange, int lowerRange);

#endif // getAndSetBits_H
