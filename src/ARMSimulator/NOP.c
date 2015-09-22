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

#include "NOP.h"
#include "ITandHints.h"
#include "StatusRegisters.h"
#include "ARMRegisters.h"
#include "getAndSetBits.h"
#include "getMask.h"
#include "ModifiedImmediateConstant.h"
#include "ConditionalExecution.h"
#include "MemoryBlock.h"
#include <stdio.h>


/*NOP Encoding T1
  No Operation does nothing.
  
    NOP<c>
      
  31 30 29 28 27 26 25 24 23 22 21 20 19 18 17 16 15 14 13 12 11 10 9 8 7 6 5 4 3 2 1 0
  |1  0  1  1| 1  1  1  1| 0  0  0  0| 0  0  0  0|               unused                |

  setflags = FALSE

*/
void NOPT1()
{
  if(inITBlock())
  {
    if( checkCondition(cond) )
    {}
    
    shiftITState();
    coreReg[PC] += 2;
  }
  else
    coreReg[PC] += 2;
}


/* NOP Encoding T2

   NOP<c>.W

   31 30 29 28 27 26 25 24 23 22 21 20 19 18 17 16 15 14 13 12 11 10 9 8 7 6 5 4 3 2 1 0
  |1  1  1  1  0 |S| 1  1  1 |0  1 |0| 1  1  1  1 |1  0 |0||0||0| 0  0 0|0 0 0 0 0 0 0 0|

where:
          <c><q>        See Standard assembler syntax fields on page A6-7.
*/
void NOPT2(uint32_t instruction)
{
  if(inITBlock())
  {
    if( checkCondition(cond) )
    {}
    
    shiftITState();
  }

  coreReg[PC] += 4;
}
