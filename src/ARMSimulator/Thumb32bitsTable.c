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


#include "Thumb32bitsTable.h"
#include "getMask.h"
#include "getAndSetBits.h"
#include <string.h>
#include <stdio.h>
#include <math.h>
#include <stdarg.h>

void invalidInstruction(uint32_t instruction)
{
  printf("invalid instruction!\n");
}


//get to know which the base 10bits opcode from the given string
void findBaseOpcode(char *string, BitsInfo *bitsInfo)
{
  uint32_t dummy = 0;
  int sizeOfString = strlen(string) - 1;
  int i = 0, numberOfbitsSegment = 0;

  while(sizeOfString >= 0)
  {
    if(string[sizeOfString] == 'X')
      dummy = setBits(dummy,0b0,i,i);
    else if(string[sizeOfString] == '0')
      dummy = setBits(dummy,0b0,i,i);
    else if(string[sizeOfString] == '1')
      dummy = setBits(dummy,0b1,i,i);
    
    sizeOfString--;
    i++;
  }
  
  (*bitsInfo).baseOpcode = dummy;
}


void getBitsInfo(char *string, BitsInfo *bitsInfo)
{
  int i = 0, numberOfXbits = 0;
  int sizeOfString = strlen(string) - 1;
  int index = sizeOfString;
  
  while(sizeOfString >= 0)
  {
    if(string[sizeOfString] == 'X')
    {
      (*bitsInfo).PositionOfbitX[i] = index-sizeOfString;
      numberOfXbits++;
      i++;
    }
    sizeOfString--;
  }
  
  (*bitsInfo).noOfDontCareBits = numberOfXbits;
  (*bitsInfo).PositionOfbitX[i] = -1;    //to indicate that it is the end
}


TableException *createTableException(int numberOfExceptions, ...)
{
  va_list ap;
  int i = 0;
  static TableException exception[MAXIMUM_NO_OF_TABLE_EXCEPTIONS + 1];         //the reason to plus 1 for the maximum number of table exceptions is to indicate the 
                                                                               //end of looping
                                                                               //eg : The loop will go on forever until mask with 0 value is found, so if the maximum number of 
                                                                               //     table exceptions is 31 then we need to add 1 more to store the end of loop
                                                                               //     indicator
  
  va_start(ap, numberOfExceptions);
  
  for(i = 0; i < numberOfExceptions; i++)                               // loop according the number of table exception passing in, and update the table 
  {                                                                     // exception array with the mask and exceptionValues respectively
    exception[i].mask = va_arg(ap, uint32_t);
    exception[i].exceptionValue = va_arg(ap, uint32_t);
  }
  
  exception[i].mask = -1;
  exception[i].exceptionValue = -1;
  
  va_end(ap);
  return exception;
}



int determineTableException(TableException *tableException, uint32_t opcode)
{
  int i = 0;
  
  while(tableException[i].mask != -1)
  {
    if( (opcode & tableException[i].mask) == tableException[i].exceptionValue)
      return 1;
    i++;
  }
  
  return 0;
}


void tabulateTable(char *string, void (*table[])(uint32_t), void (*function)(uint32_t) , TableException *tableException)
{
  BitsInfo bitsInfo;
  int i = 0, j = 0;
  
  findBaseOpcode(string, &bitsInfo);        //find the base opcode from the string passing in
  getBitsInfo(string, &bitsInfo);           //get the neccessary bits info from the string
  
  for(j = 0; j < pow(2,bitsInfo.noOfDontCareBits); j++)  //fill up the dont care bits and merge it with the baseOpcode and point the table to the function
  {
    while(bitsInfo.PositionOfbitX[i] != -1)
    {
      bitsInfo.baseOpcode = setBits(bitsInfo.baseOpcode, getBits(j,i,i), bitsInfo.PositionOfbitX[i], bitsInfo.PositionOfbitX[i]);
      i++;
    }
    
    if( determineTableException(tableException, bitsInfo.baseOpcode) == 0)
      table[bitsInfo.baseOpcode] = function;

    i = 0;
  }  
}


void initThumb32Table()
{
  // tabulateTable("XXXXXXXXXX", Thumb32Table, invalidInstruction , createTableException(NO_EXCEPTION) );   
  tabulateTable("0100XX0XXX", Thumb32Table, executeLoadStoreMultiple , createTableException(NO_EXCEPTION) );
  tabulateTable("0100XX1XXX", Thumb32Table, executeLoadStoreDualTableBranch , createTableException(NO_EXCEPTION) );
  tabulateTable("0101XXXXXX", Thumb32Table, executeDataProcessingShiftedRegister  , createTableException(NO_EXCEPTION) );
  tabulateTable("011XXXXXXX", Thumb32Table, executeCoprocessorInstructions  , createTableException(NO_EXCEPTION) );
  tabulateTable("10X0XXXXX0", Thumb32Table, executeDataProcessingModifiedImmediate , createTableException(NO_EXCEPTION) );
  tabulateTable("10X1XXXXX0", Thumb32Table, executeDataProcessingPlainImmediate , createTableException(NO_EXCEPTION) );
  tabulateTable("10XXXXXXX1", Thumb32Table, executeBranchesAndMiscellaneousControl , createTableException(NO_EXCEPTION) );
  tabulateTable("11000XXX0X", Thumb32Table, executeStoreSingleDataItem , createTableException(NO_EXCEPTION) );
  tabulateTable("1100XX001X", Thumb32Table, executeLoadByteMemoryHints , createTableException(NO_EXCEPTION) );
  tabulateTable("1100XX011X", Thumb32Table, executeLoadHalfword , createTableException(NO_EXCEPTION) );
  tabulateTable("1100XX101X", Thumb32Table, executeLoadWord , createTableException(NO_EXCEPTION) );
  tabulateTable("11010XXXXX", Thumb32Table, executeDataProcessingRegister , createTableException(NO_EXCEPTION) );
  tabulateTable("110110XXXX", Thumb32Table, executeMultiplyAccumulate , createTableException(NO_EXCEPTION) );
  tabulateTable("110111XXXX", Thumb32Table, executeLongMultiplyAccumulateDivide , createTableException(NO_EXCEPTION) );
  tabulateTable("111XXXXXXX", Thumb32Table, executeCoprocessorInstructions  , createTableException(NO_EXCEPTION) );
}



void initThumb32bitsLoadStoreMultiple()
{
  // tabulateTable("XXXXXXXX", Thumb32LoadStoreMultiple, invalidInstruction ,  createTableException(NO_EXCEPTION) );  
  tabulateTable("010XXXXX", Thumb32LoadStoreMultiple, STMRegisterT2 ,  createTableException(NO_EXCEPTION) );
  tabulateTable("011XXXXX", Thumb32LoadStoreMultiple, LDMRegisterT2 ,  createTableException(1,0b00011111, 0b00011101) );
  tabulateTable("01111101", Thumb32LoadStoreMultiple, POPT2 ,          createTableException(NO_EXCEPTION) );
  tabulateTable("100XXXXX", Thumb32LoadStoreMultiple, STMDB ,          createTableException(1,0b00011111, 0b00011101) );
  tabulateTable("10011101", Thumb32LoadStoreMultiple, PUSHT2 ,         createTableException(NO_EXCEPTION) );
  tabulateTable("101XXXXX", Thumb32LoadStoreMultiple, LDMDB ,          createTableException(NO_EXCEPTION) );
}


void initThumb32bitsLoadStoreDualTableBranch()
{
  // tabulateTable("XXXXXXXX", Thumb32LoadStoreDualTableBranch, invalidInstruction ,  createTableException(NO_EXCEPTION) );
  tabulateTable("0X10XXXX", Thumb32LoadStoreDualTableBranch, STRDImmediate ,  createTableException(NO_EXCEPTION) );
  tabulateTable("1XX0XXXX", Thumb32LoadStoreDualTableBranch, STRDImmediate ,  createTableException(NO_EXCEPTION) );
  tabulateTable("0X11XXXX", Thumb32LoadStoreDualTableBranch, LDRDImmediate ,  createTableException(NO_EXCEPTION) );
  tabulateTable("1XX1XXXX", Thumb32LoadStoreDualTableBranch, LDRDImmediate ,  createTableException(NO_EXCEPTION) );
}


void initThumb32bitsDataProcessingShiftedRegister()
{
  // tabulateTable("XXXXXXXXXXXXX", Thumb32DataProcessingShiftedRegister, invalidInstruction , createTableException(NO_EXCEPTION) );
  tabulateTable("0000XXXXXXXXX", Thumb32DataProcessingShiftedRegister, ANDRegisterT2 , createTableException(1, 0b0000000011110, 0b1110) );
  tabulateTable("0000XXXX11111", Thumb32DataProcessingShiftedRegister, TSTRegisterT2 , createTableException(NO_EXCEPTION, NO_EXCEPTION) );
  tabulateTable("0001XXXXXXXXX", Thumb32DataProcessingShiftedRegister, BICRegisterT2 , createTableException(NO_EXCEPTION, NO_EXCEPTION) );
  tabulateTable("0010XXXXXXXXX", Thumb32DataProcessingShiftedRegister, ORRRegisterT2 , createTableException(1,0b0000111100000, 0b111100000) );
  tabulateTable("00101111XXXXX", Thumb32DataProcessingShiftedRegister, executeMoveRegisterAndImmediateShifts , createTableException(NO_EXCEPTION) );
  tabulateTable("0011XXXXXXXXX", Thumb32DataProcessingShiftedRegister, ORNRegisterT1 , createTableException(1,0b0000111100000, 0b111100000) );
  tabulateTable("00111111XXXXX", Thumb32DataProcessingShiftedRegister, MVNRegisterT2 , createTableException(NO_EXCEPTION) );
  tabulateTable("0100XXXXXXXXX", Thumb32DataProcessingShiftedRegister, EORRegisterT2 , createTableException(1,0b0000111100000, 0b111100000) );
  tabulateTable("0100XXXX11111", Thumb32DataProcessingShiftedRegister, TEQRegisterT1 , createTableException(NO_EXCEPTION) );
  tabulateTable("1000XXXXXXXXX", Thumb32DataProcessingShiftedRegister, ADDRegisterT3 , createTableException(1,0b0000111100000, 0b111100000) );
  tabulateTable("1000XXXX11111", Thumb32DataProcessingShiftedRegister, CMNRegisterT2 , createTableException(NO_EXCEPTION) );
  tabulateTable("1010XXXXXXXXX", Thumb32DataProcessingShiftedRegister, ADCRegisterT2 , createTableException(NO_EXCEPTION) );
  tabulateTable("1011XXXXXXXXX", Thumb32DataProcessingShiftedRegister, SBCRegisterT2 , createTableException(NO_EXCEPTION) );
  tabulateTable("1101XXXXXXXXX", Thumb32DataProcessingShiftedRegister, SUBRegisterT2 , createTableException(1,0b0000111100000, 0b111100000) );
  tabulateTable("1101XXXX11111", Thumb32DataProcessingShiftedRegister, CMPRegisterT3 , createTableException(NO_EXCEPTION) );
  tabulateTable("1110XXXXXXXXX", Thumb32DataProcessingShiftedRegister, RSBRegisterT1 , createTableException(NO_EXCEPTION) );
}


void initThumb32bitsCoprocessorInstructions()
{
  tabulateTable("000100X101X", Thumb32CoprocessorInstructions, VMOVBetweenCoreRegAndDoubleFpuReg , createTableException(NO_EXCEPTION) );
  tabulateTable("000101X101X", Thumb32CoprocessorInstructions, VMOVBetweenCoreRegAndDoubleFpuReg , createTableException(NO_EXCEPTION) );
  tabulateTable("10XXX01101X", Thumb32CoprocessorInstructions, executeFloatingPoint32bitsTransfer , createTableException(NO_EXCEPTION) );
  tabulateTable("10XXX11101X", Thumb32CoprocessorInstructions, executeFloatingPoint32bitsTransfer , createTableException(NO_EXCEPTION) );
}

void initThumb32bitsMoveRegisterAndImmediateShift()
{
  // tabulateTable("XXXXXXX", Thumb32MoveRegisterAndImmediateShift, invalidInstruction , createTableException(NO_EXCEPTION) );
  tabulateTable("0000000", Thumb32MoveRegisterAndImmediateShift, MOVRegisterT3 , createTableException(NO_EXCEPTION) );
  tabulateTable("00XXXXX", Thumb32MoveRegisterAndImmediateShift, LSLImmediateT2 , createTableException(1,0b0011111, 0b00000) );
  tabulateTable("01XXXXX", Thumb32MoveRegisterAndImmediateShift, LSRImmediateT2 , createTableException(NO_EXCEPTION) );
  tabulateTable("10XXXXX", Thumb32MoveRegisterAndImmediateShift, ASRImmediateT2 , createTableException(NO_EXCEPTION) );
  tabulateTable("1100000", Thumb32MoveRegisterAndImmediateShift, RRXT1 , createTableException(NO_EXCEPTION, NO_EXCEPTION) );
  tabulateTable("11XXXXX", Thumb32MoveRegisterAndImmediateShift, RORImmediateT1 , createTableException(1,0b0011111, 0b00000) );
}


void initThumb32bitsDataProcessingModifiedImmediate()
{
  // tabulateTable("XXXXXXXXXXXXX", Thumb32DataProcessingModifiedImmediate, invalidInstruction , createTableException(NO_EXCEPTION) );
  tabulateTable("0000XXXXXXXXX", Thumb32DataProcessingModifiedImmediate, ANDImmediateT1 , createTableException(1,0b0000000001111, 0b1111) );
  tabulateTable("0000XXXXX1111", Thumb32DataProcessingModifiedImmediate, TSTImmediateT1 , createTableException(NO_EXCEPTION) );
  tabulateTable("0001XXXXXXXXX", Thumb32DataProcessingModifiedImmediate, BICImmediateT1 , createTableException(NO_EXCEPTION) );
  tabulateTable("0010XXXXXXXXX", Thumb32DataProcessingModifiedImmediate, ORRImmediateT1 , createTableException(1,0b0000011110000, 0b11110000) );
  tabulateTable("0010X1111XXXX", Thumb32DataProcessingModifiedImmediate, MOVImmediateT2 , createTableException(NO_EXCEPTION) );
  tabulateTable("0011XXXXXXXXX", Thumb32DataProcessingModifiedImmediate, ORNImmediateT1 , createTableException(1,0b0000011110000, 0b11110000) );
  tabulateTable("0011X1111XXXX", Thumb32DataProcessingModifiedImmediate, MVNImmediateT1 , createTableException(NO_EXCEPTION) );
  tabulateTable("0100XXXXXXXXX", Thumb32DataProcessingModifiedImmediate, EORImmediateT1 , createTableException(1,0b0000000001111, 0b1111) );
  tabulateTable("0100XXXXX1111", Thumb32DataProcessingModifiedImmediate, TEQImmediateT1 , createTableException(NO_EXCEPTION) );
  tabulateTable("1000XXXXXXXXX", Thumb32DataProcessingModifiedImmediate, ADDImmediateT3 , createTableException(1,0b0000000001111, 0b1111) );
  tabulateTable("1000XXXXX1111", Thumb32DataProcessingModifiedImmediate, CMNImmediateT1 , createTableException(NO_EXCEPTION) );
  tabulateTable("1010XXXXXXXXX", Thumb32DataProcessingModifiedImmediate, ADCImmediateT1 , createTableException(NO_EXCEPTION) );
  tabulateTable("1011XXXXXXXXX", Thumb32DataProcessingModifiedImmediate, SBCImmediateT1 , createTableException(NO_EXCEPTION) );
  tabulateTable("1101XXXXXXXXX", Thumb32DataProcessingModifiedImmediate, SUBImmediateT3 , createTableException(1,0b0000000001111, 0b1111) );
  tabulateTable("1101XXXXX1111", Thumb32DataProcessingModifiedImmediate, CMPImmediateT2 , createTableException(NO_EXCEPTION) );
  tabulateTable("1110XXXXXXXXX", Thumb32DataProcessingModifiedImmediate, RSBImmediateT2 , createTableException(NO_EXCEPTION) );
}


void initThumb32bitsDataProcessingPlainImmediate()
{
  // tabulateTable("XXXXXXXXX", Thumb32DataProcessingPlainImmediate, invalidInstruction , createTableException(NO_EXCEPTION) );
  tabulateTable("00000XXXX", Thumb32DataProcessingPlainImmediate, ADDImmediateT4 , createTableException(1,0b000001111, 0b1111) );
  tabulateTable("000001111", Thumb32DataProcessingPlainImmediate, ADRT3 , createTableException(NO_EXCEPTION) );
  tabulateTable("00100XXXX", Thumb32DataProcessingPlainImmediate, MOVImmediateT3 , createTableException(NO_EXCEPTION) );
  tabulateTable("01010XXXX", Thumb32DataProcessingPlainImmediate, SUBImmediateT4 , createTableException(1,0b000001111, 0b1111) );
  tabulateTable("010101111", Thumb32DataProcessingPlainImmediate, ADRT2 , createTableException(NO_EXCEPTION) );
  tabulateTable("01100XXXX", Thumb32DataProcessingPlainImmediate, MOVTT1 , createTableException(NO_EXCEPTION) );
  tabulateTable("100X0XXXX", Thumb32DataProcessingPlainImmediate, SSATT1 , createTableException(NO_EXCEPTION) );
  tabulateTable("10100XXXX", Thumb32DataProcessingPlainImmediate, SBFXT1 , createTableException(NO_EXCEPTION) );
  tabulateTable("10110XXXX", Thumb32DataProcessingPlainImmediate, BFIT1 , createTableException(1,0b000001111, 0b1111) );
  tabulateTable("101101111", Thumb32DataProcessingPlainImmediate, BFCT1 , createTableException(NO_EXCEPTION) );
  tabulateTable("110X0XXXX", Thumb32DataProcessingPlainImmediate, USATT1 , createTableException(NO_EXCEPTION) );
  tabulateTable("11100XXXX", Thumb32DataProcessingPlainImmediate, UBFXT1 , createTableException(NO_EXCEPTION) );
}


void initThumb32bitsBranchesAndMiscellaneousControl()
{
  // tabulateTable("XXXXXXXXXX", Thumb32BranchesAndMiscellaneousControl, invalidInstruction , createTableException(NO_EXCEPTION) );
  tabulateTable("0X0XXXXXXX", Thumb32BranchesAndMiscellaneousControl, ConditionalBranchT2 , createTableException(1,0b0000111000, 0b111000) );
  tabulateTable("0X00111010", Thumb32BranchesAndMiscellaneousControl, executeHintInstructions , createTableException(NO_EXCEPTION) );
  tabulateTable("0X1XXXXXXX", Thumb32BranchesAndMiscellaneousControl, UnconditionalBranchT2 , createTableException(NO_EXCEPTION) );
  tabulateTable("1X1XXXXXXX", Thumb32BranchesAndMiscellaneousControl, BLT1 , createTableException(NO_EXCEPTION) );
}


void initThumb32StoreSingleDataItem()
{
  // tabulateTable("XXXXXXXXX", Thumb32StoreSingleDataItem, invalidInstruction ,  createTableException(NO_EXCEPTION) );
  tabulateTable("100XXXXXX", Thumb32StoreSingleDataItem, STRBImmediateT2 ,  createTableException(NO_EXCEPTION) );
  tabulateTable("0001XXXXX", Thumb32StoreSingleDataItem, STRBImmediateT3 ,  createTableException(NO_EXCEPTION) );
  tabulateTable("0000XXXXX", Thumb32StoreSingleDataItem, STRBRegisterT2 ,  createTableException(NO_EXCEPTION) );
  tabulateTable("101XXXXXX", Thumb32StoreSingleDataItem, STRHImmediateT2 ,  createTableException(NO_EXCEPTION) );
  tabulateTable("0011XXXXX", Thumb32StoreSingleDataItem, STRHImmediateT3 ,  createTableException(NO_EXCEPTION) );
  tabulateTable("0010XXXXX", Thumb32StoreSingleDataItem, STRHRegisterT2 ,  createTableException(NO_EXCEPTION) );
  tabulateTable("110XXXXXX", Thumb32StoreSingleDataItem, STRImmediateT3 ,  createTableException(NO_EXCEPTION) );
  tabulateTable("0101XXXXX", Thumb32StoreSingleDataItem, STRImmediateT4 ,  createTableException(NO_EXCEPTION) );
  tabulateTable("0100XXXXX", Thumb32StoreSingleDataItem, STRRegisterT2 ,  createTableException(NO_EXCEPTION) );
}


void initThumb32LoadByteMemoryHints()
{
  // tabulateTable("XXXXXXXXXXXXXXXX", Thumb32LoadByteMemoryHints, invalidInstruction ,  createTableException(NO_EXCEPTION) );
  tabulateTable("01XXXXXXXXXXXXXX", Thumb32LoadByteMemoryHints, LDRBImmediateT2 ,  createTableException(2,0b0000000000001111, 0b00001111, 0b0000000011110000, 0b11110000) );
  tabulateTable("001XX1XXXXXXXXXX", Thumb32LoadByteMemoryHints, LDRBImmediateT3 ,  createTableException(1,0b0000000011110000, 0b11110000) );
  tabulateTable("001100XXXXXXXXXX", Thumb32LoadByteMemoryHints, LDRBImmediateT3 ,  createTableException(2,0b0000000000001111, 0b00001111, 0b0000000011110000, 0b11110000) );
  tabulateTable("001110XXXXXXXXXX", Thumb32LoadByteMemoryHints, LDRBT ,  createTableException(1,0b0000000011110000, 0b11110000) );
  tabulateTable("0XXXXXXX1111XXXX", Thumb32LoadByteMemoryHints, LDRBLiteral ,  createTableException(1,0b0000000000001111, 0b1111) );
  tabulateTable("00000000XXXXXXXX", Thumb32LoadByteMemoryHints, LDRBRegisterT2 ,  createTableException(2,0b0000000000001111, 0b1111, 0b0000000011110000, 0b11110000) );
  tabulateTable("11XXXXXXXXXXXXXX", Thumb32LoadByteMemoryHints, LDRSBImmediateT1 ,  createTableException(2,0b0000000000001111, 0b00001111, 0b0000000011110000, 0b11110000) );
  tabulateTable("101XX1XXXXXXXXXX", Thumb32LoadByteMemoryHints, LDRSBImmediateT2 ,  createTableException(1,0b0000000011110000, 0b11110000) );
  tabulateTable("101100XXXXXXXXXX", Thumb32LoadByteMemoryHints, LDRSBImmediateT2 ,  createTableException(2,0b0000000000001111, 0b00001111, 0b0000000011110000, 0b11110000) );
  tabulateTable("101110XXXXXXXXXX", Thumb32LoadByteMemoryHints, LDRSBT ,  createTableException(1, 0b0000000011110000, 0b11110000) );
  tabulateTable("1XXXXXXX1111XXXX", Thumb32LoadByteMemoryHints, LDRSBLiteral ,  createTableException(1,0b0000000000001111, 0b1111) );
  tabulateTable("10000000XXXXXXXX", Thumb32LoadByteMemoryHints, LDRSBRegisterT2 ,  createTableException(2,0b0000000000001111, 0b00001111, 0b0000000011110000, 0b11110000) );  
}


void initThumb32bitsLoadHalfword()
{
  // tabulateTable("XXXXXXXXXXXXXXXX", Thumb32LoadHalfword, invalidInstruction , createTableException(NO_EXCEPTION) );
  tabulateTable("01XXXXXXXXXXXXXX", Thumb32LoadHalfword, LDRHImmediateT2 , createTableException(2, 0b0000000000001111, 0b1111, 0b0000000011110000, 0b11110000) );
  tabulateTable("001XX1XXXXXXXXXX", Thumb32LoadHalfword, LDRHImmediateT3 , createTableException(2, 0b0000000000001111, 0b1111, 0b0000000011110000, 0b11110000) );
  tabulateTable("001100XXXXXXXXXX", Thumb32LoadHalfword, LDRHImmediateT3 , createTableException(2, 0b0000000000001111, 0b1111, 0b0000000011110000, 0b11110000) );
  tabulateTable("001110XXXXXXXXXX", Thumb32LoadHalfword, LDRHT , createTableException(2, 0b0000000000001111, 0b1111, 0b0000000011110000, 0b11110000) );
  tabulateTable("0XXXXXXX1111XXXX", Thumb32LoadHalfword, LDRHLiteral , createTableException(1, 0b0000000000001111, 0b1111) );
  tabulateTable("00000000XXXXXXXX", Thumb32LoadHalfword, LDRHRegisterT2 , createTableException(2, 0b0000000000001111, 0b1111, 0b0000000011110000, 0b11110000) );
  tabulateTable("11XXXXXXXXXXXXXX", Thumb32LoadHalfword, LDRSHImmediateT1 , createTableException(2, 0b0000000000001111, 0b1111, 0b0000000011110000, 0b11110000) );
  tabulateTable("101XX1XXXXXXXXXX", Thumb32LoadHalfword, LDRSHImmediateT2 , createTableException(2, 0b0000000000001111, 0b1111, 0b0000000011110000, 0b11110000) );
  tabulateTable("101100XXXXXXXXXX", Thumb32LoadHalfword, LDRSHImmediateT2 , createTableException(2, 0b0000000000001111, 0b1111, 0b0000000011110000, 0b11110000) );
  tabulateTable("101110XXXXXXXXXX", Thumb32LoadHalfword, LDRSHT , createTableException(2, 0b0000000000001111, 0b1111, 0b0000000011110000, 0b11110000) );
  tabulateTable("1XXXXXXX1111XXXX", Thumb32LoadHalfword, LDRSHLiteral , createTableException(1, 0b0000000000001111, 0b1111) );
  tabulateTable("10000000XXXXXXXX", Thumb32LoadHalfword, LDRSHRegisterT2 , createTableException(2, 0b0000000000001111, 0b1111, 0b0000000011110000, 0b11110000) );
}


void initThumb32bitsLoadWord()
{
  // tabulateTable("XXXXXXXXXXXX", Thumb32LoadWord, invalidInstruction , createTableException(NO_EXCEPTION) );
  tabulateTable("01XXXXXXXXXX", Thumb32LoadWord, LDRImmediateT3 , createTableException(1,0b000000001111, 0b1111) );
  tabulateTable("001XX1XXXXXX", Thumb32LoadWord, LDRImmediateT4 , createTableException(1,0b000000001111, 0b1111) );
  tabulateTable("001100XXXXXX", Thumb32LoadWord, LDRImmediateT4 , createTableException(1,0b000000001111, 0b1111) );
  tabulateTable("001110XXXXXX", Thumb32LoadWord, LDRTT1 , createTableException(1,0b000000001111, 0b1111) );
  tabulateTable("00000000XXXX", Thumb32LoadWord, LDRRegisterT2 , createTableException(1,0b000000001111, 0b1111) );
  tabulateTable("0XXXXXXX1111", Thumb32LoadWord, LDRLiteralT2 , createTableException(NO_EXCEPTION) );
}


void initThumb32bitsDataProcessingRegister()
{
  // tabulateTable("XXXXXXXX", Thumb32DataProcessingRegister, invalidInstruction , createTableException(NO_EXCEPTION) );
  tabulateTable("000X0000", Thumb32DataProcessingRegister, LSLRegisterT2 , createTableException(NO_EXCEPTION) );
  tabulateTable("001X0000", Thumb32DataProcessingRegister, LSRRegisterT2 , createTableException(NO_EXCEPTION) );
  tabulateTable("010X0000", Thumb32DataProcessingRegister, ASRRegisterT2 , createTableException(NO_EXCEPTION) );
  tabulateTable("011X0000", Thumb32DataProcessingRegister, RORRegisterT2 , createTableException(NO_EXCEPTION) );
  tabulateTable("00001XXX", Thumb32DataProcessingRegister, SXTHT2 , createTableException(NO_EXCEPTION) );
  tabulateTable("00011XXX", Thumb32DataProcessingRegister, UXTHT2 , createTableException(NO_EXCEPTION) );
  tabulateTable("01001XXX", Thumb32DataProcessingRegister, SXTBT2 , createTableException(NO_EXCEPTION) );
  tabulateTable("01011XXX", Thumb32DataProcessingRegister, UXTBT2 , createTableException(NO_EXCEPTION) );
  
  // Miscellaneous operations
  tabulateTable("10011000", Thumb32DataProcessingRegister, REVT2 , createTableException(NO_EXCEPTION) );
  tabulateTable("10011001", Thumb32DataProcessingRegister, REV16T2 , createTableException(NO_EXCEPTION) );
  tabulateTable("10011010", Thumb32DataProcessingRegister, RBITT1 , createTableException(NO_EXCEPTION) );
  tabulateTable("10011011", Thumb32DataProcessingRegister, REVSHT2 , createTableException(NO_EXCEPTION) );
  tabulateTable("10111000", Thumb32DataProcessingRegister, CLZT1 , createTableException(NO_EXCEPTION) );

}



void initThumb32bitsHintInstructions()
{
  // tabulateTable("XXXXXXXXXXX", Thumb32HintInstructions, invalidInstruction , createTableException(NO_EXCEPTION) );
  tabulateTable("00000000000", Thumb32HintInstructions, NOPT2 , createTableException(NO_EXCEPTION) ); 
}



void initThumb32bitsMultiplyAccumulate()
{
  // tabulateTable("XXXXXXXXX", Thumb32MultiplyAccumulate, invalidInstruction , createTableException(NO_EXCEPTION) );
  tabulateTable("000000000", Thumb32MultiplyAccumulate, MLAT1 , createTableException(1, 0b000001111, 0b1111) );
  tabulateTable("000001111", Thumb32MultiplyAccumulate, MULRegisterT2 , createTableException(NO_EXCEPTION) );
  tabulateTable("00001XXXX", Thumb32MultiplyAccumulate, MLST1 , createTableException(NO_EXCEPTION) );
}


void initThumb32bitsLongMultiplyAccumulateDivide()
{
  // tabulateTable("XXXXXXX", Thumb32LongMultiplyAccumulateDivide, invalidInstruction ,  createTableException(NO_EXCEPTION) );    
  tabulateTable("0000000", Thumb32LongMultiplyAccumulateDivide, SMULLT1 ,  createTableException(NO_EXCEPTION) );
  tabulateTable("0011111", Thumb32LongMultiplyAccumulateDivide, SDIVT1 ,  createTableException(NO_EXCEPTION) );
  tabulateTable("0100000", Thumb32LongMultiplyAccumulateDivide, UMULLT1 ,  createTableException(NO_EXCEPTION) );
  tabulateTable("0111111", Thumb32LongMultiplyAccumulateDivide, UDIVT1 ,  createTableException(NO_EXCEPTION) );
  tabulateTable("1000000", Thumb32LongMultiplyAccumulateDivide, SMLALT1 ,  createTableException(NO_EXCEPTION) );
  tabulateTable("1100000", Thumb32LongMultiplyAccumulateDivide, UMLALT1 ,  createTableException(NO_EXCEPTION) );
}



void initFloatingPoint32bitsTransfer()
{
  tabulateTable("00000XX", FloatingPoint32bitsTransfer, VMOVBetweenCoreRegAndfpuSReg ,  createTableException(NO_EXCEPTION) );
  tabulateTable("10000XX", FloatingPoint32bitsTransfer, VMOVBetweenCoreRegAndfpuSReg ,  createTableException(NO_EXCEPTION) );
  tabulateTable("0100X00", FloatingPoint32bitsTransfer, VMOVBetweenScalarAndCoreReg ,  createTableException(NO_EXCEPTION) );
  tabulateTable("1100X00", FloatingPoint32bitsTransfer, VMOVBetweenScalarAndCoreReg ,  createTableException(NO_EXCEPTION) );
  tabulateTable("00111XX", FloatingPoint32bitsTransfer, VMSR ,  createTableException(NO_EXCEPTION) );
  tabulateTable("10111XX", FloatingPoint32bitsTransfer, VMSR ,  createTableException(NO_EXCEPTION) );
}





















