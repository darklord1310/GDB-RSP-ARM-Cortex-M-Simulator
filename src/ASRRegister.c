#include "ASRRegister.h"


/*Arithmetic Shift Right Register To Register Encoding T1
        ASRS <Rdn>,<Rm>       Outside IT block.
        ASR<c> <Rdn>,<Rm>     Inside IT block
        
   31 30 29 28 27 26 25 24 23 22 21 20 19 18 17 16 15 14 13 12 11 10 9 8 7 6 5 4 3 2 1 0
  |0   1  0  0  0  0| 0  1  0  0|   Rm   |   Rdn  |             unused                  |
   
where:
          S             If present, specifies that the instruction updates the flags. Otherwise, the instruction does not
                        update the flags.
                        
          <c><q>        See Standard assembler syntax fields on page A6-7.
          
          <Rd>          Specifies the destination register.
          
          <Rn>          Specifies the register that contains the first operand.
          
          <Rm>          Specifies the register whose bottom byte contains the amount to shift by.
*/
void ASRRegisterToRegister16bitsT1(uint32_t instruction)
{
  int i;
  uint32_t Rm = getBits(instruction, 21, 19);
  uint32_t Rdn = getBits(instruction, 18, 16);
	
  unsigned int timesToShift = getBits( coreReg->reg[Rm].data ,7, 0);    //get the lowest byte from the Rm register
  unsigned int mask = ( getBits( coreReg->reg[Rm].data, 31,31 ) ) << 31;
  uint32_t temp = coreReg->reg[Rm].data;
  
  for(i = 0; i < timesToShift; i++)
  {
    temp = ( temp >> 1 ) | mask;
  }

  coreReg->reg[Rdn].data = temp;
}


void executeASRRegister()
{
  
  
  
}