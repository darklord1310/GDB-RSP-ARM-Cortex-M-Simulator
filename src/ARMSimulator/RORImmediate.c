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

#include "RORImmediate.h"
#include "ShiftOperation.h"
#include "ARMRegisters.h"
#include "getAndSetBits.h"
#include "StatusRegisters.h"
#include "ITandHints.h"
#include "ConditionalExecution.h"
#include <stdio.h>


/* Rotate Right Immediate Encoding T1

ROR{S}<c>.W <Rd>,<Rm>,#<imm5>

 31 30 29 28 27 26 25 24 23 22 21 20 19 18 17 16 15 14 13 12 11 10 9 8 7 6 5 4 3 2 1 0
|1  1  1  0  1 |0  1| 0  0  1  0 |S| 1  1  1  1 |0|   imm3  |   Rd   |imm2|1 1|  Rm   |

where:
          S         If present, specifies that the instruction updates the flags. Otherwise, the instruction does not
                    update the flags.
                    Only change N and Z flag

          <c><q>    See Standard assembler syntax fields on page A6-7.

          <Rd>      Specifies the destination register.

          <Rm>      Specifies the register that contains the first operand.

          <imm5>    Specifies the shift amount, in the range 0 to 31. See Shifts applied to a register on
                    page A6-12.
*/
void RORImmediateT1(uint32_t instruction)
{
  uint32_t Rm = getBits(instruction, 3, 0);
  uint32_t Rd = getBits(instruction, 11, 8);
  uint32_t imm2 = getBits(instruction, 7, 6);
  uint32_t imm3 = getBits(instruction, 14, 12);
  uint32_t statusFlag = getBits(instruction, 20, 20);
  uint32_t imm5 = imm3 << 2 | imm2;

  if(inITBlock())
  {
    if( checkCondition(cond) )
      executeRORImmediate(imm5, Rm, Rd, statusFlag);
    shiftITState();
  }
  else
    executeRORImmediate(imm5, Rm, Rd, statusFlag);

  coreReg[PC] += 4;
}


/*  This function will  provides the value of the contents of a register rotated by a constant value. The
    bits that are rotated off the right end are inserted into the vacated bit positions on the left. It can optionally
    update the condition flags based on the result.

    Input:  imm5        the immediate, also indicate how many times to shift
            Rm          source register
            Rd          destination register
            StatusBit   indicator for affecting the flag or not
*/
void executeRORImmediate(uint32_t imm5, uint32_t Rm, uint32_t Rd, uint32_t S)
{
  coreReg[Rd] = executeROR(imm5, coreReg[Rm], S);

  if(S == 1)
  {
    updateNegativeFlag(coreReg[Rd]);
    updateZeroFlag(coreReg[Rd]);

    // Overflow flag will not be affected and the carry flag handling is inside the executeASR function
  }
}
