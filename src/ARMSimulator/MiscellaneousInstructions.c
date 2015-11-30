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


#include "MiscellaneousInstructions.h"
#include <assert.h>
#include "ARMRegisters.h"
#include "getAndSetBits.h"
#include "StatusRegisters.h"
#include "ITandHints.h"
#include "ConditionalExecution.h"


/*DSB Encoding T1

  DSB<c> #<option>

   31 30 29 28 27 26 25 24 23 22 21 20 19 18 17 16 15 14 13 12 11 10 9 8 7 6 5 4 3 2 1 0
  |1   1  1  1  0| 0| 1  1  1| 0  1| 1| 1  1  1  1| 1  0| 0| 0| 1  1 1 1|0 1 0 0| option|

where:
        <c><q>        See Standard assembler syntax fields on page A6-7.

        <opt>         Specifies an optional limitation on the DSB operation. Values are:
        
                      SY DSB operation ensures completion of all accesses, encoded as option == '1111'. Can be
                      omitted.
                      
                      All other encodings of option are reserved. The corresponding instructions execute as system (SY)
                      DSB operations, but software must not rely on this behavior.
*/
void DSB(uint32_t instruction)
{

  if(inITBlock())
  {
    if( checkCondition(cond) )
    {
      //Implementation is empty here because it is unknown
    }
    
    shiftITState();
  }
  else
  {
    //Implementation is empty here because it is unknown
  }

  coreReg[PC] += 4;
}


/* ISB Encoding T1

   ISB<c> {#<option>}
   
   31 30 29 28 27 26 25 24 23 22 21 20 19 18 17 16 15 14 13 12 11 10 9 8 7 6 5 4 3 2 1 0
  |1   1  1  1  0| 0| 1  1  1| 0  1| 1| 1  1  1  1| 1  0| 0| 0| 1  1 1 1|0 1 1 0| option|

  t => type

where:
          <c><q>    See Standard assembler syntax fields on page A6-7.

          <opt>     Specifies an optional limitation on the ISB operation. Permitted values are:
                    SY Full system ISB operation, encoded as option == '1111'. Can be omitted.
                    All other encodings of option are RESERVED. The corresponding instructions execute as full system
                    ISB operations, but should not be relied upon by software.
*/
void ISB(uint32_t instruction)
{

 if(inITBlock())
 {
    if( checkCondition(cond) )
    {
      //Implementation is empty here because it is unknown
    }
    
    shiftITState();
 }
 else
 {
   //Implementation is empty here because it is unknown
 }

  coreReg[PC] += 4;
}

