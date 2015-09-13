/*  
    Program Name       : GDB RSP and ARM Simulator
    Author             : Wong Yan Yin, Jackson Teh Ka Sing 
    Copyright (C) 2015 TARUC

    This file is part of GDB RSP and ARM Simulator.

    GDB RSP and ARM Simulator is free software, you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    GDB RSP and ARM Simulator is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY, without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with GDB RSP and ARM Simulator.  If not, see <http://www.gnu.org/licenses/>.

*/



#ifndef StatusRegisters_H
#define StatusRegisters_H

#define OVERFLOW_FLAG_POS 28
#define maskOffBit(target, bitNo) (target & ~(1 << bitNo))
#define shiftRightMsbBitToBitPosition(value, pos) (((value) & 0x80000000) >> (31 - pos))                         
                                          
#define setOverflow(x) (coreReg[xPSR] = ( maskOffBit(coreReg[xPSR], OVERFLOW_FLAG_POS) | (shiftRightMsbBitToBitPosition(x, OVERFLOW_FLAG_POS)) )  )

#define updateOverflowFlag4Addition(signForValue1,signForValue2,signForResult) (setOverflow(~(signForValue1 ^ signForValue2) | signForResult)


#define updateOverflowFlag4Subtraction(signForValue1,signForValue2,signForResult) (setOverflow((signForValue1 ^ signForValue2) | signForResult)
                  
#include <stdbool.h>
#include <stdint.h>


bool isNegative();
bool isZero();
bool isCarry();
bool isOverflow();
bool isQSet();
void setQFlag();
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
void updateQFlag(int32_t max, int32_t min, int32_t result, int32_t sign);
int inITBlock();
uint32_t getITCond();
void shiftITState();
int isLastInITBlock();



#endif // StatusRegisters_H
