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


#include "CLZ.h"
#include "ITandHints.h"
#include "StatusRegisters.h"
#include "ARMRegisters.h"
#include "getAndSetBits.h"
#include "getMask.h"
#include "ConditionalExecution.h"


/*Count Leading Zeros Encoding T1

  CLZ<c> <Rd>,<Rm>

  31 30 29 28 27 26 25 24 23 22 21 20 19 18 17 16 15 14 13 12 11 10 9 8 7 6 5 4 3 2 1 0
 |1  1  1  1  1 |0  1  0 |1| 0  1  1 |     Rm    |1  1  1  1 |    Rd   |1|0 0 0|   Rm  |

where:
          <c><q>            See Standard assembler syntax fields on page A6-7.

          <Rd>              Specifies the destination register.

          <Rm>              Specifies the register that contains the operand. Its number must be encoded twice in
                            encoding T2, in both the Rm and Rm2 fields.

*/
void CLZT1(uint32_t instruction)
{
  uint32_t Rm = getBits(instruction, 3, 0);
  uint32_t Rm2 = getBits(instruction, 19, 16);
  uint32_t Rd = getBits(instruction, 11, 8);

  if(inITBlock())
  {
    if( checkCondition(cond) )
      executeCLZ(Rm, Rd);

    shiftITState();
  }
  else
    executeCLZ(Rm, Rd);

  coreReg[PC] += 4;
}


/* This instruction returns the number of binary zero bits before the first binary one bit in a value.

   Input:   Rd      destination register.
            Rm      register that contains the operand.
*/
void executeCLZ(uint32_t Rm, uint32_t Rd)
{
  uint32_t result = highestSetBit(coreReg[Rm]);
  writeToCoreRegisters(Rd, 32 - 1 - result );
}


/* This function will calculate the maximum bit number of any of its bits that are ones. If all of its bits are zeros,
 * return -1.
 *
 * Input:
 *          value           the value that is going to be evaluate
 *
 * Return
 *          the the maximum bit number of any of its bits that are ones
 */
uint32_t highestSetBit(uint32_t value)
{
  int i, numberOfSetBit = 0;

  if(value == 0x0)
    return - 1;

  for(i = 0; i < 32; i++)
  {
    if(getBits(value, i ,i) == 1)
      numberOfSetBit++;
  }

  return numberOfSetBit;
}
