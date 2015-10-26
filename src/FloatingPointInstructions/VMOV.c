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


#include "VMOV.h"
#include "getAndSetBits.h"
#include "getMask.h"



/* VMOV (between ARM core register and single-precision register)

      VMOV<c> <Sn>, <Rt>
      VMOV<c> <Rt>, <Sn>

31 30 29 28 27 26 25 24 23 22 21 20 19 18 17 16 15 14 13 12 11 10 9 8 7 6 5 4 3 2 1 0
|1  1  1  0| 1  1  1  0| 0  0  0|op|     Vn    |     Rt    | 1  0 1 0|N|0 0|1|0 0 0 0|

where :
            <Sn>      The single-precision register.
            
            <Rt>      The ARM core register.
*/
void VMOVBetweenCoreRegAndfpuSReg(uint32_t instruction)
{ 
  uint32_t Vn = getBits(instruction, 19, 16);
  uint32_t N = getBits(instruction, 7, 7);
  uint32_t Rt = getBits(instruction, 15, 12);
  uint32_t n = (Vn << 1) | N;
  uint32_t op = getBits(instruction, 20, 20);
  
  executeFPUChecking();
  
  if(inITBlock())
  {
    if( checkCondition(cond) )
    {
      if(op == 1)
        writeToCoreRegisters(Rt,  fpuSinglePrecision[n]);
      else
        writeSinglePrecision(n, coreReg[Rt]);
    }
    shiftITState();
  }
  else
  {
    if(op == 1)
      writeToCoreRegisters(Rt,  fpuSinglePrecision[n]);
    else
      writeSinglePrecision(n, coreReg[Rt]);
  }

  coreReg[PC] += 4;
}



/* Floating-point Move (between two ARM core registers and two single-precision registers)

    VMOV<c> <Sm>, <Sm1>, <Rt>, <Rt2>
    VMOV<c> <Rt>, <Rt2>, <Sm>, <Sm1>

31 30 29 28 27 26 25 24 23 22 21 20 19 18 17 16 15 14 13 12 11 10 9 8 7 6 5 4 3 2 1 0
|1  1  1  0| 1  1  0  0| 0  1  0|op|     Rt2   |     Rt    | 1  0 1 0|0 0|M|1|   Vm  |

where :
          <Sm>            The first single-precision register.
          
          <Sm1>           The second single-precision register. This is the next single-precision register after <Sm>.
          
          <Rt>            The ARM core register that <Sm> is transferred to or from.
          
          <Rt2>           The ARM core register that <Sm1> is transferred to or from.
*/
void VMOVBetweenCoreRegAndDoubleFpuReg(uint32_t instruction)
{
  uint32_t Vm = getBits(instruction, 3, 0);
  uint32_t M = getBits(instruction, 5, 5);
  uint32_t Rt = getBits(instruction, 15, 12);
  uint32_t Rt2 = getBits(instruction, 19, 16);
  uint32_t op = getBits(instruction, 20, 20);
  uint32_t m = (Vm << 1) | M;
  
  executeFPUChecking();
  
  if(inITBlock())
  {
    if( checkCondition(cond) )
    {
      if(op == 1)
      {
        writeToCoreRegisters(Rt,  fpuSinglePrecision[m]);
        writeToCoreRegisters(Rt2, fpuSinglePrecision[m+1]);
      }
      else
      {
        writeSinglePrecision(m, coreReg[Rt]);
        writeSinglePrecision(m+1, coreReg[Rt2]);
      }
    }
    shiftITState();
  }
  else
  {
    if(op == 1)
    { 
      writeToCoreRegisters(Rt,  fpuSinglePrecision[m]);
      writeToCoreRegisters(Rt2, fpuSinglePrecision[m+1]);
    }
    else
    { 
      writeSinglePrecision(m, coreReg[Rt]);
      writeSinglePrecision(m+1, coreReg[Rt2]);
    }
  }

  coreReg[PC] += 4;
}





/* VMOV (ARM core register to scalar)

    VMOV<c>.<size> <Dd[x]>, <Rt>

31 30 29 28 27 26 25 24 23 22 21 20 19 18 17 16 15 14 13 12 11 10 9 8 7 6 5 4 3 2 1 0
|1  1  1  0| 1  1  1  0| 0  0  H  0|     Vd    |     Rt    | 1  0 1 1|D|0 0|1|0 0 0 0|

where :
          <size>          The data size. It must be either 32 or omitted.
          
          <Dd[x]>         The doubleword register and required word. x is 1 for the top half of the register, or 0 for the bottom
                          half, and is encoded in H.
                          
          <Rt>            The source ARM core register.
*/
void VMOVBetweenScalarAndCoreReg(uint32_t instruction)
{
  uint32_t Vd = getBits(instruction, 19, 16);
  uint32_t H = getBits(instruction, 21, 21);
  uint32_t Rt = getBits(instruction, 15, 12);
  uint32_t D = getBits(instruction,7,7);
  uint32_t d = (Vd << 1) | H;
  
  executeFPUChecking();
  
  if(inITBlock())
  {
    if( checkCondition(cond) )
      writeSinglePrecision(d, coreReg[Rt]);
    
    shiftITState();
  }
  else
    writeSinglePrecision(d, coreReg[Rt]);

  coreReg[PC] += 4;  
}






/* VMRS
    
   Move to ARM core register from floating-point Special Register moves the value of the FPSCR to a
   general-purpose register, or the values of the FCSR flags to the APSR
  
    VMRS<c> <Rt>, FPSCR

31 30 29 28 27 26 25 24 23 22 21 20 19 18 17 16 15 14 13 12 11 10 9 8 7 6 5 4 3 2 1 0
|1  1  1  0| 1  1  1  0| 0  0  H  0|     Vd    |     Rt    | 1  0 1 1|D|0 0|1|0 0 0 0|

where :
          <size>          The data size. It must be either 32 or omitted.
          
          <Dd[x]>         The doubleword register and required word. x is 1 for the top half of the register, or 0 for the bottom
                          half, and is encoded in H.
                          
          <Rt>            The source ARM core register.
*/
void VMSR(uint32_t instruction)
{
  
}