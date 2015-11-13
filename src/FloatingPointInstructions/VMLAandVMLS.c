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


#include "VMLAandVMLS.h"
#include "getAndSetBits.h"
#include "getMask.h"



/* VMLA, VMLS
    
  Floating-point Multiply Accumulate multiplies two floating-point registers, and accumulates the results into the
  destination floating-point register.
      
      VML<y>{<c>}{<q>}.F32 <Sd>, <Sn>, <Sm> Encoded as sz = 0
      VML<y>{<c>}{<q>}.F64 <Dd>, <Dn>, <Dm> Encoded as sz = 1

      VMLA<c>.F32 <Sd>, <Sn>, <Sm>
      VMLS<c>.F32 <Sd>, <Sn>, <Sm>
      VMLA<c>.F64 <Dd>, <Dn>, <Dm>
      VMLS<c>.F64 <Dd>, <Dn>, <Dm>

31 30 29 28 27 26 25 24 23 22 21 20 19 18 17 16 15 14 13 12 11 10 9  8 7  6 5 4 3 2 1 0
|1  1  1  0| 1  1  1  0  0|D|  0  0|     Vn    |     Vd    | 1  0 1|sz|N|op|M|0|   Vm  |

where :
          <y>                 One of:
                                      A   Specifies VMLA, encoded as op=0.
                                      S   Specifies VMLS, encoded as op=1.
                                  
          <c>, <q>            See Standard assembler syntax fields on page A7-175.
          
          <Sd>, <Sn>, <Sm>    The destination single-precision register and the operand single-precision registers.
          
          <Dd>, <Dn>, <Dm> The destination double-precision register and the operand double-precision registers.
          
*/
void VMLAandVMLS(uint32_t instruction)
{ 
  uint32_t Vn = getBits(instruction,19,16);
  uint32_t Vd = getBits(instruction,15,12);
  uint32_t Vm = getBits(instruction,3,0);
  uint32_t sz = getBits(instruction,8,8);
  uint32_t N = getBits(instruction,7,7);
  uint32_t op = getBits(instruction,6,6);
  uint32_t M = getBits(instruction,5,5);
  uint32_t D = getBits(instruction,22,22);
  uint64_t addend64;
  uint32_t addend32;

  uint32_t d = determineRegisterBasedOnSZ(D, Vd, sz);
  uint32_t n = determineRegisterBasedOnSZ(N, Vn, sz);
  uint32_t m = determineRegisterBasedOnSZ(M, Vm, sz);
  
  executeFPUChecking();
  
  if(inITBlock())
  {
    if( checkCondition(cond) )
    {
      if(sz == 1)
        ThrowError();                           //undefined instruction if sz == 1 in FPv4-SP architecture
      else
      {
        if(op == 0)
          addend32 = FPMulSinglePrecision( fpuSinglePrecision[n], fpuSinglePrecision[m]);
        else
          addend32 = FPNeg( FPMulSinglePrecision( fpuSinglePrecision[n], fpuSinglePrecision[m]), 64);
        
        writeSinglePrecision(d, FPAddSinglePrecision(fpuSinglePrecision[d], addend32) );
      }
    }
    
    shiftITState();
  }
  else
  {
    if(sz == 1)
      ThrowError();                           //undefined instruction if sz == 1 in FPv4-SP architecture
    else
    {
      if(op == 0)
        addend32 = FPMulSinglePrecision( (fpuSinglePrecision[n]), (fpuSinglePrecision[m]) );
      else
        addend32 = FPNeg( FPMulSinglePrecision( fpuSinglePrecision[n], fpuSinglePrecision[m]), 32);

      writeSinglePrecision(d, FPAddSinglePrecision(fpuSinglePrecision[d], addend32) );
    }
  }

  coreReg[PC] += 4;  
}