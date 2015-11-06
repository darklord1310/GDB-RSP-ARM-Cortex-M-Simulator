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
void executeBranchesAndMiscellaneousControl(uint32_t instruction);
void executeHintInstructions(uint32_t instruction);
void executeLoadWord(uint32_t instruction);
void executeMultiplyAccumulate(uint32_t instruction);
void executeLongMultiplyAccumulateDivide(uint32_t instruction);
void executeLoadStoreMultiple(uint32_t instruction);
void executeStoreSingleDataItem(uint32_t instruction);
void executeLoadByteMemoryHints(uint32_t instruction);
void executeLoadStoreDualTableBranch(uint32_t instruction);
void executeLoadHalfword(uint32_t instruction);
void executeCoprocessorInstructions(uint32_t instruction);
void executeCoprocessorInstructions2(uint32_t instruction);
void executeFloatingPoint32bitsTransfer(uint32_t instruction);
void executeFloatingPointDataProcessing(uint32_t instruction);
void executeFloatingPointFPLoadStore(uint32_t instruction);

#endif // ARMSimulator_H
