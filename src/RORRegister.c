#include "RORRegister.h"
#include "ITandHints.h"
#include "StatusRegisters.h"
#include "ARMRegisters.h"
#include "getAndSetBits.h"
#include "getMask.h"
#include "ModifiedImmediateConstant.h"
#include "Thumb16bitsTable.h"
#include "ConditionalExecution.h"


/*Rotate Right Register To Register Encoding T1
        RORS <Rdn>,<Rm>       Outside IT block.
        ROR<c> <Rdn>,<Rm>     Inside IT block.
        
   31 30 29 28 27 26 25 24 23 22 21 20 19 18 17 16 15 14 13 12 11 10 9 8 7 6 5 4 3 2 1 0
  |0   1  0  0  0  0| 0  1  1  1|   Rm   |   Rdn  |              unused                 |
   
where:
          S             If present, specifies that the instruction updates the flags. Otherwise, the instruction does not
                        update the flags.
                        
          <c><q>        See Standard assembler syntax fields on page A6-7.
          
          <Rd>          Specifies the destination register.
          
          <Rn>          Specifies the register that contains the first operand.
          
          <Rm>          Specifies the register whose bottom byte contains the amount to rotate by.
*/
void RORRegisterT1(uint32_t instruction)
{
  uint32_t Rm = getBits(instruction, 21, 19);
  uint32_t Rdn = getBits(instruction, 18, 16);
	
  if(inITBlock())
  {
    if( checkCondition(cond) )
      executeRORRegister(Rdn, Rdn, Rm, 0);
    
    shiftITState();
  }
  else
    executeRORRegister(Rdn, Rdn, Rm, 1);
  
  coreReg[PC] += 2;
}


void executeRORRegister(uint32_t Rd, uint32_t Rn, uint32_t Rm, uint32_t S)
{
  int i, timesToRotate, lastBitRotated;
  uint32_t temp = coreReg[Rn];                   //this temp is used to perform the rotate operation and to avoid destroy the value in Rn
  timesToRotate = getBits(coreReg[Rm], 7 ,0);
  
  for(i=0; i<timesToRotate; i++)
  {
    if(i == timesToRotate -1 )                    //to get the last bit rotated       
      lastBitRotated = getBits(temp,0,0);
      
    if( getBits(temp,0,0) == 1)
    {
      temp = temp >> 1;
      temp = setBits(temp, 1, 31, 31);
    }
    else
    {
      temp = temp >> 1;
      temp = setBits(temp, 0, 31, 31);
    }
  }
  
  coreReg[Rd] = temp;

  if( S == 1)
  {
    updateNegativeFlag(coreReg[Rd]);
    updateZeroFlag(coreReg[Rd]);
    if(timesToRotate != 0)
    {
      if(lastBitRotated == 1)
        setCarryFlag();
      else
        resetCarryFlag();
    }
  }

}