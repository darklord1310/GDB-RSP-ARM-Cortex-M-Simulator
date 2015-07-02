#ifndef StatusRegisters_H
#define StatusRegisters_H


#include <stdbool.h>
#include <stdint.h>


bool isNegative();
bool isZero();
bool isCarry();
bool isOverflow();
void setOverflowFlag();
void setZeroFlag();
void setNegativeFlag();
void setCarryFlag();
void resetOverflowFlag();
void resetCarryFlag();
void resetNegativeFlag();
void resetZeroFlag();
void updateZeroFlag(uint32_t value);
void updateNegativeFlag(uint32_t value);
void updateCarryFlagAddition(uint32_t value1, uint32_t value2);
void updateCarryFlagSubtraction(uint32_t value1, uint32_t value2);
void updateOverflowFlagAddition(uint32_t value1, uint32_t value2, uint32_t result);
void updateOverflowFlagSubtraction(uint32_t value1, uint32_t value2, uint32_t result);
int inITBlock();
uint32_t getITCond();
void shiftITState();

#endif // StatusRegisters_H
