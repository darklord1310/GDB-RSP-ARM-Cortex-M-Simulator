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
    ADD<c><q> <Rd>, PC, #<const>         Alternative for encodings

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
  uint32_t imm8 = getBits(instruction,23,16) << 2;


  //bug here, forgot to shift left twice
  if(inITBlock())
  {
    if( checkCondition(cond) )
      executeADR(Rd, imm8, TRUE);

    shiftITState();
    coreReg[PC] += 2;
  }
  else
  {
    executeADR(Rd, imm8, TRUE);
    coreReg[PC] += 2;
  }
}


/* Address to Register Encoding T2
   ADR<c>.W <Rd>,<label>            <label> before current instruction
   SUB <Rd>,PC,#0                   Special case for zero offset
   SUB<c><q> <Rd>, PC, #<const>     Alternative for encoding T2
   
Note:   It is recommended that the alternative syntax forms are avoided where possible. However,
        the only possible syntax for encoding T2 with all immediate bits zero is
        SUB<c><q> <Rd>,PC,#0.

   31 30 29 28 27 26 25 24 23 22 21 20 19 18 17 16 15 14 13 12 11 10 9 8 7 6 5 4 3 2 1 0
  |1  1  1  1  0 |i| 1  0  1  0  1 |0| 1  1  1  1 |0|  imm3   |    Rd   |     imm8       |

where:
            <c><q>          See Standard assembler syntax fields on page A6-7.

            <Rd>            Specifies the destination register.

            <label>         Specifies the label of an instruction or literal data item whose address is to be loaded into

            <Rd>.           The assembler calculates the required value of the offset from the Align(PC,4) value
                            of the ADR instruction to this label.
                            If the offset is negative, encoding T2 is permitted with imm32 equal to minus the offset.
                            Allowed values of the offset are -4095 to -1.

  In the alternative syntax forms:
           <const>          Specifies the offset value for the ADD form and minus the offset value for the SUB form.
                            Allowed values are multiples of four in the range 0 to 1020 for encoding T1 and any value
                            in the range 0 to 4095 for encodings T2 and T3.
*/
void ADRT2(uint32_t instruction)
{
  uint32_t imm8 = getBits(instruction, 7, 0);
  uint32_t Rd = getBits(instruction, 11, 8);
  uint32_t imm3 = getBits(instruction, 14, 12);

  uint32_t i = getBits(instruction, 26, 26);
  uint32_t temp = (i << 3 ) | imm3;

  uint32_t ModifiedConstant = temp << 8 | imm8;

  if(inITBlock())
  {
    if( checkCondition(cond) )
      executeADR(Rd, ModifiedConstant, FALSE);
    shiftITState();
  }
  else
    executeADR(Rd, ModifiedConstant, FALSE);

  coreReg[PC] += 4;
}


/* Address to Register Encoding T3
   ADR<c>.W <Rd>,<label>                <label> after current instruction
   ADD<c><q> <Rd>, PC, #<const>         Alternative for encodings

   31 30 29 28 27 26 25 24 23 22 21 20 19 18 17 16 15 14 13 12 11 10 9 8 7 6 5 4 3 2 1 0
  |1  1  1  1  0 |i| 1  0  0  0  0 |0| 1  1  1  1 |0|  imm3   |    Rd   |     imm8      |

where:
            <c><q>          See Standard assembler syntax fields on page A6-7.

            <Rd>            Specifies the destination register.

            <label>         Specifies the label of an instruction or literal data item whose address is to be loaded into

            <Rd>.           The assembler calculates the required value of the offset from the Align(PC,4) value
                            of the ADR instruction to this label.
                            If the offset is positive, encodings T1 and T3 are permitted with imm32 equal to the offset.
                            Allowed values of the offset are multiples of four in the range 0 to 1020 for encoding T1 and
                            any value in the range 0 to 4095 for encoding T3.

  In the alternative syntax forms:
           <const>          Specifies the offset value for the ADD form and minus the offset value for the SUB form.
                            Allowed values are multiples of four in the range 0 to 1020 for encoding T1 and any value
                            in the range 0 to 4095 for encodings T2 and T3.
*/
void ADRT3(uint32_t instruction)
{
  uint32_t imm8 = getBits(instruction, 7, 0);
  uint32_t Rd = getBits(instruction, 11, 8);
  uint32_t imm3 = getBits(instruction, 14, 12);

  uint32_t i = getBits(instruction, 26, 26);
  uint32_t temp = (i << 3 ) | imm3;

  uint32_t ModifiedConstant = temp << 8 | imm8;

  if(inITBlock())
  {
    if( checkCondition(cond) )
      executeADR(Rd, ModifiedConstant, TRUE);
    shiftITState();
  }
  else
    executeADR(Rd, ModifiedConstant, TRUE);

  coreReg[PC] += 4;
}


uint32_t alignPC(uint32_t value, uint32_t alignIndex)
{
  return (alignIndex * (value/alignIndex) );

}


/* This instruction adds an immediate value to the PC value, and writes the result to the destination register.

   Input: Rd          destination register
          immediate   immediate value which will be added with PC value
*/
void executeADR(uint32_t Rd, uint32_t immediate, Add add)
{
  uint32_t PCAfterAlign = alignPC(coreReg[PC]+4, 4);
  
  if(add == TRUE)
    coreReg[Rd] =  PCAfterAlign + immediate;
  else
    coreReg[Rd] =  PCAfterAlign - immediate;
}