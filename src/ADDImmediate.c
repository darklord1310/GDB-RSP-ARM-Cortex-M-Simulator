#include "ADDImmediate.h"
#include "ARMRegisters.h"
#include "getBits.h"
#include "StatusRegisters.h"
#include "ModifiedImmediateConstant.h"
#include "ConditionalExecution.h"
#include <stdio.h>
#include <assert.h>


/*Add Immediate Encoding T1 (Add Immediate 3bits)
    ADDS <Rd>,<Rn>,#<imm3>      Outside IT block.
    ADD<c> <Rd>,<Rn>,#<imm3>    Inside IT block.
      
   31 30 29 28 27 26 25 24 23 22 21 20 19 18 17 16 15 14 13 12 11 10 9 8 7 6 5 4 3 2 1 0
  |0  0   0| 1  1| 1  0|  imm3  |   Rn   |   Rd   |                unused               |

where :  
          S             If present, specifies that the instruction updates the flags. Otherwise, the instruction does not
                        update the flags.
                          
          <c><q>        See Standard assembler syntax fields on page A6-7.
          
          <Rd>          Specifies the destination register. If <Rd> is omitted, this register is the same as <Rn>.
          
          <Rn>          Specifies the register that contains the first operand. If the SP is specified for <Rn>, see ADD
                        (SP plus immediate) on page A6-26. If the PC is specified for <Rn>, see ADR on page A6-30.
                        
          <const>       Specifies the immediate value to be added to the value obtained from <Rn>. The range of
                        allowed values is 0-7 for encoding T1, 0-255 for encoding T2 and 0-4095 for encoding T4.
                        See Modified immediate constants in Thumb instructions on page A5-15 for the range of
                        allowed values for encoding T3.
                        
          When multiple encodings of the same length are available for an instruction, encoding T3
          is preferred to encoding T4 (if encoding T4 is required, use the ADDW syntax). Encoding T1
          is preferred to encoding T2 if <Rd> is specified and encoding T2 is preferred to encoding T1
          if <Rd> is omitted
*/
void ADDImmediateT1(uint32_t instruction)
{
  uint32_t imm3 = getBits(instruction,24,22);
  uint32_t Rn = getBits(instruction,21,19);
  uint32_t Rd = getBits(instruction,18,16);
  assert(imm3 <= 0b111);
  assert(Rn <= 0b111);
  assert(Rd <= 0b111);

 if(inITBlock())
 {
    uint32_t ITCond = getITCond();
    if( checkCondition(ITCond) )
      executeADDImmediate(Rn, Rd, imm3, 0);
 }
 else
    executeADDImmediate(Rn, Rd, imm3, 1);
  
}



/*Add Immediate Encoding T2 (Add Immediate 8bits)
    ADDS <Rdn>,#<imm8>          Outside IT block.
    ADD<c> <Rdn>,#<imm8>        Inside IT block.
      
   31 30 29 28 27 26 25 24 23 22 21 20 19 18 17 16 15 14 13 12 11 10 9 8 7 6 5 4 3 2 1 0
  |0  0   1| 1  0|   Rdn  |          imm8         |                unused               |

where :  
          S             If present, specifies that the instruction updates the flags. Otherwise, the instruction does not
                        update the flags.
                          
          <c><q>        See Standard assembler syntax fields on page A6-7.
          
          <Rd>          Specifies the destination register. If <Rd> is omitted, this register is the same as <Rn>.
          
          <Rn>          Specifies the register that contains the first operand. If the SP is specified for <Rn>, see ADD
                        (SP plus immediate) on page A6-26. If the PC is specified for <Rn>, see ADR on page A6-30.
                        
          <const>       Specifies the immediate value to be added to the value obtained from <Rn>. The range of
                        allowed values is 0-7 for encoding T1, 0-255 for encoding T2 and 0-4095 for encoding T4.
                        See Modified immediate constants in Thumb instructions on page A5-15 for the range of
                        allowed values for encoding T3.
                        
          When multiple encodings of the same length are available for an instruction, encoding T3
          is preferred to encoding T4 (if encoding T4 is required, use the ADDW syntax). Encoding T1
          is preferred to encoding T2 if <Rd> is specified and encoding T2 is preferred to encoding T1
          if <Rd> is omitted
*/
void ADDImmediateT2(uint32_t instruction)
{
  uint32_t imm8 = getBits(instruction,23,16);
  uint32_t Rdn = getBits(instruction,26,24);
  assert(imm8 <= 011111111);
  assert(Rdn <= 0b111);

  if(inITBlock())
  {
    uint32_t ITCond = getITCond();
    if( checkCondition(ITCond) )
      executeADDImmediate(Rdn, Rdn, imm8, 0);
  }
  else
    executeADDImmediate(Rdn, Rdn, imm8, 1);
  
}


/* This instruction adds an immediate value to a register value, and writes the result to the destination register. 

   Input: Rn          register value which will be added with immediate  
          Rd          destination register
          immediate   immediate value which will be added with Rn
          S           if set will affect the status register
*/
void executeADDImmediate(uint32_t Rn, uint32_t Rd, uint32_t immediate, uint32_t S)
{
  uint32_t temp = coreReg->reg[Rn].data + immediate;            //get the result of Rn + immediate
  coreReg->reg[Rd].data = temp;
  
  if(S == 1)
  {
    updateZeroFlag(coreReg->reg[Rd].data);
    updateNegativeFlag(coreReg->reg[Rd].data);
    updateOverflowFlagAddition(coreReg->reg[Rn].data, immediate, temp);
    updateCarryFlagAddition(coreReg->reg[Rn].data, immediate);
  }
}