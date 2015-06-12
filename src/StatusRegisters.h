#ifndef StatusRegisters_H
#define StatusRegisters_H

#include "getBits.h"
#include "getMask.h"

unsigned int StatusRegisters;
typedef enum { ZERO, CARRY, OVERFLOW, NEGATIVE} FlagType;

int checkFlag(int flagType);
void setFlag(int flagType);
void initStatusRegister();

#endif // StatusRegisters_H
