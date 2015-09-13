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



#ifndef ARMSimulator_H
#define ARMSimulator_H

#include <stdint.h>

typedef enum { INSTRUCTION32bits, INSTRUCTION16bits} instructionType;

int is32or16instruction(uint32_t instruction);
void executeInstructionFrom16bitsTable(uint32_t opcode1, uint32_t instruction);
void armSimulate16(uint32_t instruction);
void armSimulate32(uint32_t instruction);
void initializeAllTable();
void initializeSimulator();
void ARMSimulator(uint32_t instruction);
void armStep();
uint32_t retrieveInstructionFromMemory();
void writeInstructionToMemoryGivenByAddress(uint32_t instruction, uint32_t address);
void executeDataProcessingModifiedImmediate(uint32_t instruction);
void executeDataProcessingPlainImmediate(uint32_t instruction);
void executeDataProcessingShiftedRegister(uint32_t instruction);
void executeMoveRegisterAndImmediateShifts(uint32_t instruction);
void executeDataProcessingRegister(uint32_t instruction);
void executeLoadWord(uint32_t instruction);
void executeMultiplyAccumulate(uint32_t instruction);
void executeLongMultiplyAccumulateDivide(uint32_t instruction);
void executeLoadStoreMultiple(uint32_t instruction);

#endif // ARMSimulator_H
