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



#include "BFIandBFC.h"

/* Bit Field Insert Encoding T1

BFI<c> <Rd>,<Rn>,#<lsb>,#<width>

31 30 29 28 27 26 25 24 23 22 21 20 19 18 17 16 15 14 13 12 11 10 9 8 7 6 5 4 3 2 1 0
|1  1  1  1 0 |0| 1  1 |0  1  1 |0|     Rn     |0|  imm3   |    Rd  |imm2|0|   msb  |

where :
          <c><q>        See Standard assembler syntax fields on page A6-7.

          <Rd>          Specifies the destination register.

          <Rn>          Specifies the source register.

          <lsb>         Specifies the least significant destination bit, in the range 0 to 31. This determines the
                        required value of lsbit.

          <width>       Specifies the number of bits to be copied, in the range 1-32-<lsb>. The required value of
                        msbit is <lsb>+<width>-1.

This instruction copies any number of low order bits from a register into the same number of adjacent bits at
any position in the destination register.
*/
void BFIT1(uint32_t instruction)
{
  uint32_t Rd = getBits(instruction, 11, 8);
  uint32_t Rn = getBits(instruction, 19, 16);
  uint32_t msbit = getBits(instruction, 5, 0);              // msb of the Rd to be inserted
  uint32_t imm2 = getBits(instruction, 7, 6);
  uint32_t imm3 = getBits(instruction, 14, 12);

  uint32_t lsbit = (imm3 << 2) | imm2;                      // lsb of the Rd to be inserted
  uint32_t temp = getBits(coreReg[Rn], msbit - lsbit, 0);   // value of Rn that will insert to Rd

  if(inITBlock())
  {
    if( checkCondition(cond) )
      coreReg[Rd] = setBits(coreReg[Rd], temp, msbit, lsbit);
    shiftITState();
  }
  else
    coreReg[Rd] = setBits(coreReg[Rd], temp, msbit, lsbit);

  coreReg[PC] += 4;
}


/* Bit Field Clear Encoding T1

BFC<c> <Rd>,#<lsb>,#<width>

31 30 29 28 27 26 25 24 23 22 21 20 19 18 17 16 15 14 13 12 11 10 9 8 7 6 5 4 3 2 1 0
|1  1  1  1 0 |0| 1  1 |0  1  1 |0| 1  1  1  1 |0|  imm3   |    Rd  |imm2|0|   msb  |

where :
          <c><q>        See Standard assembler syntax fields on page A6-7.

          <Rd>          Specifies the destination register.

          <lsb>         Specifies the least significant destination bit, in the range 0 to 31. This determines the
                        required value of lsbit.

          <width>       Specifies the number of bits to be copied, in the range 1-32-<lsb>. The required value of
                        msbit is <lsb>+<width>-1.

This instruction clears any number of adjacent bits at any position in a register, without affecting the other
bits in the register.
*/
void BFCT1(uint32_t instruction)
{
  uint32_t Rd = getBits(instruction, 11, 8);
  uint32_t msbit = getBits(instruction, 5, 0);              // msb of the Rd to be inserted
  uint32_t imm2 = getBits(instruction, 7, 6);
  uint32_t imm3 = getBits(instruction, 14, 12);

  uint32_t lsbit = (imm3 << 2) | imm2;                      // lsb of the Rd to be inserted

  if(inITBlock())
  {
    if( checkCondition(cond) )
      coreReg[Rd] = setBits(coreReg[Rd], 0, msbit, lsbit);
    shiftITState();
  }
  else
    coreReg[Rd] = setBits(coreReg[Rd], 0, msbit, lsbit);

  coreReg[PC] += 4;
}