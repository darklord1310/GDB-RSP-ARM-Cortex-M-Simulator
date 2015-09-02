#ifndef StatusRegisters_H
#define StatusRegisters_H

#define OVERFLOW_FLAG_POS 28
#define maskOffBit(target, bitNo) (target & ~(1 << bitNo))
#define shiftRightMsbBitToBitPosition(value, pos) (((value) & 0x80000000) >> (31 - pos))                         
                                          
#define setOverflow(x) (coreReg[xPSR] = maskOffBit((coreReg[xPSR], OVERFLOW_FLAG_POS) | (shiftRightMsbBitToBitPosition(x, OVERFLOW_FLAG_POS)) )  )

#define updateOverflowFlag4Addition(signForValue1,signForValue2,signForResult) (setOverflow(~(signForValue1 ^ signForValue2) | signForResult)


#define updateOverflowFlag4Subtraction(signForValue1,signForValue2,signForResult) (setOverflow((signForValue1 ^ signForValue2) | signForResult)
                  
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
int isLastInITBlock();
void ALUWritePC(uint32_t address);



#endif // StatusRegisters_H
