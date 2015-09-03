#include "ORNImmediate.h"
#include "ITandHints.h"
#include "ConditionalExecution.h"
#include <stdio.h>

/*  ORN Immediate Encoding T1

ORN{S}<c> <Rd>,<Rn>,#<const>

31 30 29 28 27 26 25 24 23 22 21 20 19 18 17 16 15 14 13 12 11 10 9 8 7 6 5 4 3 2 1 0
|1  1  1  1 0 |i||0| 0  0  1  1 |S|     Rn     |0|  imm3   |    Rd   |     imm8      |

where:
          S         If present, specifies that the instruction updates the flags. Otherwise, the
                    instruction does not update the flags.

          <c><q>    See Standard assembler syntax fields on page A6-7.
          
          <Rd>      Specifies the destination register. If <Rd> is omitted, this register is the
                    same as <Rn>.

          <Rn>      Specifies the register that contains the operand.

          <const>   Specifies the immediate value to be tested against the value obtained from <Rn>. See
                    Modified immediate constants in Thumb instructions on page A5-15 for the range of
                    allowed values.
*/
void ORNImmediateT1(uint32_t instruction)
{
    uint32_t imm8 = getBits(instruction, 7, 0);
    uint32_t Rd = getBits(instruction, 11, 8);
    uint32_t Rn = getBits(instruction, 19, 16);
    uint32_t imm3 = getBits(instruction, 14, 12);
    uint32_t statusFlag = getBits(instruction, 20, 20);
    uint32_t i = getBits(instruction, 26, 26);
    uint32_t bit7 = getBits(instruction, 7, 7);
    uint32_t temp = (i << 3 ) | imm3;
    uint32_t modifyControl = (temp << 1) | getBits(imm8,7,7);

    uint32_t ModifiedConstant = ModifyImmediateConstant(modifyControl, imm8);

    if(inITBlock())
    {
        if( checkCondition(cond) )
            executeORNImmediate(ModifiedConstant, Rd, Rn, statusFlag);
        shiftITState();
    }
    else
        executeORNImmediate(ModifiedConstant, Rd, Rn, statusFlag);

    coreReg[PC] += 4;
}


/*  This function will perform the ORN immediate

    Input:  immediate       the NOT immediate going to OR with Rn and move into Rd
            Rd              destination register
            Rn              register that contains the first operand
            S               indicator for affecting the flag or not
*/
void executeORNImmediate(uint32_t immediate, uint32_t Rd, uint32_t Rn, uint32_t S)
{
    coreReg[Rd] = ~immediate | coreReg[Rn];

    if(S == 1)
    {
        updateZeroFlag(coreReg[Rd]);
        updateNegativeFlag(coreReg[Rd]);
    }
}
