#include "LSLRegister.h"
#include "ITandHints.h"
#include "StatusRegisters.h"
#include "ARMRegisters.h"
#include "getAndSetBits.h"
#include "getMask.h"
#include "ModifiedImmediateConstant.h"
#include "Thumb16bitsTable.h"
#include "ConditionalExecution.h"


/*Logical Shift Left Register To Register Encoding T1
      LSLS <Rdn>,<Rm>         Outside IT block.
      LSL<c> <Rdn>,<Rm>       Inside IT block
  
  Logical Shift Left (register) shifts a register value left by a variable number of bits, shifting in zeros, and
  writes the result to the destination register. The variable number of bits is read from the bottom byte of a
  register. It can optionally update the condition flags based on the result.
  
   31 30 29 28 27 26 25 24 23 22 21 20 19 18 17 16 15 14 13 12 11 10 9 8 7 6 5 4 3 2 1 0
  |0   1  0  0  0  0| 0  0  1  0|   Rm   |   Rdn  |             unused                  |
   
where:
            S             If present, specifies that the instruction updates the flags. Otherwise, the instruction does not
                          update the flags.
                          
            <c><q>        See Standard assembler syntax fields on page A6-7.
            
            <Rd>          Specifies the destination register.
            
            <Rn>          Specifies the register that contains the first operand.
            
            <Rm>          Specifies the register whose bottom byte contains the amount to shift by.
*/

void LSLRegisterToRegisterT1(uint32_t instruction)
{
  uint32_t Rm = getBits(instruction, 21, 19);
  uint32_t Rdn = getBits(instruction, 18, 16);

  if(inITBlock())
  {
    if( checkCondition(cond) )
      executeLSLRegister(Rm, Rdn, 0);
    
    shiftITState();
  }
  else
    executeLSLRegister(Rm, Rdn, 1);
  
}




void executeLSLRegister(uint32_t Rm, uint32_t Rdn, uint32_t S)
{
  int lastBitShifted;
  unsigned int timesToShift = getBits( coreReg[Rm] ,7, 0);    //get the lowest byte from the Rm register

  if(timesToShift <= 32)
  {
    lastBitShifted = getBits(coreReg[Rdn], 32-timesToShift, 32-timesToShift);
    if( timesToShift == 32)
      coreReg[Rdn] = 0;
    else
      coreReg[Rdn] =  coreReg[Rdn] << timesToShift ;
  }
  else
  {
    lastBitShifted = 0;
    coreReg[Rdn] = 0;
  }

  
  if( S == 1)
  {
    updateNegativeFlag(coreReg[Rdn]);
    updateZeroFlag(coreReg[Rdn]);
    if(timesToShift != 0)
    {
      if(lastBitShifted == 1)
        setCarryFlag();
      else
        resetCarryFlag();
    }
  }

}