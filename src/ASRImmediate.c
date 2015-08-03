#include "ASRImmediate.h"
#include "ARMRegisters.h"
#include "getAndSetBits.h"
#include "StatusRegisters.h"
#include "ITandHints.h"
#include "ConditionalExecution.h"
#include <stdio.h>

/*Arithmetic Shift Right Immediate Encoding T1
      ASRS <Rd>,<Rm>,#<imm5>        Outside IT block.
      ASR<c> <Rd>,<Rm>,#<imm5>      Inside IT block.
      
   31 30 29 28 27 26 25 24 23 22 21 20 19 18 17 16 15 14 13 12 11 10 9 8 7 6 5 4 3 2 1 0
  |0  0   0| 1  0|     imm5     |   Rm   |   Rd   |                unused               |
   
where:
        S               If present, specifies that the instruction updates the flags. 
                        Affect carry, overflow, negative.
                        Carry flag is updated to the last bit shifted out, bit[n-1], of the register Rm
                        
        <c><q>          See Standard assembler syntax fields on page A6-7.
        
        <Rd>            Specifies the destination register.
        
        <Rm>            Specifies the register that contains the first operand.
        
        <imm5>          Specifies the shift amount, in the range 1 to 32. See Shifts applied to a register on
                        page A6-12.
*/
void ASRImmediateT1(uint32_t instruction)
{
  uint32_t imm5 = getBits(instruction, 26 , 22);
  uint32_t Rm = getBits(instruction, 21, 19);
  uint32_t Rd = getBits(instruction, 18, 16);
  uint32_t MSBofRm = getBits( coreReg[Rm], 31,31 );
  
  if(inITBlock())
  {
    if( checkCondition(cond) )
      executeASRImmediate(imm5, Rm, Rd, 0, MSBofRm);
    shiftITState();
  }
  else
    executeASRImmediate(imm5, Rm, Rd, 1, MSBofRm);
  
  coreReg[PC] += 2;
}


/*  This function will perform the arithmetic shift right for immediate
  
    Input:  imm5        the immediate, also indicate how many times to shift
            Rm          source register
            Rd          destination register
            StatusBit   indicator for affecting the flag or not
            MSBofRm     MSB of source register

*/
void executeASRImmediate(uint32_t imm5, uint32_t Rm, uint32_t Rd, uint32_t StatusBit, uint32_t MSBofRm)
{
  int i, timesToShift, lastBitShifted;
  uint32_t mask = MSBofRm << 31;                //create mask to achieve arithmetic shift
                                                
  uint32_t temp = coreReg[Rm];                  //create a dummy to prevent changing the register value
  
  if( imm5 != 0)                                //if imm5 is not zero, means not maximum 32 shift
    timesToShift = imm5;
  else
    timesToShift = 32;
  
  for(i = 0; i < timesToShift; i++)
  {
    if( i == timesToShift - 1)                  //this is to get the last bit of Rm before shifted out
      lastBitShifted = getBits(temp, 0,0);
    temp = ( temp >> 1 ) | mask;
  }
  
  coreReg[Rd] = temp;
  
  if(StatusBit == 1)
  {
    updateZeroFlag(temp);
    updateNegativeFlag(temp); 
    if(lastBitShifted == 1)                     //if lastBitShifted is 1, the carry is set, else carry not set
      setCarryFlag();
    else
      resetCarryFlag();
  }
}



