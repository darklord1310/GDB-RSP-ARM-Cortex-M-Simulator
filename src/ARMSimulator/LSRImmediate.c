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


#include "LSRImmediate.h"
#include "ShiftOperation.h"
#include <stdint.h>


/*Logical Shift Right Immediate Encoding T1
      LSRS <Rd>,<Rm>,#<imm5>        Outside IT block.
      LSR<c> <Rd>,<Rm>,#<imm5>      Inside IT block

  Note : Can only shift 1 < n <= 32 times
   31 30 29 28 27 26 25 24 23 22 21 20 19 18 17 16 15 14 13 12 11 10 9 8 7 6 5 4 3 2 1 0
  |0  0  0 |0  1|     imm5      |   Rm  |    Rd   |             unused                 |

where:
        S          If present, specifies that the instruction updates the flags. Otherwise, the instruction does not
                   update the flags.

        <c><q>     See Standard assembler syntax fields on page A6-7.

        <Rd>       Specifies the destination register.

        <Rm>       Specifies the register that contains the first operand.

        <imm5>     Specifies the shift amount, in the range 1 to 32. See Shifts applied to a register on
                   page A6-12.
*/
void LSRImmediateT1(uint32_t instruction)
{
  uint32_t imm5 = getBits(instruction, 26 , 22);
  uint32_t Rm = getBits(instruction, 21, 19);
  uint32_t Rd = getBits(instruction, 18, 16);

  if(inITBlock())
  {
    if( checkCondition(cond) )
      executeLSRImmediate(imm5, Rm, Rd, 0);
    shiftITState();
    coreReg[PC] += 2;
  }
  else
  {
    executeLSRImmediate(imm5, Rm, Rd, 1);
    coreReg[PC] += 2;
  }
}


/* Logical Shift Right Immediate Encoding T2

LSR{S}<c>.W <Rd>,<Rm>,#<imm5>

 31 30 29 28 27 26 25 24 23 22 21 20 19 18 17 16 15 14 13 12 11 10 9 8 7 6 5 4 3 2 1 0
|1  1  1  0  1 |0  1| 0  0  1  0 |S| 1  1  1  1 |0|   imm3  |   Rd   |imm2|0 1|  Rm   |

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
void LSRImmediateT2(uint32_t instruction)
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
      executeLSRImmediate(imm5, Rm, Rd, statusFlag);
    shiftITState();
  }
  else
    executeLSRImmediate(imm5, Rm, Rd, statusFlag);

  coreReg[PC] += 4;
}


/*  This function will perform the logical shift right for immediate

    Input:  immediate       the immediate, also indicate how many times to shift
            Rm              source register
            Rd              destination register
            S               indicator for affecting the flag or not

*/
void executeLSRImmediate(uint32_t immediate, uint32_t Rm, uint32_t Rd, uint32_t S)
{
  coreReg[Rd] = executeLSR(immediate, coreReg[Rm], S);

  if(S == 1)
  {
    updateNegativeFlag(coreReg[Rd]);
    updateZeroFlag(coreReg[Rd]);

    // Overflow flag will not be affected and the carry flag handling is inside the executeLSR function
  }
}



