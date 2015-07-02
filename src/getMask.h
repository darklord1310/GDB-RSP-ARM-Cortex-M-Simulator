#ifndef getMask_H
#define getMask_H

#include <stdint.h>

uint32_t getMaskforSetBits(uint32_t valueToSet, int bitPosition);
uint32_t getMaskforGetBits(int bitPosition);

#endif // getMask_H
