#include "ADDSPImmediate.h"
#include "ITandHints.h"
#include "StatusRegisters.h"
#include "ARMRegisters.h"
#include "getAndSetBits.h"
#include "getMask.h"
#include "ModifiedImmediateConstant.h"
#include "ConditionalExecution.h"
#include "MemoryBlock.h"
#include <stdio.h>


/*Add SP with Immediate Encoding T1
    ADD<c> <Rd>,SP,#<imm8>
      
  31 30 29 28 27 26 25 24 23 22 21 20 19 18 17 16 15 14 13 12 11 10 9 8 7 6 5 4 3 2 1 0
  |1  0  1  0| 1|    Rd  |           imm8        |                unused               |

  setflags = FALSE
  
where:
            S            If present, specifies that the instruction updates the flags. Otherwise, the instruction does not
                         update the flags.
                         
            <c><q>       See Standard assembler syntax fields on page A6-7.
            
            <Rd>         Specifies the destination register. If <Rd> is omitted, this register is SP.
            
            <const>      Specifies the immediate value to be added to the value obtained from <Rn>. Allowed values
                         are multiples of 4 in the range 0-1020 for encoding T1, multiples of 4 in the range 0-508 for
                         encoding T2 and any value in the range 0-4095 for encoding T4. See Modified immediate
                         constants in Thumb instructions on page A5-15 for the range of allowed values for encoding
                         T3.
                         
            When both 32-bit encodings are available for an instruction, encoding T3 is preferred to
            encoding T4 (if encoding T4 is required, use the ADDW syntax).
            
            The pre-UAL syntax ADD<c>S is equivalent to ADDS<c>.
*/
void ADDSPImmediateT1(uint32_t instruction)
{
  uint32_t Rd = getBits(instruction,26,24);
  uint32_t imm8 = getBits(instruction,23,16);
  
  if(inITBlock())
  {
    if( checkCondition(cond) )
      coreReg[Rd] = coreReg[SP] + imm8;
    
    shiftITState();
  }
  else
    coreReg[Rd] = coreReg[SP] + imm8;
  
}





/*Add SP with Immediate Encoding T2
    ADD<c> SP,SP,#<imm7>
      
  31 30 29 28 27 26 25 24 23 22 21 20 19 18 17 16 15 14 13 12 11 10 9 8 7 6 5 4 3 2 1 0
  |1  0  1  1| 0  0  0  0| 0|         imm7       |                unused               |

  setflags = FALSE
  
where:
            S            If present, specifies that the instruction updates the flags. Otherwise, the instruction does not
                         update the flags.
                         
            <c><q>       See Standard assembler syntax fields on page A6-7.
            
            <Rd>         Specifies the destination register. If <Rd> is omitted, this register is SP.
            
            <const>      Specifies the immediate value to be added to the value obtained from <Rn>. Allowed values
                         are multiples of 4 in the range 0-1020 for encoding T1, multiples of 4 in the range 0-508 for
                         encoding T2 and any value in the range 0-4095 for encoding T4. See Modified immediate
                         constants in Thumb instructions on page A5-15 for the range of allowed values for encoding
                         T3.
                         
            When both 32-bit encodings are available for an instruction, encoding T3 is preferred to
            encoding T4 (if encoding T4 is required, use the ADDW syntax).
            
            The pre-UAL syntax ADD<c>S is equivalent to ADDS<c>.
*/
void ADDSPImmediateT2(uint32_t instruction)
{
  uint32_t imm7 = getBits(instruction,22,16);  
    
  coreReg[SP] = coreReg[SP] + imm7;
}
