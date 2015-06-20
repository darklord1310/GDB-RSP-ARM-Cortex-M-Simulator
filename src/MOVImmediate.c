#include "MOVImmediate.h"
#include <stdio.h>

/*Move Immediate Encoding T1
        MOVS <Rd>,#<imm8>               Outside IT block.
        MOV<c> <Rd>,#<imm8>             Inside IT block.

  Note : This instruction can never move any negative value
  
   31 30 29 28 27 26 25 24 23 22 21 20 19 18 17 16 15 14 13 12 11 10 9 8 7 6 5 4 3 2 1 0
  |0   0  1| 0  0|   Rd   |         imm8          |               unused                |
   
where:
        S         If present, specifies that the instruction updates the flags. Otherwise, the instruction does not
                  update the flags.
                
        <c><q>    See Standard assembler syntax fields on page A6-7.
        
        <Rd>      Specifies the destination register. It can only cover until R7 because of 3 bits
        
        <const>   Specifies the immediate value to be placed in <Rd>. The range of allowed values is 0-255 for
                  encoding T1

*/
void MOVImmediateT1(uint32_t instruction)
{
	uint32_t imm8 = getBits(instruction, 23, 16);
	uint32_t destinationRegister = getBits(instruction, 26, 24);
	
  //if(inITBlock)
    //executeMOVImmediate(uint32_t immediate, uint32_t Rd, 0);
  //else
    executeMOVImmediate(imm8, destinationRegister, 1);
}




/* Move Immediate Encoding T2

MOV{S}<c>.W <Rd>,#<const>

31 30 29 28 27 26 25 24 23 22 21 20 19 18 17 16 15 14 13 12 11 10 9 8 7 6 5 4 3 2 1 0
|1  1  1  1 0 |i| 0  0  0  1  0 |S| 1  1  1  1  0 |  imm3  |    Rd   |     imm8      |

where:
          S         If present, specifies that the instruction updates the flags. Otherwise, the instruction does not
                    update the flags.
                  
          <c><q>    See Standard assembler syntax fields on page A6-7.
          
          <Rd>      Specifies the destination register.
          
          <const>   Specifies the immediate value to be placed in <Rd>. The range of allowed values is 0-255 for
                    encoding T1 and 0-65535 for encoding T3. See Modified immediate constants in Thumb
                    instructions on page A5-15 for the range of allowed values for encoding T2.
                    
          When both 32-bit encodings are available for an instruction, encoding T2 is preferred to
          encoding T3 (if encoding T3 is required, use the MOVW syntax)
*/
void MOVImmediateT2(uint32_t instruction)
{
  uint32_t imm8 = getBits(instruction, 7, 0);
  uint32_t Rd = getBits(instruction, 11, 8);
  uint32_t imm3 = getBits(instruction, 14, 12);
  uint32_t statusFlag = getBits(instruction, 20, 20);
  uint32_t i = getBits(instruction, 26, 26);
  uint32_t bit7 = getBits(instruction, 7, 7);
  
  uint32_t ModifiedConstant = ModifyImmediateConstant(i,imm3, bit7, imm8);

  executeMOVImmediate(ModifiedConstant, Rd, statusFlag);
}



/* Move Immediate Encoding T3

MOVW<c> <Rd>,#<imm16>

31 30 29 28 27 26 25 24 23 22 21 20 19 18 17 16 15 14 13 12 11 10 9 8 7 6 5 4 3 2 1 0
|1  1  1  1 0 |i| 1  0  0  1  0  0 |   imm4    |0|  imm3   |    Rd   |     imm8      |

This instruction will not affect the status register
largest value for the constant is 65536 which means 16 bits value

16 bits = imm4 | i | imm3 | imm8

where:
          S         If present, specifies that the instruction updates the flags. Otherwise, the instruction does not
                    update the flags.
                  
          <c><q>    See Standard assembler syntax fields on page A6-7.
          
          <Rd>      Specifies the destination register.
          
          <const>   Specifies the immediate value to be placed in <Rd>. The range of allowed values is 0-255 for
                    encoding T1 and 0-65535 for encoding T3. See Modified immediate constants in Thumb
                    instructions on page A5-15 for the range of allowed values for encoding T2.
                    
          When both 32-bit encodings are available for an instruction, encoding T2 is preferred to
          encoding T3 (if encoding T3 is required, use the MOVW syntax)
*/
void MOVImmediateT3(uint32_t instruction)
{
  uint32_t imm8 = getBits(instruction, 7, 0);
  uint32_t Rd = getBits(instruction, 11, 8);
  uint32_t imm3 = getBits(instruction, 14, 12);
  uint32_t imm4 = getBits(instruction, 19, 16);
  uint32_t i = getBits(instruction, 26, 26);
  
  uint32_t constant;
  
  constant = ( imm3 << 8 ) | imm8;
  constant = ( i << 11 ) | constant;
  constant = ( imm4 << 12) | constant;
 
  executeMOVImmediate(constant, Rd, 0);
}


void executeMOVImmediate(uint32_t immediate, uint32_t Rd, uint32_t S)
{
  coreReg->reg[Rd].data = immediate;                              //move immediate into destination register
  int MSBofImmediate = getBits(coreReg->reg[Rd].data,31,31);      //check the bit31 of the immediate, set carry flag
                                                                  //accordingly
  if(S == 1)
  {
    updateZeroFlag(coreReg->reg[Rd].data);
    updateNegativeFlag(coreReg->reg[Rd].data);
    if(immediate > 0xff)                                          //When an Operand2 constant is used with the instructions MOVS, MVNS, ANDS, ORRS, 
    {                                                             //ORNS, EORS, BICS, TEQ or TST, the carry flag is updated to bit[31] of the constant
                                                                  //if the constant is greater than 255 and can be produced by shifting an 8-bit value
      if(MSBofImmediate == 1)
        setCarryFlag();
      else
        resetCarryFlag();
    }
  }
}


