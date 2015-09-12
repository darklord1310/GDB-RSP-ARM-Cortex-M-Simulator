#include "SignedAndUnsignedExtend.h"
#include "ITandHints.h"
#include "StatusRegisters.h"
#include "ARMRegisters.h"
#include "getAndSetBits.h"
#include "getMask.h"
#include "ConditionalExecution.h"
#include "UnconditionalAndConditionalBranch.h"
#include "ShiftOperation.h"


/*Signed Extend Halfword Encoding T1
    SXTH<c> <Rd>,<Rm>

  31 30 29 28 27 26 25 24 23 22 21 20 19 18 17 16 15 14 13 12 11 10 9 8 7 6 5 4 3 2 1 0
  |1  0  1  1| 0  0  1  0| 0  0|   Rm   |   Rd   |                unused               |

where:
            <c><q>                See Standard assembler syntax fields on page A6-7.

            <Rd>                  Specifies the destination register.

            <Rm>                  Specifies the register that contains the operand.

            <rotation>            This can be any one of:
                                  • ROR #8.
                                  • ROR #16.
                                  • ROR #24.
                                  • Omitted.

*/
void SXTHT1(uint32_t instruction)
{
  uint32_t Rm = getBits(instruction,21,19);
  uint32_t Rd = getBits(instruction,18,16);

  if(inITBlock())
  {
    if( checkCondition(cond) )
    {
      coreReg[Rd] = signExtend(coreReg[Rm], 16);
    }

    shiftITState();
    coreReg[PC] += 2;
  }
  else
  {
    coreReg[Rd] = signExtend(coreReg[Rm], 16);
    coreReg[PC] += 2;
  }

}




/*Signed Extend Byte Encoding T1
    SXTB<c> <Rd>,<Rm>

  31 30 29 28 27 26 25 24 23 22 21 20 19 18 17 16 15 14 13 12 11 10 9 8 7 6 5 4 3 2 1 0
  |1  0  1  1| 0  0  1  0| 0  1|   Rm   |   Rd   |                unused               |

where:
            <c><q>                See Standard assembler syntax fields on page A6-7.

            <Rd>                  Specifies the destination register.

            <Rm>                  Specifies the register that contains the operand.

            <rotation>            This can be any one of:
                                  • ROR #8.
                                  • ROR #16.
                                  • ROR #24.
                                  • Omitted.

*/
void SXTBT1(uint32_t instruction)
{
  uint32_t Rm = getBits(instruction,21,19);
  uint32_t Rd = getBits(instruction,18,16);

  if(inITBlock())
  {
    if( checkCondition(cond) )
      coreReg[Rd] = signExtend(coreReg[Rm], 8);

    shiftITState();
  }
  else
    coreReg[Rd] = signExtend(coreReg[Rm], 8);

  coreReg[PC] += 2;
}




/*Unsigned Extend Halfword Encoding T1
    UXTH<c> <Rd>,<Rm>

  31 30 29 28 27 26 25 24 23 22 21 20 19 18 17 16 15 14 13 12 11 10 9 8 7 6 5 4 3 2 1 0
  |1  0  1  1| 0  0  1  0| 1  0|   Rm   |   Rd   |                unused               |

where:
            <c><q>                See Standard assembler syntax fields on page A6-7.

            <Rd>                  Specifies the destination register.

            <Rm>                  Specifies the register that contains the operand.

            <rotation>            This can be any one of:
                                  • ROR #8.
                                  • ROR #16.
                                  • ROR #24.
                                  • Omitted.

*/
void UXTHT1(uint32_t instruction)
{
  uint32_t Rm = getBits(instruction,21,19);
  uint32_t Rd = getBits(instruction,18,16);

  if(inITBlock())
  {
    if( checkCondition(cond) )
      coreReg[Rd] = getBits(coreReg[Rm], 15, 0);

    shiftITState();
  }
  else
    coreReg[Rd] = getBits(coreReg[Rm], 15, 0);

  coreReg[PC] += 2;
}




/*Unsigned Extend Byte Encoding T1
    UXTB<c> <Rd>,<Rm>

  31 30 29 28 27 26 25 24 23 22 21 20 19 18 17 16 15 14 13 12 11 10 9 8 7 6 5 4 3 2 1 0
  |1  0  1  1| 0  0  1  0| 1  1|   Rm   |   Rd   |                unused               |

where:
            <c><q>                See Standard assembler syntax fields on page A6-7.

            <Rd>                  Specifies the destination register.

            <Rm>                  Specifies the register that contains the operand.

            <rotation>            This can be any one of:
                                  • ROR #8.
                                  • ROR #16.
                                  • ROR #24.
                                  • Omitted.

*/
void UXTBT1(uint32_t instruction)
{
  uint32_t Rm = getBits(instruction,21,19);
  uint32_t Rd = getBits(instruction,18,16);

  if(inITBlock())
  {
    if( checkCondition(cond) )
    coreReg[Rd] = getBits(coreReg[Rm], 7, 0);

    shiftITState();
  }
  else
  coreReg[Rd] = getBits(coreReg[Rm], 7, 0);

  coreReg[PC] += 2;
}


/*Signed Extend Halfword Encoding T2

  SXTH<c>.W <Rd>,<Rm>{,<rotation>}

  31 30 29 28 27 26 25 24 23 22 21 20 19 18 17 16 15 14 13 12 11 10 9 8 7 6 5 4 3 2 1 0
 |1  1  1  1  1 |0  1  0 |0| 0  0  0 |1  1  1  1 |1  1  1  1 |    Rd   |1|0| R |   Rm  |
 
  R => rotation

where:
            <c><q>                See Standard assembler syntax fields on page A6-7.

            <Rd>                  Specifies the destination register.

            <Rm>                  Specifies the register that contains the operand.

            <rotation>            This can be any one of:
                                  • ROR #8.
                                  • ROR #16.
                                  • ROR #24.
                                  • Omitted.

                                  If your assembler accepts shifts by #0 and treats them as equivalent to no shift or LSL
                                  #0, then it must accept ROR #0 here. It is equivalent to omitting <rotation>.
*/
void SXTHT2(uint32_t instruction)
{
  uint32_t rotated;
  uint32_t Rm = getBits(instruction, 3, 0);
  uint32_t Rd = getBits(instruction, 11, 8);
  uint32_t r = getBits(instruction, 5, 4);
  uint32_t rotation = r << 3;

  if(inITBlock())
  {
    if( checkCondition(cond) )
    {
      rotated = executeROR(rotation, coreReg[Rm], 0);
      coreReg[Rd] = signExtend(rotated, 16);
    }

    shiftITState();
  }
  else
  {
    rotated = executeROR(rotation, coreReg[Rm], 0);
    coreReg[Rd] = signExtend(rotated, 16);
  }

  coreReg[PC] += 4;
}


/*Unsigned Extend Halfword Encoding T2

  UXTH<c>.W <Rd>,<Rm>{,<rotation>}

  31 30 29 28 27 26 25 24 23 22 21 20 19 18 17 16 15 14 13 12 11 10 9 8 7 6 5 4 3 2 1 0
 |1  1  1  1  1 |0  1  0 |0| 0  0  1 |1  1  1  1 |1  1  1  1 |    Rd   |1|0| R |   Rm  |
 
  R => rotation

where:
            <c><q>                See Standard assembler syntax fields on page A6-7.

            <Rd>                  Specifies the destination register.

            <Rm>                  Specifies the register that contains the operand.

            <rotation>            This can be any one of:
                                  • ROR #8.
                                  • ROR #16.
                                  • ROR #24.
                                  • Omitted.

                                  If your assembler accepts shifts by #0 and treats them as equivalent to no shift or LSL
                                  #0, then it must accept ROR #0 here. It is equivalent to omitting <rotation>.
*/
void UXTHT2(uint32_t instruction)
{
  uint32_t rotated;
  uint32_t Rm = getBits(instruction, 3, 0);
  uint32_t Rd = getBits(instruction, 11, 8);
  uint32_t r = getBits(instruction, 5, 4);
  uint32_t rotation = r << 3;

  if(inITBlock())
  {
    if( checkCondition(cond) )
    {
      rotated = executeROR(rotation, coreReg[Rm], 0);
      coreReg[Rd] = getBits(rotated, 15, 0);
    }

    shiftITState();
  }
  else
  {
    rotated = executeROR(rotation, coreReg[Rm], 0);
    coreReg[Rd] = getBits(rotated, 15, 0);
  }

  coreReg[PC] += 4;
}