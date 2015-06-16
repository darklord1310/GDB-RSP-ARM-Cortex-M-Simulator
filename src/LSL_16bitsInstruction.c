#include "LSL_16bitsInstruction.h"
#include <stdint.h>

/*Logical Shift Left Immediate Encoding T1
      LSLS <Rd>,<Rm>,#<imm5> Outside IT block.
      LSL<c> <Rd>,<Rm>,#<imm5> Inside IT block
      
   15  14  13  12  11  10  9   8   7   6   5   4   3   2   1   0
  |0   0   0 | 0   0 |        imm5       |    Rm     |    Rd    |
   
where:
        S          If present, specifies that the instruction updates the flags. Otherwise, the instruction does not
                   update the flags.
                   
        <c><q>     See Standard assembler syntax fields on page A6-7.
        
        <Rd>       Specifies the destination register.
        
        <Rm>       Specifies the register that contains the first operand.
        
        <imm5>     Specifies the shift amount, in the range 0 to 31. See Shifts applied to a register on
                   page A6-12.
*/
void LSLImmediate16bitsT1(uint32_t instruction)
{
	uint32_t imm8 = getBits(instruction, 23, 16);
	uint32_t destinationRegister = getBits(instruction, 26, 24);
	
	coreReg->reg[destinationRegister].data = imm8;
}