#include "LSR_16bitsInstruction.h"
#include <stdint.h>


/*Logical Shift Right Immediate Encoding T1
      LSRS <Rd>,<Rm>,#<imm5>        Outside IT block.
      LSR<c> <Rd>,<Rm>,#<imm5>      Inside IT block
      
  Note : Can only shift 1 < n <= 32 times
  
   15  14  13  12  11  10  9   8   7   6   5   4   3   2   1   0
  |0   0   0 | 0   1 |        imm5       |    Rm     |    Rd    |
   
where:
        S          If present, specifies that the instruction updates the flags. Otherwise, the instruction does not
                   update the flags.
                   
        <c><q>     See Standard assembler syntax fields on page A6-7.
        
        <Rd>       Specifies the destination register.
        
        <Rm>       Specifies the register that contains the first operand.
        
        <imm5>     Specifies the shift amount, in the range 1 to 32. See Shifts applied to a register on
                   page A6-12.
*/
void LSRImmediate16bitsT1(uint32_t instruction)
{
	uint32_t imm5 = getBits(instruction, 26 , 22);
	uint32_t Rm = getBits(instruction, 21, 19);
  uint32_t Rd = getBits(instruction, 18, 16);
	
  if( imm5 == 0)
    coreReg->reg[Rd].data = 0x0;
  else
    coreReg->reg[Rd].data = coreReg->reg[Rm].data >> imm5;
  
}