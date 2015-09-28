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


#include "CBZandCBNZ.h"
#include "ITandHints.h"
#include "StatusRegisters.h"
#include "ARMRegisters.h"
#include "getAndSetBits.h"
#include "getMask.h"
#include "ModifiedImmediateConstant.h"
#include "ConditionalExecution.h"
#include "MemoryBlock.h"
#include <stdio.h>


/*Compare and Branch on Non-Zero and Compare and Branch on Zero Encoding T1
    CB{N}Z <Rn>,<label>
      
  31 30 29 28 27 26 25 24 23 22 21 20 19 18 17 16 15 14 13 12 11 10 9 8 7 6 5 4 3 2 1 0
  |1  0  1  1|op| 0  i  1|      imm5    |    Rn  |               unused                |
  
where:
            <c><q>                See Standard assembler syntax fields on page A6-7.
            
            <Rn>                  The first operand register.
            
            <label>               The label of the instruction that is to be branched to. The assembler calculates the required
                                  value of the offset from the PC value of the CB{N}Z instruction to this label, then selects an
                                  encoding that will set imm32 to that offset. Allowed offsets are even numbers in the range 0
                                  to 126.
*/
void CBNZorCBZ(uint32_t instruction)
{
  uint32_t op = getBits(instruction, 27,27);
  uint32_t i = getBits(instruction, 25,25);
  uint32_t imm5 = getBits(instruction, 23,19);
  uint32_t Rn = getBits(instruction, 18, 16);
  
  uint32_t imm32 = ( ( i << 5 ) | imm5 ) << 1 ;

  if(   ( op == 0 && coreReg[Rn] == 0)   ||  ( op == 1 && coreReg[Rn] != 0)     )
  {
    coreReg[PC] = coreReg[PC] + imm32 + 4;
    coreReg[PC] = coreReg[PC] & 0xfffffffe;
  }
  
}