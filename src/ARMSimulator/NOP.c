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
