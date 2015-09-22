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


#include "MOVRegister.h"
#include "ARMRegisters.h"
#include "getAndSetBits.h"
#include "StatusRegisters.h"
#include "ITandHints.h"
#include "ConditionalExecution.h"
#include <assert.h>


/*
  Move Register to Register Encoding T1
        MOV<c> <Rd>,<Rm>

   31 30 29 28 27 26 25 24 23 22 21 20 19 18 17 16 15 14 13 12 11 10 9 8 7 6 5 4 3 2 1 0
  |0  1  0  0  0  1 | 1 0 |D|     Rm     |   Rd   |             unused                  |

  where:
            S       If present, specifies that the instruction updates the flags. Otherwise, the instruction does not
                    update the flags.
                    Only change N and Z flag

            <c><q>  See Standard assembler syntax fields on page A6-7.

            <Rd>    The destination register. This register can be the SP or PC, provided S is not specified.
                    If <Rd> is the PC, then only encoding T1 is permitted, and the instruction causes a branch to
                    the address moved to the PC. The instruction must either be outside an IT block or the last
                    instruction of an IT block.

            <Rm>    The source register. This register can be the SP or PC.The instruction must not specify S if
                    <Rm> is the SP or PC.

            D       is the fourth bit for the Rd, if the address can be reach using 3 bits D = 0, else D = 1

*/
void MOVRegisterToRegisterT1(uint32_t instruction)
{
  uint32_t Rm = getBits(instruction, 22, 19);
  uint32_t Rd = getBits(instruction, 18, 16);
  uint32_t D = getBits(instruction, 23, 23);

  Rd = ( D << 3 ) | Rd;     // this is to merge the D with Rd to make Rd becomes 4 bits
                            // Eg. new Rd = D Rd2 Rd1 Rd0

  if( inITBlock() )
  {
    if( checkCondition(cond) )
      executeMOVRegister(Rm, Rd, 0);

    shiftITState();
  }
  else
    executeMOVRegister(Rm, Rd, 0);

  if(Rd != PC)
    coreReg[PC] += 2;
}



/*
  Move Register to Register Encoding T2
        MOVS <Rd>,<Rm>

  Note :  This can only applicable to those registers lower than R7

   31 30 29 28 27 26 25 24 23 22 21 20 19 18 17 16 15 14 13 12 11 10 9 8 7 6 5 4 3 2 1 0
  |0  0  0  0  0  0  0  0  0  0 |   Rm   |   Rd   |               unused                |


  where:
            S       If present, specifies that the instruction updates the flags. Otherwise, the instruction does not
                    update the flags.
                    Only change N and Z flag

            <c><q>  See Standard assembler syntax fields on page A6-7.

            <Rd>    The destination register. This register can be the SP or PC, provided S is not specified.
                    If <Rd> is the PC, then only encoding T1 is permitted, and the instruction causes a branch to
                    the address moved to the PC. The instruction must either be outside an IT block or the last
                    instruction of an IT block.

            <Rm>    The source register. This register can be the SP or PC.The instruction must not specify S if
                    <Rm> is the SP or PC.

*/
void MOVRegisterToRegisterT2(uint32_t instruction)
{
  uint32_t Rm = getBits(instruction, 21, 19);
  uint32_t Rd = getBits(instruction, 18, 16);

  assert(Rm != SP || Rm != PC);
  assert(Rd != SP || Rd != PC);

  if( inITBlock() )
  {
    if( checkCondition(cond) )
      executeMOVRegister(Rm, Rd, 0);

    shiftITState();
    coreReg[PC] += 2;
  }
  else
  {
    executeMOVRegister(Rm, Rd, 1);
    coreReg[PC] += 2;
  }

}


/* Move From Register To Register Encoding T3

MOV{S}<c>.W <Rd>,<Rm>

NOTE
====
ARM deprecates the use of the following MOV (register) instructions:
• ones in which <Rd> is the SP or PC and <Rm> is also the SP or PC is deprecated.
• ones in which S is specified and <Rm> is the SP, or <Rm> is the PC.

31 30 29 28 27 26 25 24 23 22 21 20 19 18 17 16 15 14 13 12 11 10 9 8 7 6 5 4 3 2 1 0
|1  1  1  0 1 |0  1| 0  0  1  0 |S| 1  1  1  1 |0| 0  0  0 |    Rd   |0 0 0 0|  Rm   |

where:
          S         If present, specifies that the instruction updates the flags. Otherwise, the instruction does not
                    update the flags.
                    Only change N and Z flag

          <c><q>    See Standard assembler syntax fields on page A6-7.

          <Rd>      The destination register. This register can be the SP or PC, provided S is not specified.
                    If <Rd> is the PC, then only encoding T1 is permitted, and the instruction causes a branch to
                    the address moved to the PC. The instruction must either be outside an IT block or the last
                    instruction of an IT block.

          <Rm>      The source register. This register can be the SP or PC. The instruction must not specify S if
                    <Rm> is the SP or PC.

Encoding T3 is not permitted if either:
• <Rd> or <Rm> is the PC
• both <Rd> and <Rm> are the SP.
*/
void MOVRegisterT3(uint32_t instruction)
{
  uint32_t Rm = getBits(instruction, 3, 0);
  uint32_t Rd = getBits(instruction, 11, 8);
  uint32_t statusFlag = getBits(instruction, 20, 20);

  assert(Rd != PC || Rm != PC);
  assert(Rd != SP && Rm != SP);

  if(inITBlock())
 {
    if( checkCondition(cond) )
      executeMOVRegister(Rm, Rd, statusFlag);
    shiftITState();
 }
 else
    executeMOVRegister(Rm, Rd, statusFlag);

  coreReg[PC] += 4;
}


/*  This function will perform the move immediate from Rm to Rd

    Input:  Rm              source register
            Rd              destination register
            S               indicator for affecting the flag or not

*/
void executeMOVRegister(uint32_t Rm, uint32_t Rd, uint32_t S)
{
  if(Rd == PC)                    // only for encoding T1
    ALUWritePC(coreReg[Rm]);
  else if(Rm == PC)
    coreReg[Rd] = coreReg[Rm] + 4;
  else
  {
    coreReg[Rd] = coreReg[Rm];

    if(S == 1)
    {
      updateZeroFlag(coreReg[Rd]);
      updateNegativeFlag(coreReg[Rd]);
    }
  }
}
