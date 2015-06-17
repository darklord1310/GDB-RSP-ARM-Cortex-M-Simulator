#ifndef StatusRegisters_H
#define StatusRegisters_H

#include "getBits.h"
#include "getMask.h"
#include <stdbool.h>
#include <stdint.h>

uint32_t StatusRegisters;

bool isNegative();
bool isZero();
bool isCarry();
bool isOverflow();
void setOverflowFlag();
void setZeroFlag();
void setNegativeFlag();
void setCarryFlag();
void initStatusRegister();
void updateStatusRegister(uint32_t value);

#endif // StatusRegisters_H
