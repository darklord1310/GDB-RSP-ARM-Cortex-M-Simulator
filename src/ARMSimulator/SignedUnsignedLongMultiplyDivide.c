#include "SignedUnsignedLongMultiplyDivide.h"
#include <assert.h>
#include "ARMRegisters.h"
#include "getAndSetBits.h"
#include "StatusRegisters.h"
#include "ADDSPRegister.h"
#include "ModifiedImmediateConstant.h"
#include "ITandHints.h"
#include "ConditionalExecution.h"
#include <stdio.h>


/*Multiply Accumulate Encoding T1
    MLA<c> <Rd>,<Rn>,<Rm>,<Ra>
      
   31 30 29 28 27 26 25 24 23 22 21 20 19 18 17 16 15 14 13 12 11 10 9 8 7 6 5 4 3 2 1 0
  |1   1  1  1  1| 0  1  1  0| 0  0  0|     Rn    |     Ra    |    Rd   |0 0 0 0|   Rm  |

where:
        <c><q>        See Standard assembler syntax fields on page A6-7.
        
        <Rd>          Specifies the destination register.
        
        <Rn>          Specifies the register that contains the first operand.
        
        <Rm>          Specifies the register that contains the second operand.
        
        <Ra>          Specifies the register containing the accumulate value.
*/
void SMULLT1(uint32_t instruction)
{
  uint32_t Rm = getBits(instruction,3,0);
  uint32_t Rd = getBits(instruction,11,8);
  uint32_t Rn = getBits(instruction,19,16);
  uint32_t Ra = getBits(instruction,15,12);
  
  if(inITBlock())
  {
    if( checkCondition(cond) )
      coreReg[Rd] = coreReg[Rn] * coreReg[Rm] + coreReg[Ra];

    shiftITState();
  }
  else
    coreReg[Rd] = coreReg[Rn] * coreReg[Rm] + coreReg[Ra];

  coreReg[PC] += 4;
}



void SDIVT1(uint32_t instruction)
{

}


void UMULLT1(uint32_t instruction)
{

}

void UDIVT1(uint32_t instruction)
{

}

void SMLALT1(uint32_t instruction)
{

}

void UMLALT1(uint32_t instruction)
{

}