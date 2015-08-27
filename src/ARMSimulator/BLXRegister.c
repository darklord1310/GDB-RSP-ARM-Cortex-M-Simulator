#include "BLXRegister.h"
#include "ARMRegisters.h"
#include "getAndSetBits.h"
#include "StatusRegisters.h"
#include "ADDSPRegister.h"
#include "ModifiedImmediateConstant.h"
#include "ITandHints.h"
#include "ConditionalExecution.h"
#include <stdio.h>
#include "ErrorSignal.h"

/*Branch with Link and Exchange
 
    BLX<c> <Rm>            Outside or last in IT block
    
  Branch with Link and Exchange calls a subroutine at an address and instruction set specified by a register.
  ARMv7-M only supports the Thumb instruction set. An attempt to change the instruction execution state
  causes an exception.
      
   31 30 29 28 27 26 25 24 23 22 21 20 19 18 17 16 15 14 13 12 11 10 9 8 7 6 5 4 3 2 1 0
  |0  1   0  0  0  1| 1  1| 1|     Rm    | 0  0  0|                unused               |

where:
        <c><q>      See Standard assembler syntax fields on page A6-7.
        
        <Rm>      Specifies the register that contains the branch target address and instruction set selection bit
*/
void BLXRegister(uint32_t instruction)
{
  uint32_t Rm = getBits(instruction,22,19);

  if( !inITBlock() || isLastInITBlock() || Rm != 15)   // if not inside IT block, or last instruction inside IT block or Rm is PC
  {
    if( getBits(coreReg[Rm],0,0) == 1)
    {
      if(inITBlock())
      {
        if( checkCondition(cond) )
        {
          coreReg[Rm] = setBits(coreReg[Rm], 0, 0, 0);                  //change the bit 0 to be 0
          uint32_t next_instr_addr = coreReg[PC] + 2;
          coreReg[LR] = ( getBits(next_instr_addr, 31,1) << 1) | 1;     //change the bit 0 to be 1 because when return to function call by calling bx lr
                                                                        //the bx instruction must get the value which the bit 0 is 1
          coreReg[PC] = coreReg[Rm];
        }
        shiftITState();
      }
      else
      {
        coreReg[Rm] = setBits(coreReg[Rm], 0, 0, 0);                  //change the bit 0 to be 0
        uint32_t next_instr_addr = coreReg[PC] + 2;
        coreReg[LR] = ( getBits(next_instr_addr, 31,1) << 1) | 1;     //change the bit 0 to be 1 because when return to function call by calling bx lr
                                                                      //the bx instruction must get the value which the bit 0 is 1
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




