/*
    Program Name       : GDB RSP and ARM Simulator
    Author             : Wong Yan Yin, Jackson Teh Ka Sing
    Copyright (C) 2015 TARUC

    This file is part of GDB RSP and ARM Simulator.

    GDB RSP and ARM Simulator is free software, you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    GDB RSP and ARM Simulator is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY, without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with GDB RSP and ARM Simulator.  If not, see <http://www.gnu.org/licenses/>.

*/


#include "SUBSPRegister.h"
#include "ITandHints.h"
#include "StatusRegisters.h"
#include "ARMRegisters.h"
#include "getAndSetBits.h"
#include "getMask.h"
#include "ConditionalExecution.h"
#include "ShiftOperation.h"
#include <stdio.h>
#include <assert.h>



/* Sub SP with Register Encoding T1

   SUB{S}<c>.W <Rd>,SP,<Rm>{,<shift>}

   31 30 29 28 27 26 25 24 23 22 21 20 19 18 17 16 15 14 13 12 11 10 9 8 7 6 5 4 3 2 1 0
  |1  1  1  0  1 |0||1| 1  1  0  1 |S| 1  1  0  1 |0|   imm3  |   Rd   |imm2| t |   Rm  |

  t => type

where:
          S           If present, specifies that the instruction updates the flags. Otherwise, the instruction does not
                      update the flags.

          <c><q>      See Standard assembler syntax fields on page A6-7.

          <Rd>        Specifies the destination register. If <Rd> is omitted, this register is SP.

          <Rm>        Specifies the register that is optionally shifted and used as the second operand.

          <shift>     Specifies the shift to apply to the value read from <Rm>. If <shift> is omitted, no shift is
                      applied and all encodings are permitted. If <shift> is specified, only encoding T3 is
                      permitted. The possible shifts and how they are encoded are described in Shifts applied to a
                      register on page A6-12.

          If <Rd> is SP or omitted, <shift> is only permitted to be LSL #0, LSL #1, LSL #2 or LSL #3.
*/
void SUBSPRegisterT1(uint32_t instruction)
{
  uint32_t Rm =  getBits(instruction, 3, 0);
  uint32_t Rd = getBits(instruction, 11, 8);
  uint32_t imm2 = getBits(instruction, 7, 6);
  uint32_t imm3 = getBits(instruction, 14, 12);
  uint32_t statusFlag = getBits(instruction, 20, 20);
  uint32_t shiftType = getBits(instruction, 5, 4);

  uint32_t shiftImm = (imm3 << 2 ) | imm2;

  if(Rd == SP)
    assert(shiftType == 0 && shiftImm <= 3);

  if(inITBlock())
  {
    if( checkCondition(cond) )
      executeSUBSPRegister(Rd,Rm, statusFlag, shiftType, shiftImm);
    shiftITState();
  }
  else
    executeSUBSPRegister(Rd, Rm, statusFlag, shiftType, shiftImm);

  coreReg[PC] += 4;
}


/* This instruction subtracts an optionally-shifted register value from the SP value, and writes the result to the
   destination register.

   Input: Rd          destination register
          Rm          register value which will be added with Rn after shifted
          S               indicator for affecting the flag or not
          shiftType       determine what type of shifting is needed
          shiftImmediate  shift range from 0 to 31
*/
void executeSUBSPRegister(uint32_t Rd, uint32_t Rm, uint32_t S, uint32_t shiftType, uint32_t shiftImmediate)
{
  uint32_t backupRn = coreReg[SP];
  uint32_t shiftedRm, temp;

  shiftType = determineShiftOperation(shiftType, shiftImmediate);
  shiftedRm = executeShiftOperation(shiftType, shiftImmediate, coreReg[Rm], 0);

  temp = coreReg[SP] - shiftedRm;
  coreReg[Rd] = temp;

  if(S == 1)
  {
    updateZeroFlag(coreReg[Rd]);
    updateNegativeFlag(coreReg[Rd]);
    updateOverflowFlagSubtraction(backupRn, shiftedRm, coreReg[Rd]);
    updateCarryFlagSubtraction(backupRn, shiftedRm);
  }
}
