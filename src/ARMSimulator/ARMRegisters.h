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


#ifndef ARMRegisters_H
#define ARMRegisters_H


#include <stdint.h>

#define NUM_OF_CORE_Register    18  //register start from R0 - R15, R0 to R12 are GPR, R13 is StackPointer, R14 is LinkRegister, R15 is ProgramCounter
#define SP                      13
#define LR                      14
#define PC                      15
#define xPSR                    16
#define fPSCR                   17
#define NUM_OF_FPUD_Register    16
#define NUM_OF_FPUS_Register    32


uint32_t coreReg[NUM_OF_CORE_Register];
uint32_t fpuSinglePrecision[NUM_OF_FPUS_Register];
uint64_t fpuDoublePrecision[NUM_OF_FPUD_Register];


void initCoreRegister();
void writeSinglePrecision(int regNum, uint32_t valueToWrite);
void writeDoublePrecision(int regNum, uint64_t valueToWrite);



#endif // ARMRegisters_H
