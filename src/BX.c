#include "BX.h"
#include "ARMRegisters.h"
#include "getAndSetBits.h"
#include "StatusRegisters.h"
#include "ADDSPRegister.h"
#include "ModifiedImmediateConstant.h"
#include "ITandHints.h"
#include "ConditionalExecution.h"
#include <stdio.h>
#include <CException.h>
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
  uint32_t IT1to0 = getBits(coreReg[xPSR], 26,25);        //get the IT[1:0] from coreReg[xPSR]
  uint32_t IT7to2 = getBits(coreReg[xPSR], 15,10);        //get the IT[7:2] from coreReg[xPSR]
  uint32_t IT = (IT7to2 << 2) | IT1to0;                   //combine the IT[1:0] and IT[7:2]
  
  if( !inITBlock() | getBits(IT, 3,0) == 0b1000 )
  {
    if( getBits(coreReg[Rm],0,0) == 1)
    {
      coreReg[Rm] = setBits(coreReg[Rm], 0, 0, 0);                  //change the bit 0 to be 0
      coreReg[PC] = coreReg[Rm];
      shiftITState();
    }
    else
      Throw(UsageFault);
  }
  else
    Throw(UsageFault);
}




