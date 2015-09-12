#include "UnconditionalAndConditionalBranch.h"
#include "ARMRegisters.h"
#include "getAndSetBits.h"
#include "StatusRegisters.h"
#include "ModifiedImmediateConstant.h"
#include "ITandHints.h"
#include "ConditionalExecution.h"
#include "ErrorSignal.h"
#include <stdio.h>
#include "CException.h"
#include "SVC.h"


/*Branch causes a branch to a target address.

    B<c> <label> Outside or last in IT block

   31 30 29 28 27 26 25 24 23 22 21 20 19 18 17 16 15 14 13 12 11 10 9 8 7 6 5 4 3 2 1 0
  |1  1   1  0  0|             imm11              |                unused               |

where:
          <c><q>        See Standard assembler syntax fields on page A6-7.

          Note
                        Encodings T1 and T3 are conditional in their own right, and do not require an IT instruction
                        to make them conditional.
                        For encodings T1 and T3, <c> is not allowed to be AL or omitted. The 4-bit encoding of the
                        condition is placed in the instruction and not in a preceding IT instruction, and the
                        instruction is not allowed to be in an IT block. As a result, encodings T1 and T2 are never
                        both available to the assembler, nor are encodings T3 and T4.

          <label>       Specifies the label of the instruction that is to be branched to. The assembler calculates the
                        required value of the offset from the PC value of the B instruction to this label, then selects
                        an encoding that will set imm32 to that offset.

          Allowed offsets are even numbers in the range -256 to 254 for encoding T1, -2048 to 2046
          for encoding T2, -1048576 to 1048574 for encoding T3, and -16777216 to 16777214 for
          encoding T4.
*/
void UnconditionalBranchT1(uint32_t instruction)
{
  uint32_t imm11 = getBits(instruction,26,16);
  uint32_t imm11AfterShift = imm11 << 1;

  if( !( inITBlock() ) || isLastInITBlock())
  {
    if( inITBlock() )
    {
      if( checkCondition(cond) )
      {
        uint32_t afterSignExtend = signExtend(imm11AfterShift, 12);
        coreReg[PC] = coreReg[PC] + afterSignExtend + 4;
      }
      shiftITState();
    }
    else
    {
      uint32_t afterSignExtend = signExtend(imm11AfterShift, 12);
      coreReg[PC] = coreReg[PC] + afterSignExtend + 4;
    }
  }
  else
  {
    placePCtoVectorTable(UsageFault);
    Throw(UsageFault);
  }
}



/*Branch causes a branch to a target address.

    B<c> <label>         Not allowed in IT block.

   31 30 29 28 27 26 25 24 23 22 21 20 19 18 17 16 15 14 13 12 11 10 9 8 7 6 5 4 3 2 1 0
  |1  1   0  1|    cond   |          imm8         |                unused               |

where:
          <c><q>        See Standard assembler syntax fields on page A6-7.

          Note
                        Encodings T1 and T3 are conditional in their own right, and do not require an IT instruction
                        to make them conditional.
                        For encodings T1 and T3, <c> is not allowed to be AL or omitted. The 4-bit encoding of the
                        condition is placed in the instruction and not in a preceding IT instruction, and the
                        instruction is not allowed to be in an IT block. As a result, encodings T1 and T2 are never
                        both available to the assembler, nor are encodings T3 and T4.

          <label>       Specifies the label of the instruction that is to be branched to. The assembler calculates the
                        required value of the offset from the PC value of the B instruction to this label, then selects
                        an encoding that will set imm32 to that offset.

          Allowed offsets are even numbers in the range -256 to 254 for encoding T1, -2048 to 2046
          for encoding T2, -1048576 to 1048574 for encoding T3, and -16777216 to 16777214 for
          encoding T4.
*/
void ConditionalBranchT1(uint32_t instruction)
{
  uint32_t imm8 = getBits(instruction,23,16);
  uint32_t imm8AfterShift = imm8 << 1;
  uint32_t condition = getBits(instruction,27,24);

  if( !( inITBlock() ) && condition != 0b1110 )
  {
    if(condition != 0b1111 )
    {
      if( checkCondition(condition) )
      {
        uint32_t afterSignExtend = signExtend(imm8AfterShift, 9);
        coreReg[PC] = coreReg[PC] + afterSignExtend + 4;
      }
    }
    else
      SVC(instruction);
  }
  else
  {
    placePCtoVectorTable(UsageFault);
    Throw(UsageFault);
  }
}




/* This function will sign extend the value passing in and sign extend the number to 32 bits
 *
 * Input:
 *          value           the value that is going to be sign extend to 32bits
 *          numberOfBits    number of bits of the value
 *
 * Return
 *          the value after sign extend
 */
uint32_t signExtend(uint32_t value, int numberOfBits)
{
  if( getBits(value, numberOfBits-1, numberOfBits-1) == 1)        //if the sign bit of the value is 1, then set all the bits infront of it up to bit31 by 1
    value = setBits(value, 0xffffffff, 31, numberOfBits);
  else
    value = setBits(value, 0x00000000, 31, numberOfBits);         //if the sign bit of the value is 0, then set all the bits infront of it up to bit31 by 0

  return value;
}
