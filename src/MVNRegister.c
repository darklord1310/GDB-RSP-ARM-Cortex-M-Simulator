#include "MVNRegister.h"
#include "ITandHints.h"
#include "StatusRegisters.h"
#include "ARMRegisters.h"
#include "getAndSetBits.h"
#include "getMask.h"
#include "ModifiedImmediateConstant.h"
#include "Thumb16bitsTable.h"
#include "ConditionalExecution.h"


/*  
  Move Not Register to Register Encoding T1 
  
      MVNS    <Rd>,<Rm>     Outside IT block.
      MVN<c>  <Rd>,<Rm>     Inside IT block.
        
   31 30 29 28 27 26 25 24 23 22 21 20 19 18 17 16 15 14 13 12 11 10 9 8 7 6 5 4 3 2 1 0
  |0   1  0  0  0  0| 1  1  1  1|   Rm   |   Rdn  |             unused                  |
    
  where:
            S           If present, specifies that the instruction updates the flags. Otherwise, the instruction does not
                        update the flags.
                        
            <c><q>      See Standard assembler syntax fields on page A6-7.
            
            <Rd>        Specifies the destination register.
            
            <Rm>        Specifies the register that is optionally shifted and used as the source register.
            
            <shift>     Specifies the shift to apply to the value read from <Rm>. If <shift> is omitted, no shift is
                        applied and both encodings are permitted. If <shift> is specified, only encoding T2 is
                        permitted. The possible shifts and how they are encoded are described in Shifts applied to a
                        register on page A6-12.
  
*/
void MVNRegisterT1(uint32_t instruction)
{
  uint32_t Rm = getBits(instruction, 21, 19);
  uint32_t Rd = getBits(instruction, 18, 16);
	
  if(inITBlock())
  {  
    if( checkCondition(cond) )
      executeMVNRegister(Rm, Rd, 0,-1);  //status flag is not affected
    
    shiftITState();
  }
  else
    executeMVNRegister(Rm, Rd, 1,-1);   //status flag is affected
  
  coreReg[PC] += 2;
}





/*  Bitwise NOT (register) writes the bitwise inverse of a register value to the destination register. It can
    optionally update the condition flags based on the result.
  
    Input:  Rm              source register
            Rd              destination register
            S               indicator for affecting the flag or not
            shiftType       determine what type of shifting is needed, -1 if no shifting

*/
void executeMVNRegister(uint32_t Rm, uint32_t Rd, uint32_t S, uint32_t shiftType)
{
  coreReg[Rd] = ~coreReg[Rm];
  
  if(S == 1)
  {
    updateZeroFlag(coreReg[Rd]);
    updateNegativeFlag(coreReg[Rd]);
  }
}


