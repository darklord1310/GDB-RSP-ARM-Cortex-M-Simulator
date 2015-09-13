/*  
    Program Name       : GDB RSP and ARM Simulator
    Author             : Wong Yan Yin, Jackson Teh Ka Sing 
    Copyright (C) 2015 TARUC

    This file is part of GDB RSP and ARM Simulator.

    GDB RSP and ARM Simulator is free software, you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    GDB RSP and ARM Simulator is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY, without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with GDB RSP and ARM Simulator.  If not, see <http://www.gnu.org/licenses/>.

*/



#include "SUBSPImmediate.h"
#include "ITandHints.h"
#include "StatusRegisters.h"
#include "ARMRegisters.h"
#include "getAndSetBits.h"
#include "getMask.h"
#include "ModifiedImmediateConstant.h"
#include "ConditionalExecution.h"
#include "MemoryBlock.h"
#include <stdio.h>


/*SUB (SP minus immediate) Encoding T1
    SUB<c> SP,SP,#<imm7>
      
  31 30 29 28 27 26 25 24 23 22 21 20 19 18 17 16 15 14 13 12 11 10 9 8 7 6 5 4 3 2 1 0
  |1  0  1  1| 0  0  0  0| 1|         imm7       |                unused               |

  setflags = FALSE
  
where:
          S               If present, specifies that the instruction updates the flags. Otherwise, the instruction does not
                          update the flags.
                          
          <c><q>          See Standard assembler syntax fields on page A6-7.
          
          <Rd>            Specifies the destination register. If <Rd> is omitted, this register is SP.
          
          <const>         Specifies the immediate value to be added to the value obtained from SP. Allowed values
                          are multiples of 4 in the range 0-508 for encoding T1 and any value in the range 0-4095 for
                          encoding T3. See Modified immediate constants in Thumb instructions on page A5-15 for
                          the range of allowed values for encoding T2.
                          
          When both 32-bit encodings are available for an instruction, encoding T2 is preferred to
          encoding T3 (if encoding T3 is required, use the SUBW syntax).
*/
void SUBSPImmediateT1(uint32_t instruction)
{
  uint32_t imm7 = getBits(instruction,22,16);
  
  if(inITBlock())
  {
    if( checkCondition(cond) )
      coreReg[SP] = coreReg[SP] - ( imm7 << 2);
    
    shiftITState();
    coreReg[PC] += 2;
  }
  else
  {
    coreReg[SP] = coreReg[SP] - ( imm7 << 2);
    coreReg[PC] += 2;
  }
  
  
}
