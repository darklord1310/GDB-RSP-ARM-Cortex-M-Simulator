#include "RSBImmediate.h"
#include "ITandHints.h"
#include "ConditionalExecution.h"
#include <assert.h>


/*Reverse Subtract Immediate Encoding T1
      RSBS    <Rd>,<Rn>,#0    Outside IT block.
      RSB<c>  <Rd>,<Rn>,#0    Inside IT block.
      
   31 30 29 28 27 26 25 24 23 22 21 20 19 18 17 16 15 14 13 12 11 10 9 8 7 6 5 4 3 2 1 0
  |0   1  0  0  0  0| 1  0  0  1|   Rn   |   Rd   |             unused                  |

where :  
          S           If present, specifies that the instruction updates the flags. Otherwise, the instruction does not
                      update the flags.
                      
          <c><q>      See Standard assembler syntax fields on page A6-7.
          
          <Rd>        Specifies the destination register. If <Rd> is omitted, this register is the same as <Rn>.
          
          <Rn>        Specifies the register that contains the first operand.
          
          <const>     Specifies the immediate value to be added to the value obtained from <Rn>. The only allowed
                      value for encoding T1 is 0. See Modified immediate constants
*/
void RSBImmediateT1(uint32_t instruction)
{
  uint32_t Rn = getBits(instruction,21,19);
  uint32_t Rd = getBits(instruction,18,16);
  assert(Rn <= 0b111);
  assert(Rd <= 0b111);

  if(inITBlock())
  {
    if( checkCondition(cond) )
      executeRSBImmediate(Rn, Rd, 0);
    shiftITState();
  }
 else
    executeRSBImmediate(Rn, Rd, 1);
  
  coreReg[PC] += 2;
}



/* Reverse Subtract (immediate) subtracts a register value from a 0, and writes the result to
   the destination register. It can optionally update the condition flags based on the result.

   Input: Rn          register value which will be added with immediate  
          Rd          destination register
          immediate   immediate value which will be added with Rn
          S           if set will affect the status register
*/
void executeRSBImmediate(uint32_t Rn, uint32_t Rd, uint32_t S)
{
  uint32_t backupRn = coreReg[Rn];            //prevent the Rn value to be overwritten in case if Rn = Rd
  uint32_t temp = 0 - coreReg[Rn];            //get the result of 0 - Rn
  coreReg[Rd] = temp;
  
  if(S == 1)
  {
    updateZeroFlag(coreReg[Rd]);
    updateNegativeFlag(coreReg[Rd]);
    updateOverflowFlagSubtraction(0, backupRn, coreReg[Rd]);
    updateCarryFlagSubtraction(0, backupRn);
  }
}