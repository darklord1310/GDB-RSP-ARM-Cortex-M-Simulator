#include "BL.h"
#include "ARMRegisters.h"
#include "getAndSetBits.h"
#include "StatusRegisters.h"
#include "ITandHints.h"
#include "ConditionalExecution.h"
#include "ErrorSignal.h"
#include <stdio.h>
#include "CException.h"
#include "SVC.h"


/* Branch with Link (immediate) calls a subroutine at a PC-relative address.

   BL<c> <label>         Outside or last in IT block.

   31 30 29 28 27 26 25 24 23 22 21 20 19 18 17 16 15 14 13 12 11 10 9 8 7 6 5 4 3 2 1 0
  |1  1  1  1  0 |S|             imm10            |1  1|J1||1||J2|        imm11         |

where:
          <c><q>        See Standard assembler syntax fields on page A6-7.

          <label>       Specifies the label of the instruction that is to be branched to.
                        The assembler calculates the required value of the offset from the PC value of the BL
                        instruction to this label, then selects an encoding that will set imm32 to that offset.
                        Allowed offsets are even numbers in the range -16777216 to 16777214.
*/
void BLT1(uint32_t instruction)
{
  uint32_t imm10 = getBits(instruction, 25, 16);
  uint32_t imm11 = getBits(instruction, 10, 0);
  uint32_t S = getBits(instruction, 26, 26);
  uint32_t J1 = getBits(instruction, 13, 13);
  uint32_t J2 = getBits(instruction, 11, 11);

  uint32_t I1 = ~(J1 ^ S) & 0x1;
  uint32_t I2 = ~(J2 ^ S) & 0x1;

  uint32_t imm32 = imm11 << 1;
  imm32 = imm10 << 12 | imm32;
  imm32 = I2 << 22 | imm32;
  imm32 = I1 << 23 | imm32;
  imm32 = S << 24 | imm32;
  imm32 = signExtend(imm32, 25);

  if( !( inITBlock() ) || isLastInITBlock())
  {
    if( inITBlock() )
    {
      if( checkCondition(cond) )
      {
        uint32_t nextInstrAddr = coreReg[PC] + 4;
        coreReg[LR] = nextInstrAddr | 0x1;
        coreReg[PC] = coreReg[PC] + imm32 + 4;
      }

      shiftITState();
    }
    else
    {
      uint32_t nextInstrAddr = coreReg[PC] + 4;
      coreReg[LR] = nextInstrAddr | 0x1;
      coreReg[PC] = coreReg[PC] + imm32 + 4;
    }
  }
  else
  {
    placePCtoVectorTable(UsageFault);
    Throw(UsageFault);
  }
}
