#include "ADR.h"
#include "ITandHints.h"
#include "StatusRegisters.h"
#include "ARMRegisters.h"
#include "getAndSetBits.h"
#include "getMask.h"
#include "ModifiedImmediateConstant.h"
#include "ConditionalExecution.h"
#include "MemoryBlock.h"



/*Address to Register Encoding T1
    ADR<c> <Rd>,<label>
      
  31 30 29 28 27 26 25 24 23 22 21 20 19 18 17 16 15 14 13 12 11 10 9 8 7 6 5 4 3 2 1 0
  |1  0  1  0| 0|    Rd  |           imm8        |                unused               |
  
where:
            <c><q>                See Standard assembler syntax fields on page A6-7.
            
            <Rd>                  Specifies the destination register.
            
            <label>               Specifies the label of an instruction or literal data item whose address is to be loaded into
            
            <Rd>.                 The assembler calculates the required value of the offset from the Align(PC,4) value
                                  of the ADR instruction to this label.
                                  If the offset is positive, encodings T1 and T3 are permitted with imm32 equal to the offset.
                                  Allowed values of the offset are multiples of four in the range 0 to 1020 for encoding T1 and
                                  any value in the range 0 to 4095 for encoding T3.
                                  If the offset is negative, encoding T2 is permitted with imm32 equal to minus the offset.
                                  Allowed values of the offset are -4095 to -1.
                                  
  In the alternative syntax forms:
            <const>               Specifies the offset value for the ADD form and minus the offset value for the SUB form.
                                  Allowed values are multiples of four in the range 0 to 1020 for encoding T1 and any value
                                  in the range 0 to 4095 for encodings T2 and T3.
*/
void ADRT1(uint32_t instruction)
{
  uint32_t Rd = getBits(instruction,26,24);
  uint32_t imm8 = getBits(instruction,23,16);
  
  //bug here, forgot to shift left twice
  if(inITBlock())
  {
    if( checkCondition(cond) )
      executeADR(Rd, imm8);
    shiftITState();
  }
  else
    executeADR(Rd, imm8);
}



uint32_t alignPC(uint32_t value, uint32_t alignIndex)
{
  return (alignIndex * (value/alignIndex) );  
  
}


void executeADR(uint32_t Rd, uint32_t immediate)
{
  uint32_t PCAfterAlign = alignPC(coreReg[PC]+4, 4);
  coreReg[Rd] =  PCAfterAlign + immediate;
  
}