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


#include "ADCRegister.h"
#include <assert.h>
#include "ARMRegisters.h"
#include "getAndSetBits.h"
#include "StatusRegisters.h"
#include "ModifiedImmediateConstant.h"
#include "ITandHints.h"
#include "ConditionalExecution.h"
#include "ShiftOperation.h"
#include <stdio.h>


/*Add with Carry Register To Register Encoding T1
  ADCS        <Rdn>,<Rm>     Outside IT block.
  ADC<c>      <Rdn>,<Rm>     Inside IT block.

   31 30 29 28 27 26 25 24 23 22 21 20 19 18 17 16 15 14 13 12 11 10 9 8 7 6 5 4 3 2 1 0
  |0   1  0  0  0  0| 0  1  0  1|   Rm   |   Rdn  |             unused                  |

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
void ADCRegisterT1(uint32_t instruction)
{
  uint32_t Rm =  getBits(instruction,21,19);
  uint32_t Rdn = getBits(instruction,18,16);

 if(inITBlock())
 {
    if( checkCondition(cond) )
      executeADCRegister(Rm, Rdn, Rdn, 0, 0, 0);

    shiftITState();
 }
 else
    executeADCRegister(Rm, Rdn, Rdn, 1, 0, 0);

  coreReg[PC] += 2;
}


/* Add with Carry Register Encoding T2

   ADC{S}<c>.W <Rd>,<Rn>,<Rm>{,<shift>}

   31 30 29 28 27 26 25 24 23 22 21 20 19 18 17 16 15 14 13 12 11 10 9 8 7 6 5 4 3 2 1 0
  |1  1  1  0  1 |0  1 |1  0  1  0 |S|     Rn     |0|   imm3  |   Rd   |imm2| t |   Rm  |

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
                      applied and both encodings are permitted. If <shift> is specified, only encoding T2 is
                      permitted. The possible shifts and how they are encoded are described in Shifts applied to a
                      register on page A6-12.

          A special case is that if ADC<c> <Rd>,<Rn>,<Rd> is written with <Rd> and <Rn> both in the range R0-R7, it will
          be assembled using encoding T2 as though ADC<c> <Rd>,<Rn> had been written. To prevent this happening,
          use the .W qualifier.
*/
void ADCRegisterT2(uint32_t instruction)
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
      executeADCRegister(Rm, Rd, Rn, statusFlag, shiftType, shiftImm);
    shiftITState();
  }
  else
    executeADCRegister(Rm, Rd, Rn, statusFlag, shiftType, shiftImm);

  coreReg[PC] += 4;
}


/* Add with Carry (register) adds a register value, the carry flag value, and an optionally-shifted register value,
   and writes the result to the destination register. It can optionally update the condition flags based on the
   result.

   Input: Rn          register value which will be added with Rm
          Rd          destination register
          Rm          register value which will be added with Rn after shifted
          S           if set will affect the status register
          shiftType       determine what type of shifting is needed
          shiftImmediate  shift range from 0 to 31
*/
void executeADCRegister(uint32_t Rm, uint32_t Rd, uint32_t Rn, uint32_t S, uint32_t shiftType, uint32_t shiftImmediate)
{
  uint32_t backupRn = coreReg[Rn];                                      //this is to avoid the value of Rn being overwritten in case
                                                                        //of Rn and Rd is pointing to the same register
  uint32_t carryFlag = getBits(coreReg[xPSR], 29, 29);                  //store the current carry flag
  uint32_t shiftedRm, temp;

  shiftType = determineShiftOperation(shiftType, shiftImmediate);
  shiftedRm = executeShiftOperation(shiftType, shiftImmediate, coreReg[Rm], 0);

  temp = coreReg[Rn] + shiftedRm;
  writeToCoreRegisters(Rd, temp + carryFlag);                              //get the result of Rn + Rm + Carry
                                  
  if(S == 1)
  {
    updateZeroFlag(coreReg[Rd]);
    updateNegativeFlag(coreReg[Rd]);

    updateOverflowFlagAddition(backupRn, shiftedRm, temp);
    if(isOverflow() == 0)
      updateOverflowFlagAddition(temp, carryFlag , coreReg[Rd]);

    updateCarryFlagAddition(backupRn, shiftedRm);
    if(isCarry() == 0)
      updateCarryFlagAddition(temp, carryFlag);
  }
}