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


#include "ADCImmediate.h"


/* ADC Immediate Encoding T1

ADC{S}<c> <Rd>,<Rn>,#<const>

31 30 29 28 27 26 25 24 23 22 21 20 19 18 17 16 15 14 13 12 11 10 9 8 7 6 5 4 3 2 1 0
|1  1  1  1 0 |i||0| 1  0  1  0 |S|      Rn    |0|  imm3   |    Rd   |     imm8      |

where :
          S             If present, specifies that the instruction updates the flags. Otherwise, the instruction
                        does not update the flags.

          <c><q>        See Standard assembler syntax fields on page A6-7.

          <Rd>          Specifies the destination register. If <Rd> is omitted, this register is the same as <Rn>.

          <Rn>          Specifies the register that contains the operand. This register is allowed to be the SP.

          <const>       Specifies the immediate value to be added to the value obtained from <Rn>. See Modified
                        immediate constants in Thumb instructions on page A5-15 for the range of allowed values.
*/
void ADCImmediateT1(uint32_t instruction)
{
  uint32_t imm8 = getBits(instruction, 7, 0);
  uint32_t Rd = getBits(instruction, 11, 8);
  uint32_t Rn = getBits(instruction, 19, 16);
  uint32_t imm3 = getBits(instruction, 14, 12);
  uint32_t statusFlag = getBits(instruction, 20, 20);

  uint32_t i = getBits(instruction, 26, 26);
  uint32_t bit7 = getBits(instruction, 7, 7);
  uint32_t temp = (i << 3 ) | imm3;
  uint32_t modifyControl = (temp << 1) | bit7;

  uint32_t ModifiedConstant = ModifyImmediateConstant(modifyControl, imm8, 0);

  if(inITBlock())
  {
    if( checkCondition(cond) )
      executeADCImmediate(Rn, Rd, ModifiedConstant, statusFlag);
    shiftITState();
  }
  else
    executeADCImmediate(Rn, Rd, ModifiedConstant, statusFlag);

  coreReg[PC] += 4;
}


/* This instruction adds an immediate value and the carry flag to a register value,
   and writes the result to the destination register.

   Input: Rn          register value which will be added with immediate and carry flag
          Rd          destination register
          immediate   immediate value which will be added with Rn
          S           if set will affect the status register
*/
void executeADCImmediate(uint32_t Rn, uint32_t Rd, uint32_t immediate, uint32_t S)
{
  uint32_t carry = getBits(coreReg[xPSR], 29, 29);
  uint32_t backupRn = coreReg[Rn];
  uint32_t temp = coreReg[Rn] + immediate;
  coreReg[Rd] = temp + carry;               //get the result of Rn + immediate + carry flag

  if(S == 1)
  {
    updateZeroFlag(coreReg[Rd]);
    updateNegativeFlag(coreReg[Rd]);
    updateOverflowFlagAddition(backupRn, immediate, temp);
    if(isOverflow() == 0)
      updateOverflowFlagAddition(temp, carry , coreReg[Rd]);

    updateCarryFlagAddition(backupRn, immediate);
    if(isCarry() == 0)
      updateCarryFlagAddition(temp, carry);
  }
}
