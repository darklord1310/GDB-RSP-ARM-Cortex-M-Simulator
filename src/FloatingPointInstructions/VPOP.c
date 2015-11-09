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


#include "VPOP.h"
#include "VLDM.h"
#include "getAndSetBits.h"
#include "getMask.h"


/* VPOP Encoding T1 and T2
    
      Floating-point Pop Registers loads multiple consecutive floating-point registers from the stack.
  
    VPOP <list>

31 30 29 28 27 26 25 24 23 22 21 20 19 18 17 16 15 14 13 12 11 10 9 8 7 6 5 4 3 2 1 0
|1  1  1  0| 1  1  0  0  1  D  1  1| 1  1  0  1|     Vd    | 1  0 1 X|      imm8     |

where :
          <size>              An optional data size specifier. If present, it must be equal to the size in bits, 32 or 64, of the
                              floating-point registers in <list>.
                              
          <list>              The extension registers to be loaded, as a list of consecutively numbered doubleword or
                              single-precision floating-point registers, separated by commas and surrounded by brackets.
                              <list> must contain at least one floating-point register, and not more than sixteen.
*/
void VPOP(uint32_t instruction)
{ 
  uint32_t D = getBits(instruction,22,22);
  uint32_t Vd = getBits(instruction,15,12);
  uint32_t imm8 = getBits(instruction,7,0);
  uint32_t imm32 = imm8 << 2;
  uint32_t singleOrDoublePrecision = getBits(instruction,8,8);
  uint32_t d, regs;
  uint32_t address = coreReg[SP];
  coreReg[SP]+=imm32;
  
  executeFPUChecking();
  
  if(singleOrDoublePrecision == 1)
  {
    d = (D << 4) | Vd;
    regs = imm8 / 2;
  }
  else
  {
    d = (Vd << 1) | D;
    regs = imm8;
  }
  
  if(inITBlock())
  {
    if( checkCondition(cond) )
      loadFPMultiple(address, d, regs, !singleOrDoublePrecision);
    
    shiftITState();
  }
  else
    loadFPMultiple(address, d, regs, !singleOrDoublePrecision);

  coreReg[PC] += 4;
}











