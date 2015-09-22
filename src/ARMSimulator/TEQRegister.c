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


#include "TEQRegister.h"
#include "ITandHints.h"
#include "StatusRegisters.h"
#include "ARMRegisters.h"
#include "getAndSetBits.h"
#include "getMask.h"
#include "ConditionalExecution.h"
#include "ShiftOperation.h"


/* Test Equivalence Register Encoding T2

   TEQ<c> <Rn>,<Rm>{,<shift>}

   31 30 29 28 27 26 25 24 23 22 21 20 19 18 17 16 15 14 13 12 11 10 9 8 7 6 5 4 3 2 1 0
  |1  1  1  0  1 |0  1 |0  1  0  0 |1|     Rn     |0|   imm3  |1  1  11|imm2| t |   Rm  |

  t => type

where:
          S         If present, specifies that the instruction updates the flags. Otherwise, the instruction does not
                    update the flags.

          <c><q>    See Standard assembler syntax fields on page A6-7.

          <Rd>      Specifies the destination register. If <Rd> is omitted, this register is the same as <Rn>.

          <Rn>      Specifies the register that contains the first operand.

          <Rm>      Specifies the register that is optionally shifted and used as the second operand.

          <shift>   Specifies the shift to apply to the value read from <Rm>. If <shift> is omitted, no shift is
                    applied and both encodings are permitted. If <shift> is specified, only encoding T2 is
                    permitted. The possible shifts and how they are encoded are described in Shifts applied to a
                    register on page A6-12.

          A special case is that if EOR<c> <Rd>,<Rn>,<Rd> is written with <Rd> and <Rn> both in the range R0-R7, it will
          be assembled using encoding T2 as though EOR<c> <Rd>,<Rn> had been written. To prevent this happening,
          use the .W qualifier.
*/
void TEQRegisterT1(uint32_t instruction)
{
  uint32_t Rm =  getBits(instruction, 3, 0);
  uint32_t Rn = getBits(instruction, 19, 16);
  uint32_t imm2 = getBits(instruction, 7, 6);
  uint32_t imm3 = getBits(instruction, 14, 12);
  uint32_t shiftType = getBits(instruction, 5, 4);

  uint32_t shiftImm = (imm3 << 2 ) | imm2;

  if(inITBlock())
  {
    if( checkCondition(cond) )
      executeTEQRegister(Rm, Rn, shiftType, shiftImm);
    shiftITState();
  }
  else
    executeTEQRegister(Rm, Rn, shiftType, shiftImm);

  coreReg[PC] += 4;
}


/*  This instruction performs an exclusive OR operation on a register value and an optionally-shifted
    register value. It updates the condition flags based on the result, and discards the result.

    Input:  Rm              source register
            Rn              the register that contains the first operand
            shiftType       determine what type of shifting is needed
            shiftImmediate  shift range from 0 to 31
*/
void executeTEQRegister(uint32_t Rm, uint32_t Rn, uint32_t shiftType, uint32_t shiftImmediate)
{
  uint32_t shiftedRm, result;

  shiftType = determineShiftOperation(shiftType, shiftImmediate);
  shiftedRm = executeShiftOperation(shiftType, shiftImmediate, coreReg[Rm], 1);

  result = coreReg[Rn] ^ shiftedRm;

  updateZeroFlag(result);
  updateNegativeFlag(result);
}