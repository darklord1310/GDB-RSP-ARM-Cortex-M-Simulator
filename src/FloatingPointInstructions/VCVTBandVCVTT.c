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
|1  1  1  0| 1  1  1  0  1| D| 1  1  0  0  1 op|     Vd    | 1  0 1 sz T 1 M 0|   Vm  |

where :
        <y>           Specifies which half of the operand register <Sm> or destination register <Sd> is used for the operand
                      or destination:
                          B     VCVTB. Encoded as T = 0. Instruction uses the bottom half of the register, bits[15:0].
                          T     VCVTT. Encoded as T = 1. Instruction uses the top half of the register, bits[31:16].
                      
        <c>, <q>      See Standard assembler syntax fields on page A7-175.
        
        <Sd>          The single-precision destination register.
        
        <Sm>          The single-precision operand register.
        
        <Dd>          The double-precision destination register.
        
        <Dm>          The double-precision operand register
*/
void VCVTBandVCVTT(uint32_t instruction)
{
  uint32_t Vd = getBits(instruction,15,12);
  uint32_t Vm = getBits(instruction,3,0);
  uint32_t op = getBits(instruction,16,16);
  uint32_t sz = getBits(instruction,8,8);
  uint32_t M = getBits(instruction,5,5);
  uint32_t D = getBits(instruction,22,22);
  uint32_t T = getBits(instruction,7,7);  
  uint32_t d, m, temp;
  int lowBit;
  
  if(sz == 1)
  {
    if(op == 0)
    {
      d = (D << 4) | Vd;
      m = (Vm << 1) | M;
    }
    else
    {
      d = (Vd << 1) | D;
      m = (M << 4) | Vm;
    }
  }
  else
  {
    d = (Vd << 1) | D;
    m = (Vm << 1) | M;
  }
  
  if(T == 1)
    lowBit = 16;
  else 
    lowBit = 0;

  executeFPUChecking();
  
  if(inITBlock())
  {
    if( checkCondition(cond) )
    {
      if(op == 0)   // convert from half precision
      {
        if(sz == 1)
          ThrowError();                           //undefined instruction if sz == 1 in FPv4-SP architecture
        else
          writeSinglePrecision(d, FPHalfToSingle((uint16_t)getBits(fpuSinglePrecision[m],lowBit+15,lowBit), 32) );
      }
      else
      {
        if(sz == 1)
          ThrowError();                           //undefined instruction if sz == 1 in FPv4-SP architecture
        else
        {
          if(lowBit == 0)
          {
            temp = FPSingleToHalf(fpuSinglePrecision[m], fPSCR);    //use a 32bits temp to store the 16bits converted value                                                               
            writeSinglePrecision(d, setBits(temp, 0x7FFF, 31,16) ); //and make the upper 16bits becomes 0x7FFF
          }
          else
          {
            temp = FPSingleToHalf(fpuSinglePrecision[m], fPSCR);            //use a 32bits temp to store the 16bits converted value
            writeSinglePrecision(d, setBits( temp << 16, 0xFFFF, 15, 0) );  //and make the lower 16bits becomes 0xFFFF
          }
        }
      }
    }
    
    shiftITState();
  }
  else
  {
    if(op == 0)   // convert from half precision
    {
      if(sz == 1)
        ThrowError();                           //undefined instruction if sz == 1 in FPv4-SP architecture
      else
        writeSinglePrecision(d, FPHalfToSingle((uint16_t)getBits(fpuSinglePrecision[m],lowBit+15,lowBit), 32) );
    }
    else
    {
      if(sz == 1)
        ThrowError();                           //undefined instruction if sz == 1 in FPv4-SP architecture
      else
      {
        if(lowBit == 0)
        {
          temp = FPSingleToHalf(fpuSinglePrecision[m], fPSCR);    //use a 32bits temp to store the 16bits converted value    
          writeSinglePrecision(d, setBits(temp, 0x7FFF, 31,16) ); //and make the upper 16bits becomes 0x7FFF
        }
        else
        {
          temp = FPSingleToHalf(fpuSinglePrecision[m], fPSCR);            //use a 32bits temp to store the 16bits converted value
          writeSinglePrecision(d, setBits( temp << 16, 0xFFFF, 15, 0) );  //and make the lower 16bits becomes 0xFFFF
        }
      }
    }
  }

  coreReg[PC] += 4;  
}