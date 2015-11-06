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


#include "VMSR.h"
#include "getAndSetBits.h"
#include "getMask.h"



/* VMRS
    
    Move to floating-point Special Register from ARM core register moves the value of a general-purpose register to
    the FPSCR.
  
    VMSR<c> FPSCR, <Rt>

31 30 29 28 27 26 25 24 23 22 21 20 19 18 17 16 15 14 13 12 11 10 9 8 7 6 5 4 3 2 1 0
|1  1  1  0| 1  1  1  0| 1  1  1 0| 0  0  0  1|     Rt    | 1  0 1 0|0 0 0 1|0 0 0 0|

where :
              <Rt> The general-purpose register to be transferred to the FPSCR.

*/
void VMSR(uint32_t instruction)
{
  uint32_t Rt = getBits(instruction,15,12);
  uint32_t mask = 0xf7C0009f;                  //this mask is to mask off the bits which will not be affected by this instruction
  uint32_t L = getBits(instruction,20,20);
  uint32_t newFPSCR = coreReg[Rt] & mask;
  
  executeFPUChecking();
  
  if(inITBlock())
  {
    if( checkCondition(cond) )
      writeToCoreRegisters(fPSCR, newFPSCR);
    
    shiftITState();
  }
  else
    writeToCoreRegisters(fPSCR, newFPSCR);

  coreReg[PC] += 4;  
}