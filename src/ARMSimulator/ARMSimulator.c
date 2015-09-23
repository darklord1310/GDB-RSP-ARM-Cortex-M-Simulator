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



#include "ARMSimulator.h"
#include <stdio.h>
#include <assert.h>
#include <stdint.h>
#include "getAndSetBits.h"
#include "getMask.h"
#include "StatusRegisters.h"
#include "ARMRegisters.h"
#include "Thumb16bitsTable.h"
#include "Thumb32bitsTable.h"
#include "ConditionalExecution.h"
#include "MemoryBlock.h"
#include "ErrorSignal.h"
#include "ADDSPImmediate.h"
#include "ADR.h"


void initializeSimulator()
{
  initCoreRegister();
  initializeAllTable();
  resetMemoryBlock();
  resetVectorTableAddress();
}

void initializeAllTable()
{
  //16bits
  initThumb16bitsOpcode00XXXX();
  initThumb16bitsOpcode010000();
  initThumb16bitsOpcode010001();
  initThumb16bitsOpcode1011XX();
  initThumb16LoadStoreSingleData();
  initThumb16bitsOpcode1101XX();

  //32bits
  initThumb32bitsDataProcessingPlainImmediate();
  initThumb32bitsDataProcessingModifiedImmediate();
  initThumb32bitsDataProcessingShiftedRegister();
  initThumb32bitsMoveRegisterAndImmediateShift();
  initThumb32bitsDataProcessingRegister();
  initThumb32bitsBranchesAndMiscellaneousControl();
  initThumb32bitsHintInstructions();
  initThumb32bitsLoadWord();
  initThumb32bitsMultiplyAccumulate();
  initThumb32bitsLongMultiplyAccumulateDivide();
  initThumb32bitsLoadStoreMultiple();
  initThumb32StoreSingleDataItem();
  initThumb32LoadByteMemoryHints();
  initThumb32bitsLoadStoreDualTableBranch();
  initThumb32Table();
}


/*  This function is to check the instruction is 32 bits or 16 bits
 *
 *  hw1[15:11]
 *        0b11100 Thumb 16-bit unconditional branch instruction, defined in all Thumb architectures.
 *        0bxxxxx Thumb 16-bit instructions.
 *        0b111xx Thumb 32-bit instructions, defined in Thumb-2, see Instruction encoding for 32-bit
 *
 *  Return : INSTRUCTION32bits if 32 bits
 *           INSTRUCTION16bits if 16 bits
 *
 */
int is32or16instruction(uint32_t instruction)
{
  if( getBits(instruction, 31, 29) == 0b111 )                 // if first 3 bits are 111, it is possible to be a 32bits instruction
  {                                                           // further checking is needed
    if( getBits(instruction, 28, 27) == 0b00)
      return INSTRUCTION16bits;
    else
      return INSTRUCTION32bits;
	}
  else
      return INSTRUCTION16bits;
}




/*  This function will categorize all the 16bits instructions and execute them based on their groups shown below
 *  There are total 77 16bits instructions
 *  15  14  13  12  11  10  9   8   7   6   5   4   3   2   1   0
 *  |                   |
 *          op1
 *
 *  Check opcode 1 first, then branch out
 *
 *  opcode 1
 *    00xxxx   --->  ShiftAddSubtractMoveCompare
 *    010000   --->  Data Processing
 *    010001   --->  SpecialDataInstructionAndBranchExchange
 *    01001x   --->  LoadFromLiteralPool
 *    0101xx   --->  LoadOrStoreSingleData
 *    011xxx   ___|
 *    100xxx   ___|
 *    10100x   --->  GeneratePCRelativeAddress
 *    10101x   --->  GenerateSPRelativeAddress
 *    1011xx   --->  Miscellaneous16bitsInstruction
 *    11000x   --->  StoreMultipleRegisters
 *    11001x   --->  LoadMultipleRegisters
 *    1101xx   --->  ConditionalBranch
 *    11100x   --->  UnconditionalBranch
 */
void armSimulate16(uint32_t instruction)
{
  uint32_t opcode1 = getBits(instruction, 31, 26);

  assert(opcode1 < 58);         // because maximum opcode is 111001 which is 57, so cannot exceed 57

  executeInstructionFrom16bitsTable(opcode1,instruction);

}


void armSimulate32(uint32_t instruction)
{
  uint32_t op1 = getBits(instruction,28,27);
  uint32_t op2 = getBits(instruction,26,20);
  uint32_t op = getBits(instruction,15,15);
  uint32_t opcode = ( ( (op1 << 7) | op2 ) << 1 ) | op;

  (*Thumb32Table[opcode])(instruction);
}


void executeDataProcessingModifiedImmediate(uint32_t instruction)
{
  uint32_t op = getBits(instruction,24,20);
  uint32_t Rn = getBits(instruction,19,16);
  uint32_t Rd = getBits(instruction,11,8);
  uint32_t opcode = (((op << 4) | Rn ) << 4) | Rd;

  (*Thumb32DataProcessingModifiedImmediate[opcode])(instruction);
}


void executeDataProcessingPlainImmediate(uint32_t instruction)
{
  uint32_t op = getBits(instruction,24,20);
  uint32_t Rn = getBits(instruction,19,16);
  uint32_t opcode = (op << 4) | Rn ;

  (*Thumb32DataProcessingPlainImmediate[opcode])(instruction);
}


void executeDataProcessingShiftedRegister(uint32_t instruction)
{
  uint32_t op = getBits(instruction,24,21);
  uint32_t Rn = getBits(instruction,19,16);
  uint32_t Rd = getBits(instruction,11,8);
  uint32_t S = getBits(instruction,20,20);
  uint32_t opcode = ((((op << 4) | Rn ) << 4) | Rd) << 1 | S;

  (*Thumb32DataProcessingShiftedRegister[opcode])(instruction);
}


void executeMoveRegisterAndImmediateShifts(uint32_t instruction)
{
  uint32_t type = getBits(instruction, 5, 4);
  uint32_t imm2 = getBits(instruction, 7, 6);
  uint32_t imm3 = getBits(instruction, 14, 12);
  uint32_t shiftImm = imm3 << 2 | imm2;
  uint32_t opcode = type << 5 | shiftImm;

  (*Thumb32MoveRegisterAndImmediateShift[opcode])(instruction);
}


void executeDataProcessingRegister(uint32_t instruction)
{
  uint32_t op1 = getBits(instruction,23,20);
  uint32_t op2 = getBits(instruction,7,4);
  uint32_t opcode = (op1 << 4) | op2;

  (*Thumb32DataProcessingRegister[opcode])(instruction);
}

void executeBranchesAndMiscellaneousControl(uint32_t instruction)
{
  uint32_t op1 = getBits(instruction, 26, 20);
  uint32_t op2 = getBits(instruction, 14, 12);
  uint32_t opcode = (op2 << 7) | op1;

  (*Thumb32BranchesAndMiscellaneousControl[opcode])(instruction);
}

void executeHintInstructions(uint32_t instruction)
{
  uint32_t op1 = getBits(instruction, 10, 8);
  uint32_t op2 = getBits(instruction, 7, 0);
  uint32_t opcode = (op1 << 7) | op2;

  (*Thumb32HintInstructions[opcode])();
}


void executeLoadWord(uint32_t instruction)
{
  uint32_t op1 = getBits(instruction,24,23);
  uint32_t Rn = getBits(instruction,19,16);
  uint32_t op2 = getBits(instruction,11,6);
  uint32_t opcode = (((op1 << 6) | op2 ) << 4) | Rn;

  (*Thumb32LoadWord[opcode])(instruction);
}


void executeMultiplyAccumulate(uint32_t instruction)
{
  uint32_t op1 = getBits(instruction,22,20);
  uint32_t op2 = getBits(instruction,5,4);
  uint32_t Ra = getBits(instruction,15,12);
  uint32_t opcode = (((op1 << 2) | op2 ) << 4) | Ra;

  (*Thumb32MultiplyAccumulate[opcode])(instruction);
}



void executeLongMultiplyAccumulateDivide(uint32_t instruction)
{
  uint32_t op1 = getBits(instruction,22,20);
  uint32_t op2 = getBits(instruction,7,4);
  uint32_t opcode = (op1 << 4) | op2;

  (*Thumb32LongMultiplyAccumulateDivide[opcode])(instruction);
}



void executeLoadStoreMultiple(uint32_t instruction)
{
  uint32_t op = getBits(instruction,24,23);
  uint32_t L = getBits(instruction,20,20);
  uint32_t Rn = getBits(instruction,19,16);
  uint32_t W = getBits(instruction,21,21);
  uint32_t WRn = (W << 4) | Rn;
  uint32_t opcode = ( ( (op << 1) | L) << 5) | WRn;
  
  (*Thumb32LoadStoreMultiple[opcode])(instruction);
  
}


void executeStoreSingleDataItem(uint32_t instruction)
{
  uint32_t op1 = getBits(instruction,23,21);
  uint32_t op2 = getBits(instruction,11,6);
  uint32_t opcode = (op1 << 6) | op2;
  
  (*Thumb32StoreSingleDataItem[opcode])(instruction);
}


void executeLoadByteMemoryHints(uint32_t instruction)
{
  uint32_t op1 = getBits(instruction,24,23);
  uint32_t Rn = getBits(instruction,19,16);
  uint32_t Rt = getBits(instruction,15,12);
  uint32_t op2 = getBits(instruction,11,6);
  uint32_t opcode = (((((op1 << 6) | op2) << 4) | Rn ) << 4) | Rt;

  (*Thumb32LoadByteMemoryHints[opcode])(instruction);
}


void executeLoadStoreDualTableBranch(uint32_t instruction)
{
  uint32_t op1 = getBits(instruction,24,23);
  uint32_t op3 = getBits(instruction,7,4);
  uint32_t op2 = getBits(instruction,21,20);
  uint32_t opcode = (((op1 << 2) | op2) << 4) | op3;

  (*Thumb32LoadStoreDualTableBranch[opcode])(instruction);
}



void executeInstructionFrom16bitsTable(uint32_t opcode1, uint32_t instruction)
{
  uint32_t opcode2;

  if( opcode1 <= 0b001111)                              //Shift (immediate), add, subtract, move, and compare
  {
    opcode2 = getBits(instruction,29,25);
    (*Thumb16Opcode00XXXX[opcode2])(instruction);
  }
  else if(opcode1 == 0b010000)                          //Data processing
  {
    opcode2 = getBits(instruction,25,22);
    (*Thumb16Opcode010000[opcode2])(instruction);
  }
  else if(opcode1 == 0b010001)                          //Special data instructions and branch and exchange
  {
    opcode2 = getBits(instruction,25,22);
    (*Thumb16Opcode010001[opcode2])(instruction);
  }
  else if(opcode1 == 0b010010 || opcode1 == 0b010011)   //Load from Literal Pool
  {
    LDRLiteralT1(instruction);
  }
  else if(opcode1 <= 0b100111)                          //Load/store single data item
  {
    opcode2 = getBits(instruction,31,25);
    (*Thumb16LoadStoreSingleData[opcode2])(instruction);
  }
  else if(opcode1 == 0b101000 || opcode1 == 0b101001)   //Generate PC-relative address
  {
    ADRT1(instruction);
  }
  else if(opcode1 == 0b101010 || opcode1 == 0b101011)   //Generate SP-relative address
    ADDSPImmediateT1(instruction);
  else if(opcode1 <= 0b101111)                          //Miscellaneous 16-bit instructions
  {
    opcode2 = getBits(instruction,27,21);
    (*Thumb16Opcode1011XX[opcode2])(instruction);
  }
  else if(opcode1 == 0b110001 || opcode1 == 0b110000)   //Store Multiple Registers
  {
    STMRegisterT1(instruction);
  }
  else if(opcode1 == 0b110010 || opcode1 == 0b110011)   //Load Multiple Registers
  {
    LDMRegisterT1(instruction);
  }
  else if(opcode1 <= 0b110111)                          //Conditional branch, and supervisor call
  {
    opcode2 = getBits(instruction,27,24);
    (*Thumb16Opcode1101XX[opcode2])(instruction);
  }
  else if(opcode1 == 0b111000 || opcode1 == 0b111001)   //Unconditional branch
  {
    UnconditionalBranchT1(instruction);
  }
}




void ARMSimulator(uint32_t instruction)
{
  int check = is32or16instruction(instruction);

  if(check == INSTRUCTION16bits)
  {
    armSimulate16(instruction);
  }
  else
  {
    armSimulate32(instruction);
  }
}


uint32_t retrieveInstructionFromMemory()
{
  uint32_t instructionRetrieved = ((short int)memoryBlock[virtualMemToPhysicalMem(coreReg[PC])]) << 16 |
                                  ((short int)memoryBlock[virtualMemToPhysicalMem(coreReg[PC] + 1)]) << 24;

  int check = is32or16instruction(instructionRetrieved);

  if(check == INSTRUCTION16bits)
    return instructionRetrieved;
  else
  {
    uint32_t lower16bits = ((short int)memoryBlock[virtualMemToPhysicalMem(coreReg[PC] + 2)]) |
                           ((short int)memoryBlock[virtualMemToPhysicalMem(coreReg[PC] + 3)]) << 8;
    instructionRetrieved = instructionRetrieved | lower16bits;

    return instructionRetrieved;
  }
}



void armStep()
{
  uint32_t instruction;

  instruction = retrieveInstructionFromMemory();                  //read the instruction from ROM
  int check = is32or16instruction(instruction);                   //check the instruction is 16 or 32 bits

  if(check == INSTRUCTION16bits)                                  //execute 16 or 32 bits instruction
    armSimulate16(instruction);
  else
    armSimulate32(instruction);

}



//this function is only used for testing purposes
void printRegister()
{
  int i;
  for(i = 0; i < 15; i++)
  {
    printf("r%d : %x\n", i, coreReg[i]);
  }

  if( isCarry() )
    printf("C : %d\n", 1);
  else
    printf("C : %d\n", 0);

  if( isNegative() )
    printf("N : %d\n", 1);
  else
    printf("N : %d\n", 0);

  if( isOverflow() )
    printf("OV : %d\n", 1);
  else
    printf("OV : %d\n", 0);

  if( isZero() )
    printf("Z : %d\n", 1);
  else
    printf("Z : %d\n", 0);

  printf("xPSR: %x\n", coreReg[xPSR]);
}


//this function is only used for testing purposes only
void writeInstructionToMemoryGivenByAddress(uint32_t instruction, uint32_t address)
{
  int check = is32or16instruction(instruction);

  if(check == INSTRUCTION16bits)
  {
    memoryBlock[virtualMemToPhysicalMem(address) ] = getBits(instruction,23,16);
    memoryBlock[virtualMemToPhysicalMem(address+1) ] = getBits(instruction,31,24);
  }
  else
  {
    memoryBlock[virtualMemToPhysicalMem(address) ] = getBits(instruction,23,16);
    memoryBlock[virtualMemToPhysicalMem(address + 1) ] = getBits(instruction,31,24);
    memoryBlock[virtualMemToPhysicalMem(address + 2) ] = getBits(instruction,7,0);
    memoryBlock[virtualMemToPhysicalMem(address + 3) ] = getBits(instruction,15,8);
  }

}
