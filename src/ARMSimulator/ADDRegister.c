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


#include "ADDRegister.h"
#include <assert.h>
#include <stdio.h>
#include "StatusRegisters.h"
#include "ADDRegister.h"
#include "ADR.h"
#include "ARMRegisters.h"
#include "getAndSetBits.h"
#include "ADDSPRegister.h"
#include "ModifiedImmediateConstant.h"
#include "ITandHints.h"
#include "ConditionalExecution.h"
#include "ShiftOperation.h"


/*Add Register To Register Encoding T1
    ADDS <Rd>,<Rn>,<Rm>     Outside IT block.
    ADD<c> <Rd>,<Rn>,<Rm>   Inside IT block.

   31 30 29 28 27 26 25 24 23 22 21 20 19 18 17 16 15 14 13 12 11 10 9 8 7 6 5 4 3 2 1 0
  |0  0   0| 1  1| 0  0|   Rm   |   Rn   |   Rd   |                unused               |

where:
          S           If present, specifies that the instruction updates the flags. Otherwise, the instruction does not
                      update the flags.

          <c><q>      See Standard assembler syntax fields on page A6-7.

          <Rd>        Specifies the destination register. If <Rd> is omitted, this register is the same as <Rn> and
                      encoding T2 is preferred to encoding T1 if both are available (this can only happen inside
                      an IT block). If <Rd> is specified, encoding T1 is preferred to encoding T2.

          <Rn>        Specifies the register that contains the first operand. If the SP is specified for <Rn>, see ADD
                      (SP plus register) on page A6-28.

          <Rm>        Specifies the register that is optionally shifted and used as the second operand.

          <shift>     Specifies the shift to apply to the value read from <Rm>. If <shift> is omitted, no shift is
                      applied and all encodings are permitted. If <shift> is specified, only encoding T3 is
                      permitted. The possible shifts and how they are encoded are described in Shifts applied to a
                      register on page A6-12.

          Inside an IT block, if ADD<c> <Rd>,<Rn>,<Rd> cannot be assembled using encoding T1, it is assembled using
          encoding T2 as though ADD<c> <Rd>,<Rn> had been written. To prevent this happening, use the .W qualifier.
*/
void ADDRegisterToRegisterT1(uint32_t instruction)
{
  uint32_t Rm = getBits(instruction,24,22);
  uint32_t Rn = getBits(instruction,21,19);
  uint32_t Rd = getBits(instruction,18,16);
  assert(Rm <= 0b111);
  assert(Rn <= 0b111);
  assert(Rd <= 0b111);

 if(inITBlock())
 {
    if( checkCondition(cond) )
      executeADDRegister(Rm, Rd, Rn, 0, 0, 0);
    shiftITState();
 }
 else
    executeADDRegister(Rm, Rd, Rn, 1, 0, 0);

  coreReg[PC] += 2;

}



/*Add Register To Register Encoding T2
    ADD<c> <Rdn>,<Rm>

    setflags = FALSE

   31 30 29 28 27 26 25 24 23 22 21 20 19 18 17 16 15 14 13 12 11 10 9 8 7 6 5 4 3 2 1 0
  |0   1  0  0  0  1| 0  0|DN|     Rm    |   Rdn  |                unused               |

where:
          S           If present, specifies that the instruction updates the flags. Otherwise, the instruction does not
                      update the flags.

          <c><q>      See Standard assembler syntax fields on page A6-7.

          <Rd>        Specifies the destination register. If <Rd> is omitted, this register is the same as <Rn> and
                      encoding T2 is preferred to encoding T1 if both are available (this can only happen inside
                      an IT block). If <Rd> is specified, encoding T1 is preferred to encoding T2.

          <Rn>        Specifies the register that contains the first operand. If the SP is specified for <Rn>, see ADD
                      (SP plus register) on page A6-28.

          <Rm>        Specifies the register that is optionally shifted and used as the second operand.

          <shift>     Specifies the shift to apply to the value read from <Rm>. If <shift> is omitted, no shift is
                      applied and all encodings are permitted. If <shift> is specified, only encoding T3 is
                      permitted. The possible shifts and how they are encoded are described in Shifts applied to a
                      register on page A6-12.

          Inside an IT block, if ADD<c> <Rd>,<Rn>,<Rd> cannot be assembled using encoding T1, it is assembled using
          encoding T2 as though ADD<c> <Rd>,<Rn> had been written. To prevent this happening, use the .W qualifier.
*/
void ADDRegisterToRegisterT2(uint32_t instruction)
{
  uint32_t Rm = getBits(instruction,22,19);
  uint32_t Rdn = getBits(instruction,18,16);
  uint32_t DN = getBits(instruction,23,23);

  Rdn = (DN << 3) | Rdn;
  assert(Rm <= 0x0f);
  assert(Rdn <= 0x0f);
  assert(DN <= 1);

  if(inITBlock())
  {
    if( checkCondition(cond) )
    {
      if(Rm == 0b1101)
        ADDSPRegisterT1(instruction);
      else if(Rdn == 0b1101)
        ADDSPRegisterT2(instruction);
      else
        executeADDRegister(Rm, Rdn, Rdn, 0, 0, 0);
    }
    shiftITState();

    if( Rdn != PC)
      coreReg[PC] += 2;
  }
  else
  {
    if(Rm == 0b1101)
      ADDSPRegisterT1(instruction);
    else if(Rdn == 0b1101)
      ADDSPRegisterT2(instruction);
    else
      executeADDRegister(Rm, Rdn, Rdn, 0, 0, 0);

    if( Rdn != PC)
      coreReg[PC] += 2;
  }
}


/* Add Register Encoding T3

   ADD{S}<c>.W <Rd>,<Rn>,<Rm>{,<shift>}

   31 30 29 28 27 26 25 24 23 22 21 20 19 18 17 16 15 14 13 12 11 10 9 8 7 6 5 4 3 2 1 0
  |1  1  1  0  1 |0  1 |1  0  0  0 |S|     Rn     |0|   imm3  |   Rd   |imm2| t |   Rm  |

  t => type

where:
          S           If present, specifies that the instruction updates the flags. Otherwise, the instruction does not
                      update the flags.

          <c><q>      See Standard assembler syntax fields on page A6-7.

          <Rd>        Specifies the destination register. If <Rd> is omitted, this register is the same as <Rn> and
                      encoding T2 is preferred to encoding T1 if both are available (this can only happen inside
                      an IT block). If <Rd> is specified, encoding T1 is preferred to encoding T2.

          <Rn>        Specifies the register that contains the first operand. If the SP is specified for <Rn>, see ADD
                      (SP plus register) on page A6-28.

          <Rm>        Specifies the register that is optionally shifted and used as the second operand.

          <shift>     Specifies the shift to apply to the value read from <Rm>. If <shift> is omitted, no shift is
                      applied and all encodings are permitted. If <shift> is specified, only encoding T3 is
                      permitted. The possible shifts and how they are encoded are described in Shifts applied to a
                      register on page A6-12.

          Inside an IT block, if ADD<c> <Rd>,<Rn>,<Rd> cannot be assembled using encoding T1, it is assembled using
          encoding T2 as though ADD<c> <Rd>,<Rn> had been written. To prevent this happening, use the .W qualifier.
*/
void ADDRegisterT3(uint32_t instruction)
{
  uint32_t Rm =  getBits(instruction, 3, 0);
  uint32_t Rd = getBits(instruction, 11, 8);
  uint32_t Rn = getBits(instruction, 19, 16);
  uint32_t imm2 = getBits(instruction, 7, 6);
  uint32_t imm3 = getBits(instruction, 14, 12);
  uint32_t statusFlag = getBits(instruction, 20, 20);
  uint32_t shiftType = getBits(instruction, 5, 4);

  uint32_t shiftImm = (imm3 << 2 ) | imm2;

  if(inITBlock())
  {
    if( checkCondition(cond) )
      executeADDRegister(Rm, Rd, Rn, statusFlag, shiftType, shiftImm);
    shiftITState();
  }
  else
    executeADDRegister(Rm, Rd, Rn, statusFlag, shiftType, shiftImm);

  coreReg[PC] += 4;
}


/* This instruction adds a register value and an optionally-shifted register value, and writes the result to the
   destination register. It can optionally update the condition flags based on the result.

   Input: Rn          register value which will be added with Rm
          Rd          destination register
          Rm          register value which will be added with Rn after shifted
          S               indicator for affecting the flag or not
          shiftType       determine what type of shifting is needed
          shiftImmediate  shift range from 0 to 31
*/
void executeADDRegister(uint32_t Rm, uint32_t Rd, uint32_t Rn, uint32_t S, uint32_t shiftType, uint32_t shiftImmediate)
{
  uint32_t backupRn = coreReg[Rn];
  uint32_t shiftedRm, temp;

  shiftType = determineShiftOperation(shiftType, shiftImmediate);
  shiftedRm = executeShiftOperation(shiftType, shiftImmediate, coreReg[Rm], 0);

  if(Rd == PC)                                              // only for encoding T2
  {
    uint32_t address = shiftedRm + coreReg[Rn] + 4;
    ALUWritePC(address);
  }
  else if(Rm == PC)
  {
    // coreReg[Rd] = alignPC(coreReg[Rm] + 2, 4) + coreReg[SP];
    coreReg[Rd] = shiftedRm + coreReg[Rn] + 4;
  }
  else
  {
    temp = coreReg[Rn] + shiftedRm;
    coreReg[Rd] = temp;

    if(S == 1)
    {
      updateZeroFlag(coreReg[Rd]);
      updateNegativeFlag(coreReg[Rd]);
      updateOverflowFlagAddition(backupRn, shiftedRm, coreReg[Rd]);
      updateCarryFlagAddition(backupRn, shiftedRm);
    }
  }
}