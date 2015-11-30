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


#include "VCVTBandVCVTT.h"
#include "getAndSetBits.h"
#include "getMask.h"



/* VCVTB, VCVTT
    
    Floating-point Convert Bottom and Floating-point Convert Top do one of the following:
    
      • Convert the half-precision value in the top or bottom half of a single-precision register to single-precision
        and write the result to a single-precision register.
        
      • Convert the value in a single-precision register to half-precision and write the result into the top or bottom
        half of a single-precision register, preserving the other half of the target register.
        
      • Convert the half-precision value in the top or bottom half of a single-precision register to double-precision
        and write the result to a double-precision register, without intermediate rounding.
        
      • Convert the value in the double-precision register to half-precision and write the result into the top or bottom
        half of a double-precision register, preserving the other half of the target register, without intermediate
        rounding.
  
  
    VCVTB<c>.F32.F16 <Sd>, <Sm>
    VCVTT<c>.F32.F16 <Sd>, <Sm>
    VCVTB<c>.F16.F32 <Sd>, <Sm>
    VCVTT<c>.F16.F32 <Sd>, <Sm>

31 30 29 28 27 26 25 24 23 22 21 20 19 18 17 16 15 14 13 12 11 10 9  8 7 6 5 4 3 2 1 0
|1  1  1  0| 1  1  1  0  1| D| 1  1| 0  0  0  1|     Vd    | 1  0 1 sz 0 1 M 0|   Vm  |

where :
        <c>, <q>          See Standard assembler syntax fields on page A7-175.
        
        <Sd>, <Sm>        The destination single-precision register and the operand single-precision register.
        
        <Dd>, <Dm>        The destination double-precision register and the operand double-precision register.
*/
void VCVTBandVCVTT(uint32_t instruction)
{
  uint32_t Vd = getBits(instruction,15,12);
  uint32_t Vm = getBits(instruction,3,0);
  uint32_t sz = getBits(instruction,8,8);
  uint32_t M = getBits(instruction,5,5);
  uint32_t D = getBits(instruction,22,22);

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