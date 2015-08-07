#include "BX.h"
#include "ARMRegisters.h"
#include "getAndSetBits.h"
#include "StatusRegisters.h"
#include "ADDSPRegister.h"
#include "ModifiedImmediateConstant.h"
#include "ITandHints.h"
#include "ConditionalExecution.h"
#include <stdio.h>
#include "CException.h"
#include "ErrorSignal.h"


/*Branch and Exchange
 
    BX<c> <Rm> Outside or last in IT block
    
  Branch and Exchange causes a branch to an address and instruction set specified by a register. ARMv7-M
  only supports the Thumb instruction set. An attempt to change the instruction execution state causes an
  exception
  
  For BX and BLX, bit[0] of Rm must be 1 for correct execution, but a branch occurs to the target
  address created by changing bit[0] to 0.
  
   31 30 29 28 27 26 25 24 23 22 21 20 19 18 17 16 15 14 13 12 11 10 9 8 7 6 5 4 3 2 1 0
  |0  1   0  0  0  1| 1  1| 0|     Rm    | 0  0  0|                unused               |

where:
        <c><q>      See Standard assembler syntax fields on page A6-7.
        
        <Rm>      Specifies the register that contains the branch target address and instruction set selection bit
*/
void BX(uint32_t instruction)
{
  uint32_t Rm = getBits(instruction,22,19);            
  
  if( !inITBlock() || isLastInITBlock() )                 //if not inside IT block or last instruction inside IT  
  {                                                       //block only execute
    if( getBits(coreReg[Rm],0,0) == 1)                    //if the bit 0 is 1 only execute
    {
      if(inITBlock())
      {
        if( checkCondition(cond) )
        {
          coreReg[Rm] = setBits(coreReg[Rm], 0, 0, 0);                //change the bit 0 to be 0
          coreReg[PC] = coreReg[Rm];
        }
        shiftITState();
      }
      else
      {
        coreReg[Rm] = setBits(coreReg[Rm], 0, 0, 0);                  //change the bit 0 to be 0
        coreReg[PC] = coreReg[Rm];
      }
    }
    else
    {
      placePCtoVectorTable(UsageFault);
      Throw(UsageFault);
    }
  }
  else
  {
    placePCtoVectorTable(UsageFault);
    Throw(UsageFault);
  }
}




