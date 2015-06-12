#ifndef StatusRegisters_H
#define StatusRegisters_H

#include "getBits.h"
#include "getMask.h"
#include <stdbool.h>
#include <stdint.h>

uint32_t StatusRegisters;

typedef enum { ZERO, CARRY, OVERFLOW, NEGATIVE} FlagType;

bool isNegative();
bool isZero();
bool isCarry();
bool isOverflow();
void setOverflowFlag();
void setZeroFlag();
void setNegativeFlag();
void setCarryFlag();
void initStatusRegister();

#endif // StatusRegisters_H
