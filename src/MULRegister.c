#include "MULRegister.h"
#include "ITandHints.h"
#include "StatusRegisters.h"
#include "ARMRegisters.h"
#include "getAndSetBits.h"
#include "getMask.h"
#include "ModifiedImmediateConstant.h"
#include "Thumb16bitsTable.h"
#include "ConditionalExecution.h"


/*  
  Multiply Register to Register Encoding T1 
  
        MULS    <Rdm>,<Rn>,<Rdm>    Outside IT block.
        MUL<c>  <Rdm>,<Rn>,<Rdm>    Inside IT block
        
   31 30 29 28 27 26 25 24 23 22 21 20 19 18 17 16 15 14 13 12 11 10 9 8 7 6 5 4 3 2 1 0
  |0   1  0  0  0  0| 1  1  0  1|   Rn   |   Rdm  |             unused                  |
    
  where:
            S           If present, specifies that the instruction updates the flags. Otherwise, the instruction does not
                        update the flags.
                        
            <c><q>      See Standard assembler syntax fields on page A6-7.
            
            <Rd>        Specifies the destination register. If <Rd> is omitted, this register is the same as <Rn>.
            
            <Rn>        Specifies the register that contains the first operand.
            
            <Rm>        Specifies the register that contains the second operand.
  
*/
void MULRegisterT1(uint32_t instruction)
{
  uint32_t Rn = getBits(instruction, 21, 19);
  uint32_t Rdm = getBits(instruction, 18, 16);
	
  if( inITBlock() )
  {  
    if( checkCondition(cond) )
      executeMULRegister(Rdm, Rdm, Rn,0);  //status flag is not affected
    
    shiftITState();
  }
  else
    executeMULRegister(Rdm, Rdm, Rn, 1);   //status flag is affected
  
}





/*  Bitwise NOT (register) writes the bitwise inverse of a register value to the destination register. It can
    optionally update the condition flags based on the result.
  
    Input:  Rm              source register
            Rd              destination register
            S               indicator for affecting the flag or not

*/
void executeMULRegister(uint32_t Rm, uint32_t Rd, uint32_t Rn, uint32_t S)
{
  uint64_t answer = coreReg[Rm] * coreReg[Rn];
  coreReg[Rd] = coreReg[Rm] * coreReg[Rn];
  
  if(S == 1)
  {
    updateZeroFlag(coreReg[Rd]);
    updateNegativeFlag(coreReg[Rd]);
  }
}


