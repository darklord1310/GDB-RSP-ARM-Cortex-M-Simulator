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


#include "VLDR.h"
#include "getAndSetBits.h"
#include "getMask.h"


/* VSTM Encoding T1 and T2
    
      Floating-point Store Register stores a single extension register to memory, using an address from an ARM core
      register, with an optional offset.
  
    VSTR<c> <Dd>, [<Rn>{, #+/-<imm>}]
    VSTR<c> <Sd>, [<Rn>{, #+/-<imm>}]

31 30 29 28 27 26 25 24 23 22 21 20 19 18 17 16 15 14 13 12 11 10 9 8 7 6 5 4 3 2 1 0
|1  1  1  0| 1  1  0  1| U  D  0  0|     Rn    |     Vd    | 1  0 1 X|      imm8     |

where :
          .32, .64                    Optional data size specifiers.
          
          <Dd>                        The source floating-point register for a doubleword store.
          
          <Sd>                        The source floating-point register for a singleword store.
          
          <Rn>                        The base register. The SP can be used.
          
          +/-                         Is + or omitted if the immediate offset is to be added to the base register value (add == TRUE), or – if
                                      it is to be subtracted (add == FALSE). #0 and #-0 generate different instructions.
                                      
          <imm>                       The immediate offset used to form the address. Values are multiples of 4 in the range 0-1020. <imm>
                                      can be omitted, meaning an offset of +0.
*/
void VLDR(uint32_t instruction)
{ 
  uint32_t U = getBits(instruction,23,23);
  uint32_t D = getBits(instruction,22,22);
  uint32_t Rn = getBits(instruction,19,16);
  uint32_t Vd = getBits(instruction,15,12);
  uint32_t imm8 = getBits(instruction,7,0);
  uint32_t imm32 = imm8 << 2;
  uint32_t singleOrDoublePrecision = getBits(instruction,8,8);
  uint32_t d;
  
  executeFPUChecking();
  
  if(singleOrDoublePrecision == 1)
    d = (D << 4) | Vd;
  else
    d = (Vd << 1) | D;
  
  if(inITBlock())
  {
    if( checkCondition(cond) )
      executeFPStore(U, d, !singleOrDoublePrecision, imm32, Rn);
    
    shiftITState();
  }
  else
    executeFPStore(U, d, !singleOrDoublePrecision, imm32, Rn);

  coreReg[PC] += 4;
}











