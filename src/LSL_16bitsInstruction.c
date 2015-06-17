#include "LSL_16bitsInstruction.h"
#include <stdint.h>

/*Logical Shift Left Immediate Encoding T1
      LSLS <Rd>,<Rm>,#<imm5>      Outside IT block.
      LSL<c> <Rd>,<Rm>,#<imm5>    Inside IT block
      
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
	uint32_t imm5 = getBits(instruction, 26 , 22);
	uint32_t Rm = getBits(instruction, 21, 19);
  uint32_t Rd = getBits(instruction, 18, 16);
	
	coreReg->reg[Rd].data = coreReg->reg[Rm].data  << imm5;
  
}


/*Logical Shift Left Register To Register Encoding T1
      LSLS <Rdn>,<Rm>         Outside IT block.
      LSL<c> <Rdn>,<Rm>       Inside IT block
  
  Logical Shift Left (register) shifts a register value left by a variable number of bits, shifting in zeros, and
  writes the result to the destination register. The variable number of bits is read from the bottom byte of a
  register. It can optionally update the condition flags based on the result.

   15  14  13  12  11  10  9   8   7   6   5   4   3   2   1   0
  |0   1   0   0   0   0 | 0   0   1   0 |     Rm    |    Rdn   |
   
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

  unsigned int timesToShift = getBits( coreReg->reg[Rm].data ,7, 0);    //get the lowest byte from the Rm register

	coreReg->reg[Rdn].data =  coreReg->reg[Rdn].data << timesToShift;
}