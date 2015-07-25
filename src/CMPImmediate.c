#include "CMPImmediate.h"
#include "ARMRegisters.h"
#include "getAndSetBits.h"
#include "StatusRegisters.h"
#include "ModifiedImmediateConstant.h"
#include "ITandHints.h"
#include "ConditionalExecution.h"
#include <stdio.h>

/*Compare Immediate Encoding T1

    CMP<c> <Rn>,#<imm8>
       
   31 30 29 28 27 26 25 24 23 22 21 20 19 18 17 16 15 14 13 12 11 10 9 8 7 6 5 4 3 2 1 0
  |0   0  1| 0 1|   Rn    |         imm8          |                unused               |
  
  where:
          <c><q>      See Standard assembler syntax fields on page A6-7.
          
          <Rn>        Specifies the register that contains the operand. This register is allowed to be the SP.
          
          <const>     Specifies the immediate value to be added to the value obtained from <Rn>. The range of
                      allowed values is 0-255 for encoding T1. See Modified immediate constants in Thumb
                      instructions on page A5-15 for the range of allowed values for encoding T2.
*/
void CMPImmediateT1(uint32_t instruction)
{
  uint32_t imm8 = getBits(instruction, 23 , 16);
  uint32_t Rn = getBits(instruction, 26, 24);

  if(inITBlock())
  {
    if( checkCondition(cond) )
      executeCMP(imm8, Rn );
    
    shiftITState();
  }
  else
    executeCMP(imm8, Rn );
}



/*Compare Immediate Encoding T2

    CMP<c>.W <Rn>,#<const>
       
   31 30 29 28 27 26 25 24 23 22 21 20 19 18 17 16 15 14 13 12 11 10 9 8 7 6 5 4 3 2 1 0
  |1   1  1  1  0|i|  0| 1  1  0  1| 1|     Rn    |0 |  imm3  | 1  1 1 1|     imm8      |
  
  where:
          <c><q>      See Standard assembler syntax fields on page A6-7.
          
          <Rn>        Specifies the register that contains the operand. This register is allowed to be the SP.
          
          <const>     Specifies the immediate value to be added to the value obtained from <Rn>. The range of
                      allowed values is 0-255 for encoding T1. See Modified immediate constants in Thumb
                      instructions on page A5-15 for the range of allowed values for encoding T2.
*/
void CMPImmediateT2(uint32_t instruction)
{
  uint32_t imm8 = getBits(instruction, 7, 0);
  uint32_t imm3 = getBits(instruction, 14, 12);
  uint32_t i = getBits(instruction, 26, 26);
  uint32_t Rn = getBits(instruction, 19, 16);
  uint32_t bit7 = getBits(imm8,7,7);
  
  uint32_t modifiedConstant = ModifyImmediateConstant(i, imm3, bit7, imm8);
  executeCMP(modifiedConstant, Rn );
  
}


/*
  This function will execute the Compare Immediate Instruction for
  both 16bits and 32bits instruction, this function will be share
  among two
  
  Input : value        the immediate 
          Rn           the destination register
  
*/
void executeCMP(uint32_t value, uint32_t Rn )
{
  uint32_t temp = coreReg[Rn] - value;
  
  updateZeroFlag(temp);
  updateCarryFlagSubtraction(coreReg[Rn] , value);
  updateNegativeFlag(temp);
  updateOverflowFlagSubtraction(coreReg[Rn], value, temp);

}






