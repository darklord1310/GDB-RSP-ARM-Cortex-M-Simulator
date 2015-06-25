#include "ARMSimulator.h"
#include <stdio.h>
#include <assert.h>
#include <stdint.h>


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




/*  This function will categorize all the 16bits instructions and differentiate them into the groups shown below
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
void Categorize16bitsThumbInstruction(uint32_t instruction)
{
  uint32_t opcode2;
  uint32_t opcode1 = getBits(instruction, 31, 26);
  
	assert(opcode1 < 58);         // because maximum opcode is 111001 which is 57, so cannot exceed 57
  
  if( opcode1 < 16)
  {
    opcode2 = getBits(instruction,29,25);
    (*Thumb16Opcode00XXXX[opcode2])(instruction);
  }
  //else if(opcode1 == 0b010000)


}


void ARMSimulator(uint32_t instruction)
{
  //coreReg = initCoreRegister();
  //initStatusRegister();
  //initThumb16bitsOpcode00XXX();
  
  int check = is32or16instruction(instruction);

  if(check == INSTRUCTION16bits)
  {
    Categorize16bitsThumbInstruction(instruction);
  }
  
  
}



void printRegister()
{
  int i;
  for(i = 0; i < 15; i++)
  {
    printf("r%d : %x\n", i, coreReg->reg[i].data);
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
}




