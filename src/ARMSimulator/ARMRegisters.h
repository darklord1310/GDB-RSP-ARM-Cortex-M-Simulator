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


#ifndef ARMRegisters_H
#define ARMRegisters_H


#include <stdint.h>

#define NUM_OF_CORE_Register    18  //register start from R0 - R15, R0 to R12 are GPR, R13 is StackPointer, R14 is LinkRegister, R15 is ProgramCounter
#define SP                      13
#define LR                      14
#define PC                      15
#define xPSR                    16
#define fPSCR                   17
#define AIRCR                   0  // Application Interrupt and Reset Control Register
#define CCR                     1  // Configuration and Control Register
#define NUM_OF_FPUD_Register    16
#define NUM_OF_FPUS_Register    32
#define NUM_OF_SYS_Register     2


uint32_t coreReg[NUM_OF_CORE_Register];
uint32_t systemReg[NUM_OF_SYS_Register];
uint32_t fpuSinglePrecision[NUM_OF_FPUS_Register];
uint64_t fpuDoublePrecision[NUM_OF_FPUD_Register];


void initCoreRegister();
void writeSinglePrecision(int regNum, uint32_t valueToWrite);
void writeDoublePrecision(int regNum, uint64_t valueToWrite);
void writeToCoreRegisters(int regNum, uint32_t valueToWrite);


#endif // ARMRegisters_H
