#include "InstructionDecoding.h"
#include <stdio.h>


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
int is32or16instruction(unsigned int instruction)
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





/*  This function will categorize all the 16bits instructions and differentiate them into the groups shown below
 *  15  14  13  12  11  10  9   8   7   6   5   4   3   2   1   0
 *  |                   |   
 *          op1       
 *
 *  Check opcode 1 first, then branch out
 *
 *  opcode 1
 *    00xxxx   --->  ShiftAddSubctractMoveCompare
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
int Categorize16bitsThumbInstruction(unsigned int instruction)
{
  unsigned int opcode1 = getBits(instruction, 31, 26);
	
  if( opcode1 < 16)
    return SHITFADDSUBTRACTMOVECOMPARE;
  else if( opcode1 == 0b010000)
    return DATAPROCESSING;
  else if( opcode1 == 0b010001)
    return SPECIALDATAINSTRUCTIONANDBRANCHEXCHANGE;
  else if( opcode1 < 20)
    return LOADFROMLITERALPOOL;
  else if( opcode1 < 40)
    return LOADORSTORESINGLEDATA;
  else if( opcode1 < 42)
    return GENERATEPCRELATIVEADDRESS;
  else if( opcode1 < 44)
    return GENERATESPRELATIVEADDRESS;
  else if( opcode1 < 48)
    return MISCELLANEOUS16BITSINSTRUCTION;
  else if( opcode1 < 50)
    return STOREMULTIPLEREGISTERS;
  else if( opcode1 < 52)
    return LOADMULTIPLEREGISTERS;
  else if( opcode1 < 56)
    return CONDITIONALBRANCH;
  else if( opcode1 < 58)
    return UNCONDITIONALBRANCH;
  
}











