#include "ANDRegister.h"
#include <assert.h>
#include <stdio.h>
#include "ITandHints.h"
#include "StatusRegisters.h"
#include "ARMRegisters.h"
#include "getAndSetBits.h"
#include "getMask.h"
#include "ModifiedImmediateConstant.h"
#include "Thumb16bitsTable.h"
#include "ConditionalExecution.h"


/*And Register Encoding T1 
  ANDS      <Rdn>,<Rm>      Outside IT block.
  AND<c>    <Rdn>,<Rm>      Inside IT block.
      
   31 30 29 28 27 26 25 24 23 22 21 20 19 18 17 16 15 14 13 12 11 10 9 8 7 6 5 4 3 2 1 0
  |0  1   0  0  0  0|0   0  0  0|  Rm   |   Rdn   |                unused               |

  where:
          S         If present, specifies that the instruction updates the flags. Otherwise, the instruction does not
                    update the flags.
                    
          <c><q>    See Standard assembler syntax fields on page A6-7.
          
          <Rd>      Specifies the destination register. If <Rd> is omitted, this register is the same as <Rn>.
          
          <Rn>      Specifies the register that contains the first operand.
          
          <Rm>      Specifies the register that is optionally shifted and used as the second operand.
          
          <shift>   Specifies the shift to apply to the value read from <Rm>. If <shift> is omitted, no shift is
                    applied and both encodings are permitted. If <shift> is specified, only encoding T2 is
                    permitted. The possible shifts and how they are encoded are described in Shifts applied to a
                    register on page A6-12.
                    
          A special case is that if AND<c> <Rd>,<Rn>,<Rd> is written with <Rd> and <Rn> both in the range R0-R7, it will
          be assembled using encoding T2 as though AND<c> <Rd>,<Rn> had been written. To prevent this happening,
          use the .W qualifier.
          
*/
void ANDRegisterT1(uint32_t instruction)
{
  uint32_t Rm =  getBits(instruction,21,19);
  uint32_t Rdn = getBits(instruction,18,16);
  assert(Rm <= 0b111);
  assert(Rdn <= 0b111);

 if(inITBlock())
 {  
    if( checkCondition(cond) )
      executeANDRegister(Rm, Rdn, 0,0); //status flag is not affected and not shifting

    shiftITState();
 }
 else
    executeANDRegister(Rm, Rdn, 1,0);   //status flag is affected, no shifting
}



/* This instruction performs a bitwise AND of a register value and an optionally-shifted register value, and
   writes the result to the destination register.

   Input: Rm                register value which will be perform AND operation with value in Rdn
          Rdn               destination register
          S                 if set will affect the status register
          shiftOrNoShift    if 1 means there is shifting, if 0 means no shifting
*/
void executeANDRegister(uint32_t Rm, uint32_t Rdn, uint32_t S, int shiftOrNoShift)
{
  coreReg[Rdn] = coreReg[Rdn] & coreReg[Rm];
    
  if(S == 1)
  {
    updateZeroFlag(coreReg[Rdn]);
    updateNegativeFlag(coreReg[Rdn]);
    
  } 
}