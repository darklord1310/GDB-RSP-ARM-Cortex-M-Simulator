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


#include "SignedAndUnsignedSaturate.h"


/* Signed Saturate Encoding T1

SSAT<c> <Rd>,#<imm5>,<Rn>{,<shift>}

31 30 29 28 27 26 25 24 23 22 21 20 19 18 17 16 15 14 13 12 11 10 9 8 7 6 5 4 3 2 1 0
|1  1  1  1 0 |0| 1  1 |0  0||sh|0|     Rn     |0|  imm3   |    Rd  |imm2|0| sat_imm |

where :
          <c><q>        See Standard assembler syntax fields on page A6-7.

          <Rd>          Specifies the destination register.

          <imm5>        Specifies the bit position for saturation, in the range 1 to 32.

          <Rn>          Specifies the register that contains the value to be saturated.

          <shift>       Specifies the optional shift. If <shift> is omitted, LSL #0 is used.
                        If present, it must be one of:
                        LSL #N N must be in the range 0 to 31.
                        ASR #N N must be in the range 1 to 31.
*/
void SSATT1(uint32_t instruction)
{
  uint32_t Rd = getBits(instruction, 11, 8);
  uint32_t Rn = getBits(instruction, 19, 16);
  uint32_t sat_imm = getBits(instruction, 5, 0);    // imm5
  uint32_t imm2 = getBits(instruction, 7, 6);
  uint32_t imm3 = getBits(instruction, 14, 12);
  uint32_t sh = getBits(instruction, 21, 21);      // 0 => LSL, 1 => ASR

  uint32_t shiftImm = (imm3 << 2) | imm2;          // Shift immediate (N)
  assert((sh == 1 && shiftImm > 0) || sh == 0);    // ASR #N N must be in the range 1 to 31

  if(inITBlock())
  {
    if( checkCondition(cond) )
      executeSSAT(Rd, Rn, sat_imm, sh, shiftImm);
    shiftITState();
  }
  else
    executeSSAT(Rd, Rn, sat_imm, sh, shiftImm);

  coreReg[PC] += 4;
}


/* This instruction saturates an optionally-shifted signed value to a selectable signed range.
   The Q flag is set if the operation saturates.

   Input: Rn                register that contains the value to be saturated
          Rd                destination register
          immediate         immediate value which will saturated signed value to a selectable signed range
          shiftDirection    logical left or right shift
          shiftImmediate    immediate value which will shift Rn
*/
void executeSSAT(uint32_t Rd, uint32_t Rn, uint32_t immediate, uint32_t shiftDirection, uint32_t shiftImmediate)
{
  int32_t shiftRn, temp, max, min, sign = 1;       // max indicate max range of saturated value
                                                   // min indicate min range of saturated value
                                                   // sign indicate sign or unsigned

  max = (int32_t)(pow(2, immediate + 1) / 2) - 1;
  min = -(max + 1);

  if(shiftDirection)
    shiftRn = executeASR(shiftImmediate, coreReg[Rn], 0);
  else
    shiftRn = coreReg[Rn] << shiftImmediate;

  temp = (shiftRn < min) ? min: (shiftRn > max ? max: shiftRn);
  writeToCoreRegisters(Rd , temp );

  updateQFlag(max, min, shiftRn, sign);
}


/* Unsigned Saturate Encoding T1

USAT<c> <Rd>,#<imm5>,<Rn>{,<shift>}

31 30 29 28 27 26 25 24 23 22 21 20 19 18 17 16 15 14 13 12 11 10 9 8 7 6 5 4 3 2 1 0
|1  1  1  1 0 |0| 1  1 |1  0||sh|0|     Rn     |0|  imm3   |    Rd  |imm2|0| sat_imm |

where :
          <c><q>        See Standard assembler syntax fields on page A6-7.

          <Rd>          Specifies the destination register.

          <imm5>        Specifies the bit position for saturation, in the range 1 to 32.

          <Rn>          Specifies the register that contains the value to be saturated.

          <shift>       Specifies the optional shift. If <shift> is omitted, LSL #0 is used.
                        If present, it must be one of:
                        LSL #N N must be in the range 0 to 31.
                        ASR #N N must be in the range 1 to 31.
*/
void USATT1(uint32_t instruction)
{
  uint32_t Rd = getBits(instruction, 11, 8);
  uint32_t Rn = getBits(instruction, 19, 16);
  uint32_t sat_imm = getBits(instruction, 5, 0);    // imm5
  uint32_t imm2 = getBits(instruction, 7, 6);
  uint32_t imm3 = getBits(instruction, 14, 12);
  uint32_t sh = getBits(instruction, 21, 21);      // 0 => LSL, 1 => ASR

  uint32_t shiftImm = (imm3 << 2) | imm2;          // Shift immediate (N)
  assert((sh == 1 && shiftImm > 0) || sh == 0);    // ASR #N N must be in the range 1 to 31

  if(inITBlock())
  {
    if( checkCondition(cond) )
      executeUSAT(Rd, Rn, sat_imm, sh, shiftImm);
    shiftITState();
  }
  else
    executeUSAT(Rd, Rn, sat_imm, sh, shiftImm);

  coreReg[PC] += 4;
}


/* This instruction saturates an optionally-shifted signed value to a selectable signed range.
   The Q flag is set if the operation saturates.

   Input: Rn                register that contains the value to be saturated
          Rd                destination register
          immediate         immediate value which will saturated signed value to a selectable signed range
          shiftDirection    logical left or right shift
          shiftImmediate    immediate value which will shift Rn
*/
void executeUSAT(uint32_t Rd, uint32_t Rn, uint32_t immediate, uint32_t shiftDirection, uint32_t shiftImmediate)
{
  int32_t shiftRn, temp, max, min, sign = 1;       // max indicate max range of saturated value
                                                   // min indicate min range of saturated value
                                                   // sign indicate sign or unsigned

  max = (int32_t)(pow(2, immediate + 1) / 2) - 1;
  min = 0;

  if(shiftDirection)
    shiftRn = executeASR(shiftImmediate, coreReg[Rn], 0);
  else
    shiftRn = coreReg[Rn] << shiftImmediate;

  temp = (shiftRn > max) ? max: (shiftRn < 0 ? 0: shiftRn);
  writeToCoreRegisters(Rd , temp );

  updateQFlag(max, min, shiftRn, sign);
}
