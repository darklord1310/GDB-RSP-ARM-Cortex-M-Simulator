/*  
    GDB RSP and ARM Simulator

    Copyright (C) 2015 Wong Yan Yin, <jet_wong@hotmail.com>,
    Jackson Teh Ka Sing, <jackson_dmc69@hotmail.com>

    This file is part of GDB RSP and ARM Simulator.

    This program is free software, you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY, without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with This program.  If not, see <http://www.gnu.org/licenses/>.
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
