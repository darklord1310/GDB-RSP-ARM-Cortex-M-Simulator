#include "TEQImmediate.h"
#include "ITandHints.h"
#include "ConditionalExecution.h"
#include <stdio.h>

/*  TEQ Immediate Encoding T1

TEQ<c> <Rn>,#<const>

31 30 29 28 27 26 25 24 23 22 21 20 19 18 17 16 15 14 13 12 11 10 9 8 7 6 5 4 3 2 1 0
|1  1  1  1 0 |i||0| 0  1  0  0 |1|     Rn     |0|  imm3   |1  1  1 1|     imm8      |

where:
          <c><q>    See Standard assembler syntax fields on page A6-7.

          <Rn>      Specifies the register that contains the operand.

          <const>   Specifies the immediate value to be added to the value obtained from <Rn>. See Modified
                    immediate constants in Thumb instructions on page A5-15 for the range of allowed values
*/
void TEQImmediateT1(uint32_t instruction)
{
    uint32_t imm8 = getBits(instruction, 7, 0);
    uint32_t Rn = getBits(instruction, 19, 16);
    uint32_t imm3 = getBits(instruction, 14, 12);
    uint32_t i = getBits(instruction, 26, 26);
    uint32_t bit7 = getBits(instruction, 7, 7);
    uint32_t temp = (i << 3 ) | imm3;
    uint32_t modifyControl = (temp << 1) | bit7;

    uint32_t ModifiedConstant = ModifyImmediateConstant(modifyControl, imm8, 1);

    if(inITBlock())
    {
        if( checkCondition(cond) )
            executeTEQImmediate(ModifiedConstant, Rn);
        shiftITState();
    }
    else
        executeTEQImmediate(ModifiedConstant, Rn);

    coreReg[PC] += 4;
}


/*  This instruction XOR an immediate value to a register value, and discard the result.

    Input:  immediate       the immediate going to XOR with Rn and update the status flag
            Rn              register that contains the first operand
*/
void executeTEQImmediate(uint32_t immediate, uint32_t Rn)
{
    uint32_t result = immediate ^ coreReg[Rn];

    updateZeroFlag(result);
    updateNegativeFlag(result);
}
