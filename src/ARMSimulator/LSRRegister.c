#include "LSRRegister.h"
#include "ITandHints.h"
#include "StatusRegisters.h"
#include "ARMRegisters.h"
#include "getAndSetBits.h"
#include "getMask.h"
#include "ConditionalExecution.h"
#include "ShiftOperation.h"


/*Logical Shift Right Register To Register Encoding T1
        LSRS <Rdn>,<Rm>       Outside IT block.
        LSR<c> <Rdn>,<Rm>     Inside IT block.
        
   31 30 29 28 27 26 25 24 23 22 21 20 19 18 17 16 15 14 13 12 11 10 9 8 7 6 5 4 3 2 1 0
  |0   1  0  0  0  0| 0  0  1  1|   Rm   |   Rdn  |              unused                 |
   
where:
          S             If present, specifies that the instruction updates the flags. Otherwise, the instruction does not
                        update the flags.
                        
          <c><q>        See Standard assembler syntax fields on page A6-7.
          
          <Rd>          Specifies the destination register.
          
          <Rn>          Specifies the register that contains the first operand.
          
          <Rm>          Specifies the register whose bottom byte contains the amount to shift by.
*/
void LSRRegisterToRegisterT1(uint32_t instruction)
{
  uint32_t Rm = getBits(instruction, 21, 19);
  uint32_t Rd = getBits(instruction, 18, 16);
	
  if(inITBlock())
  {
    if( checkCondition(cond) )
      executeLSRRegister(Rm, Rd, Rd, 0);
    
    shiftITState();
    coreReg[PC] += 2;
  }
  else
  {
    executeLSRRegister(Rm, Rd, Rd, 1);
    coreReg[PC] += 2;
  }
  
}


/* Logical Shift Right Register Encoding T2

   LSR{S}<c>.W <Rd>,<Rn>,<Rm>

   31 30 29 28 27 26 25 24 23 22 21 20 19 18 17 16 15 14 13 12 11 10 9 8 7 6 5 4 3 2 1 0
  |1  1  1  1  1 |0  1  0 |0| 0  1 |S|     Rn     |1  1  1  1 |   Rd    |0|0 0 0|   Rm  |

where:
          S           If present, specifies that the instruction updates the flags. Otherwise, the instruction does not
                      update the flags.

          <c><q>      See Standard assembler syntax fields on page A6-7.

          <Rd>        Specifies the destination register.
          
          <Rn>        Specifies the register that contains the first operand.

          <Rm>        Specifies the register whose bottom byte contains the amount to shift by.
*/
void LSRRegisterT2(uint32_t instruction)
{
  uint32_t Rm =  getBits(instruction, 3, 0);
  uint32_t Rd = getBits(instruction, 11, 8);
  uint32_t Rn = getBits(instruction, 19, 16);
  uint32_t statusFlag = getBits(instruction, 20, 20);

  if(inITBlock())
  {
    if( checkCondition(cond) )
      executeLSRRegister(Rm, Rd, Rn, statusFlag);
    shiftITState();
  }
  else
    executeLSRRegister(Rm, Rd, Rn, statusFlag);

  coreReg[PC] += 4;
}


/* This instruction shifts a register value right by a variable number of bits, shifting in zeros, and
   writes the result to the destination register. The variable number of bits is read from the bottom byte of a
   register. It can optionally update the condition flags based on the result.

   Input: Rn          register value which will be shifted
          Rd          destination register
          Rm          register value which contain shifted value at bottom byte
          S           if set will affect the status register
*/
void executeLSRRegister(uint32_t Rm, uint32_t Rd, uint32_t Rn, uint32_t S)
{
  int lastBitShifted;
  unsigned int timesToShift = getBits(coreReg[Rm], 7, 0);    //get the lowest byte from the Rm register

  if(timesToShift <= 32)
  {
    if(timesToShift != 0)
      lastBitShifted = getBits(coreReg[Rn], timesToShift-1, timesToShift-1);
    
    if( timesToShift == 32)
      coreReg[Rd] = 0;
    else
      coreReg[Rd] =  coreReg[Rn] >> timesToShift ;
  }
  else
  {
    lastBitShifted = 0;
    coreReg[Rd] = 0;
  }

  
  if( S == 1)
  {
    updateNegativeFlag(coreReg[Rd]);
    updateZeroFlag(coreReg[Rd]);
    if(timesToShift != 0)
    {
      if(lastBitShifted == 1)
        setCarryFlag();
      else
        resetCarryFlag();
    }
  }
}