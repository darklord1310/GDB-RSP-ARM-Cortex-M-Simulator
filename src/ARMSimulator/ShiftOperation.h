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


#ifndef ShiftOperation_H
#define ShiftOperation_H

typedef enum {OMITTED,LSL,LSR,ASR,RRX,ROR} SRType;


#include <stdint.h>

int determineShiftOperation(int shiftType, uint32_t shiftAmount);
uint32_t executeShiftOperation(int shiftType, uint32_t shiftAmount, uint32_t valueToShift, uint32_t S);
uint32_t executeLSR(uint32_t shiftAmount, uint32_t valueToShift, uint32_t S);
uint32_t executeLSL(uint32_t shiftAmount, uint32_t valueToShift, uint32_t S);
uint32_t executeASR(uint32_t shiftAmount, uint32_t valueToShift, uint32_t S);
uint32_t executeROR(uint32_t shiftAmount, uint32_t valueToShift, uint32_t S);
uint32_t executeRRX(uint32_t valueToShift, uint32_t S);

#endif // ShiftOperation_H
