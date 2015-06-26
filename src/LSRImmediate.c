#include "LSRImmediate.h"
#include <stdint.h>


/*Logical Shift Right Immediate Encoding T1
      LSRS <Rd>,<Rm>,#<imm5>        Outside IT block.
      LSR<c> <Rd>,<Rm>,#<imm5>      Inside IT block
      
  Note : Can only shift 1 < n <= 32 times
   31 30 29 28 27 26 25 24 23 22 21 20 19 18 17 16 15 14 13 12 11 10 9 8 7 6 5 4 3 2 1 0
  |0  0  0 |0  1|     imm5      |   Rm  |    Rd   |             unused                 |
   
where:
        S          If present, specifies that the instruction updates the flags. Otherwise, the instruction does not
                   update the flags.
                   
        <c><q>     See Standard assembler syntax fields on page A6-7.
        
        <Rd>       Specifies the destination register.
        
        <Rm>       Specifies the register that contains the first operand.
        
        <imm5>     Specifies the shift amount, in the range 1 to 32. See Shifts applied to a register on
                   page A6-12.
*/
void LSRImmediateT1(uint32_t instruction)
{
  uint32_t imm5 = getBits(instruction, 26 , 22);
  uint32_t Rm = getBits(instruction, 21, 19);
  uint32_t Rd = getBits(instruction, 18, 16);
	
  if(inITBlock())
    executeLSRImmediate(imm5, Rm, Rd, 0);
  else
    executeLSRImmediate(imm5, Rm, Rd, 1);
}


/*  This function will perform the logical shift right for immediate
  
    Input:  immediate       the immediate, also indicate how many times to shift
            Rm              source register
            Rd              destination register
            S               indicator for affecting the flag or not

*/
void executeLSRImmediate(uint32_t immediate, uint32_t Rm, uint32_t Rd, uint32_t S)
{
  int lastBitShifted;
  
  if( immediate == 0)                                                       //if immediate is 0, means maximum shift, shift 32 times
  {
    lastBitShifted = getBits(coreReg[Rm],31,31);                            //this is to get the lastBitShifted out, the value will determine the carry flag
    coreReg[Rd] = 0x0;                                                      //the destination will have value of 0x0 for sure
  }
  else
  {
    lastBitShifted = getBits(coreReg[Rm], immediate-1, immediate-1) ;       //this is to get the lastBitShifted out, the value will determine the carry flag
    coreReg[Rd] = coreReg[Rm] >> immediate;
  }
  
  if(S == 1)                                                                //update status register
  {
    updateNegativeFlag(coreReg[Rd]);
    updateZeroFlag(coreReg[Rd]);
    if(lastBitShifted == 1)
      setCarryFlag();
    else
      resetCarryFlag();
  }
}

