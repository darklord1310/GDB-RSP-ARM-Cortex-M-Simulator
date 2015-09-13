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


#include "RSBImmediate.h"
#include "ITandHints.h"
#include "ConditionalExecution.h"
#include <assert.h>


/*Reverse Subtract Immediate Encoding T1
      RSBS    <Rd>,<Rn>,#0    Outside IT block.
      RSB<c>  <Rd>,<Rn>,#0    Inside IT block.

   31 30 29 28 27 26 25 24 23 22 21 20 19 18 17 16 15 14 13 12 11 10 9 8 7 6 5 4 3 2 1 0
  |0   1  0  0  0  0| 1  0  0  1|   Rn   |   Rd   |             unused                  |

where :
          S           If present, specifies that the instruction updates the flags. Otherwise, the instruction does not
                      update the flags.

          <c><q>      See Standard assembler syntax fields on page A6-7.

          <Rd>        Specifies the destination register. If <Rd> is omitted, this register is the same as <Rn>.

          <Rn>        Specifies the register that contains the first operand.

          <const>     Specifies the immediate value to be added to the value obtained from <Rn>. The only allowed
                      value for encoding T1 is 0. See Modified immediate constants
*/
void RSBImmediateT1(uint32_t instruction)
{
  uint32_t Rn = getBits(instruction,21,19);
  uint32_t Rd = getBits(instruction,18,16);
  assert(Rn <= 0b111);
  assert(Rd <= 0b111);

  if(inITBlock())
  {
    if( checkCondition(cond) )
      executeRSBImmediate(0, Rn, Rd, 0);
    shiftITState();
  }
 else
    executeRSBImmediate(0, Rn, Rd, 1);

  coreReg[PC] += 2;
}


/*Reverse Subtract Immediate Encoding T2
      RSB{S}<c>.W <Rd>,<Rn>,#<const>

   31 30 29 28 27 26 25 24 23 22 21 20 19 18 17 16 15 14 13 12 11 10 9 8 7 6 5 4 3 2 1 0
  |1  1  1  1  0  |i|0| 1  1  1  0 |S|     Rn     |0 |  imm3  |    Rd   |     imm8      |

where :
          S           If present, specifies that the instruction updates the flags. Otherwise, the instruction does not
                      update the flags.

          <c><q>      See Standard assembler syntax fields on page A6-7.

          <Rd>        Specifies the destination register. If <Rd> is omitted, this register is the same as <Rn>.

          <Rn>        Specifies the register that contains the first operand.

          <const>     Specifies the immediate value to be added to the value obtained from <Rn>. The only allowed
                      value for encoding T1 is 0. See Modified immediate constants in Thumb instructions on
                      page A5-15 for the range of allowed values for encoding T2.
*/
void RSBImmediateT2(uint32_t instruction)
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
      executeRSBImmediate(ModifiedConstant, Rn, Rd, statusFlag);
    shiftITState();
  }
  else
    executeRSBImmediate(ModifiedConstant, Rn, Rd, statusFlag);

  coreReg[PC] += 4;
}



/* Reverse Subtract (immediate) subtracts a register value from a 0, and writes the result to
   the destination register. It can optionally update the condition flags based on the result.

   Input: Rn          register value which will be added with immediate
          Rd          destination register
          immediate   immediate value which will be added with Rn
          S           if set will affect the status register
*/
void executeRSBImmediate(uint32_t immediate, uint32_t Rn, uint32_t Rd, uint32_t S)
{
  uint32_t backupRn = coreReg[Rn];            //prevent the Rn value to be overwritten in case if Rn = Rd
  uint32_t temp = immediate - coreReg[Rn];    //get the result of 0 - Rn
  coreReg[Rd] = temp;

  if(S == 1)
  {
    updateZeroFlag(coreReg[Rd]);
    updateNegativeFlag(coreReg[Rd]);
    updateOverflowFlagSubtraction(immediate, backupRn, coreReg[Rd]);
    updateCarryFlagSubtraction(immediate, backupRn);
  }
}