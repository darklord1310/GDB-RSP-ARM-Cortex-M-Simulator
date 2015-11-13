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


#include "VNEG.h"
#include "getAndSetBits.h"
#include "getMask.h"



/* VNEG
    
   Move to ARM core register from floating-point Special Register moves the value of the FPSCR to a
   general-purpose register, or the values of the FCSR flags to the APSR
  
    VMSR<c> FPSCR, <Rt>
    VMRS<c> <Rt>, FPSCR

31 30 29 28 27 26 25 24 23 22 21 20 19 18 17 16 15 14 13 12 11 10 9 8 7 6 5 4 3 2 1 0
|1  1  1  0| 1  1  1  0| 1  1  1  1| 0  0  0  1|     Rt    | 1  0 1 0|0 0 0 1|0 0 0 0|

where :
          <Rt>      The destination ARM core register. This register can be R0-R14 or APSR_nzcv. APSR_nzcv is
                    encoded as Rt = ’1111’, and the instruction transfers the FPSCR N, Z, C, and V flags to the APSR
                    N, Z, C, and V flags.
*/
void VNEG(uint32_t instruction)
{
  uint32_t Rt = getBits(instruction,15,12);
  uint32_t NZCVbits;
  
  executeFPUChecking();
  
  if(inITBlock())
  {
    if( checkCondition(cond) )
    {
      if(Rt != 0b1111)
        writeToCoreRegisters(Rt, coreReg[fPSCR]);
      else
      {
        NZCVbits = getBits(coreReg[fPSCR],31,28);
        coreReg[xPSR] = setBits(coreReg[xPSR], NZCVbits, 31,28);
      }
    }
    
    shiftITState();
  }
  else
  {
    if(Rt != 0b1111)
      writeToCoreRegisters(Rt, coreReg[fPSCR]);
    else
    {
      NZCVbits = getBits(coreReg[fPSCR],31,28);
      coreReg[xPSR] = setBits(coreReg[xPSR], NZCVbits, 31,28);
    }
  }

  coreReg[PC] += 4;  
  
}