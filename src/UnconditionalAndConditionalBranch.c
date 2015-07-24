#include "UnconditionalAndConditionalBranch.h"
#include "ARMRegisters.h"
#include "getAndSetBits.h"
#include "StatusRegisters.h"
#include "ModifiedImmediateConstant.h"
#include "ITandHints.h"
#include "ConditionalExecution.h"
#include <stdio.h>


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
  uint32_t signExtend = imm11 << 1;

  if( getBits(signExtend, 11,11) == 1)
    signExtend = setBits(signExtend,0b11111111111111111111,31,12);

  coreReg[PC] = coreReg[PC] + signExtend + 4;
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
  uint32_t signExtend = imm8;
  
  if( getBits(imm8, 7,7) == 1)
    signExtend = setBits(signExtend,0b11111111111111111111111,31,8);
  
  printf("signExtend: %x\n", signExtend);
  coreReg[PC] = coreReg[PC] + signExtend;
}



