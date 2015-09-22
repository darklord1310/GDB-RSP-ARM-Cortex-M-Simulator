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


#include "RRX.h"


/* Rotate Right with Extend Encoding T1

RRX{S}<c> <Rd>,<Rm>

 31 30 29 28 27 26 25 24 23 22 21 20 19 18 17 16 15 14 13 12 11 10 9 8 7 6 5 4 3 2 1 0
|1  1  1  0  1 |0  1| 0  0  1  0 |S| 1  1  1  1 |0| 0  0  0 |    Rd   |0 0|1 1|  Rm   |

where:
          S         If present, specifies that the instruction updates the flags. Otherwise, the instruction does not
                    update the flags.

          <c><q>    See Standard assembler syntax fields on page A6-7.

          <Rd>      Specifies the destination register.

          <Rm>      Specifies the register that contains the operand.
*/
void RRXT1(uint32_t instruction)
{
    uint32_t Rd = getBits(instruction, 11, 8);
    uint32_t Rm = getBits(instruction, 3, 0);
    uint32_t statusFlag = getBits(instruction, 20, 20);

    if(inITBlock())
    {
        if( checkCondition(cond) )
            executeRRXT1(Rm, Rd, statusFlag);
        shiftITState();
    }
    else
        executeRRXT1(Rm, Rd, statusFlag);

    coreReg[PC] += 4;
}


/*  This instruction  provides the value of the contents of a register shifted right by one place, with the
    carry flag shifted into bit<31>.
    RRX can optionally update the condition flags based on the result. In that case, bit<0> is shifted into the carry
    flag.

    Input:  Rm      register that will be shifted right by one place, with the carry flag shifted into bit<31>
            Rd      destination register
            S       if set will affect the status register
*/
void executeRRXT1(uint32_t Rm, uint32_t Rd, uint32_t S)
{
  coreReg[Rd] = executeRRX(coreReg[Rm], S);;

  if(S == 1)
  {
    updateZeroFlag(coreReg[Rd]);
    updateNegativeFlag(coreReg[Rd]);
  }
}
