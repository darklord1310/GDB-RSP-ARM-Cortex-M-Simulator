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


#include "VCVTandVCVTR.h"
#include "getAndSetBits.h"
#include "getMask.h"



/* VCVT, VCVTR (between floating-point and integer)
    
    Floating-point Convert (between floating-point and integer) converts a value in a register from floating-point to a
    32-bit integer, or from a 32-bit integer to floating-point, and places the result in a second register.
  
    VCVT{R}<c>.S32.F32 <Sd>, <Sm>
    VCVT{R}<c>.U32.F32 <Sd>, <Sm>
    VCVT<c>.F32.<Tm> <Sd>, <Sm>

31 30 29 28 27 26 25 24 23 22 21 20 19 18 17 16 15 14 13 12 11 10 9  8 7  6 5 4 3 2 1 0
|1  1  1  1| 1  1  1  0  1| D| 1  1  1  1|  RM |     Vd    | 1  0 1|sz op 1 M 0|   Vm  |

where :
          R             If R is specified, the operation uses the rounding mode specified by the FPSCR. Encoded as op = 0.
                        If R is omitted. the operation uses the Round towards Zero rounding mode. For syntaxes in which R
                        is optional, op is encoded as 1 if R is omitted.
                        
          <c>, <q>      See Standard assembler syntax fields on page A7-175.
          
          <Tm>          The data type for the operand. It must be one of:
                            S32 Encoded as op = 1.
                            U32 Encoded as op = 0.
                            
          <Sd>, <Sm>    The destination register and the operand register, for a single-precision operand or result.
          
          <Sd>, <Dm>    The destination register and the operand register, for a double-precision operand.
          
          <Dd>, <Sm>    The destination register and the operand register, for a double-precision result.
*/
void VCVTandVCVTR(uint32_t instruction)
{
  uint32_t Vd = getBits(instruction,15,12);
  uint32_t Vm = getBits(instruction,3,0);
  uint32_t sz = getBits(instruction,8,8);
  uint32_t M = getBits(instruction,5,5);
  uint32_t D = getBits(instruction,22,22);
  uint32_t op = getBits(instruction,7,7);
  uint32_t RM = getBits(instruction,17,16);
  uint32_t d = determineRegisterBasedOnSZ(D, Vd, sz);
  uint32_t m = determineRegisterBasedOnSZ(M, Vm, sz);
  
  executeFPUChecking();
  
  if(inITBlock())
  {
    if( checkCondition(cond) )
    {
      if(sz == 1)
        ThrowError();                           //undefined instruction if sz == 1 in FPv4-SP architecture
      else
        writeSinglePrecision(d, FPNeg(fpuSinglePrecision[m], 32 ) );
    }
    
    shiftITState();
  }
  else
  {
    if(sz == 1)
      ThrowError();                           //undefined instruction if sz == 1 in FPv4-SP architecture
    else
      writeSinglePrecision(d, FPNeg(fpuSinglePrecision[m], 32 ) );
  }

  coreReg[PC] += 4;  
}