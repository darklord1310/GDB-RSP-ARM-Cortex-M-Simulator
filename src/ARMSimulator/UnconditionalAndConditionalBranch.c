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


#include "UnconditionalAndConditionalBranch.h"
#include "ARMRegisters.h"
#include "getAndSetBits.h"
#include "StatusRegisters.h"
#include "ITandHints.h"
#include "ConditionalExecution.h"
#include "ErrorSignal.h"
#include <stdio.h>
#include "CException.h"
#include "SVC.h"
#include "ExceptionObject.h"

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
        coreReg[PC] = coreReg[PC] & 0xfffffffe;
      }
      else
      {
        coreReg[PC] = coreReg[PC] + 2;
        coreReg[PC] = coreReg[PC] & 0xfffffffe;
      }

      shiftITState();
    }
    else
    {
      uint32_t afterSignExtend = signExtend(imm11AfterShift, 12);
      coreReg[PC] = coreReg[PC] + afterSignExtend + 4;
      coreReg[PC] = coreReg[PC] & 0xfffffffe;
    }
  }
  else
  {
    //placePCtoVectorTable(UsageFault);
    ThrowError();
  }
}


/* Branch causes a branch to a target address.

   B<c>.W <label>         Outside or last in IT block.

   31 30 29 28 27 26 25 24 23 22 21 20 19 18 17 16 15 14 13 12 11 10 9 8 7 6 5 4 3 2 1 0
  |1  1  1  1  0 |S|             imm10            |1  0|J1||1||J2|        imm11         |

where:
          <c><q>        See Standard assembler syntax fields on page A6-7.
                        ======
                         Note
                        ======
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
void UnconditionalBranchT2(uint32_t instruction)
{
  uint32_t imm10 = getBits(instruction, 25, 16);
  uint32_t imm11 = getBits(instruction, 10, 0);
  uint32_t S = getBits(instruction, 26, 26);
  uint32_t J1 = getBits(instruction, 13, 13);
  uint32_t J2 = getBits(instruction, 11, 11);

  uint32_t I1 = ~(J1 ^ S) & 0x1;
  uint32_t I2 = ~(J2 ^ S) & 0x1;

  uint32_t imm32 = imm11 << 1;
  imm32 = imm10 << 12 | imm32;
  imm32 = I2 << 22 | imm32;
  imm32 = I1 << 23 | imm32;
  imm32 = S << 24 | imm32;
  imm32 = signExtend(imm32, 25);

  if( !( inITBlock() ) || isLastInITBlock())
  {
    if( inITBlock() )
    {
      if( checkCondition(cond) )
      {
        coreReg[PC] = coreReg[PC] + imm32 + 4;
        coreReg[PC] = coreReg[PC] & 0xfffffffe;
      }

      shiftITState();
    }
    else
    {
      coreReg[PC] = coreReg[PC] + imm32 + 4;
      coreReg[PC] = coreReg[PC] & 0xfffffffe;
    }
  }
  else
  {
    //placePCtoVectorTable(UsageFault);
    ThrowError();
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
        coreReg[PC] = coreReg[PC] & 0xfffffffe;
      }
      else
      {
        coreReg[PC] = coreReg[PC] + 2;
        coreReg[PC] = coreReg[PC] & 0xfffffffe;
      }
    }
    else
      SVC(instruction);
  }
  else
  {
    //placePCtoVectorTable(UsageFault);
    ThrowError();
  }
}


/* Branch causes a branch to a target address.

   B<c>.W <label>         Not allowed in IT block.

   31 30 29 28 27 26 25 24 23 22 21 20 19 18 17 16 15 14 13 12 11 10 9 8 7 6 5 4 3 2 1 0
  |1  1  1  1  0 |S|    cond    |      imm6       |1  0|J1||0||J2|        imm11         |

where:
          <c><q>        See Standard assembler syntax fields on page A6-7.
                        ======
                         Note
                        ======
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
void ConditionalBranchT2(uint32_t instruction)
{
  uint32_t imm6 = getBits(instruction, 21, 16);
  uint32_t imm11 = getBits(instruction, 10, 0);
  uint32_t S = getBits(instruction, 26, 26);
  uint32_t J1 = getBits(instruction, 13, 13);
  uint32_t J2 = getBits(instruction, 11, 11);
  uint32_t cond = getBits(instruction, 25, 22);

  // uint32_t I1 = ~(J1 ^ S) & 0x1;
  // uint32_t I2 = ~(J2 ^ S) & 0x1;

  uint32_t imm32 = imm11 << 1;
  imm32 = imm6 << 12 | imm32;
  imm32 = J2 << 18 | imm32;
  imm32 = J1 << 19 | imm32;
  imm32 = S << 20 | imm32;
  imm32 = signExtend(imm32, 21);

  if( !( inITBlock() ) && cond != 0b1110 )
  {
      if( checkCondition(cond) )
      {
        coreReg[PC] = coreReg[PC] + imm32 + 4;
        coreReg[PC] = coreReg[PC] & 0xfffffffe;
      }
      else
      {
        coreReg[PC] = coreReg[PC] + 4;
        coreReg[PC] = coreReg[PC] & 0xfffffffe;
      }
  }
  else
  {
    //placePCtoVectorTable(UsageFault);
    ThrowError();
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
