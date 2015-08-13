#include "ASRImmediate.h"
#include "ShiftOperation.h"
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
  
  if(inITBlock())
  {
    if( checkCondition(cond) )
      executeASRImmediate(imm5, Rm, Rd, 0);
    shiftITState();
  }
  else
    executeASRImmediate(imm5, Rm, Rd, 1);
  
  coreReg[PC] += 2;
}


/*  This function will perform the arithmetic shift right for immediate
  
    Input:  imm5        the immediate, also indicate how many times to shift
            Rm          source register
            Rd          destination register
            StatusBit   indicator for affecting the flag or not
            MSBofRm     MSB of source register

*/
void executeASRImmediate(uint32_t imm5, uint32_t Rm, uint32_t Rd, uint32_t S)
{
  coreReg[Rd] = executeASR(imm5, coreReg[Rm], S);
  
  if(S == 1)
  {
    updateNegativeFlag(coreReg[Rd]);
    updateZeroFlag(coreReg[Rd]);
    
    // Overflow flag will not be affected and the carry flag handling is inside the executeASR function
  }
}



