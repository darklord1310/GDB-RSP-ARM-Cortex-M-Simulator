#include "MOVT.h"


/* Move Top Encoding T1

MOVT<c> <Rd>,#<imm16>

31 30 29 28 27 26 25 24 23 22 21 20 19 18 17 16 15 14 13 12 11 10 9 8 7 6 5 4 3 2 1 0
|1  1  1  1 0 |i| 1  0 |1||1||0||0|    imm4    |0|  imm3   |    Rd   |     imm8      |

where :
          <c><q>        See Standard assembler syntax fields on page A6-7.

          <Rd>          Specifies the destination register.

          <imm16>       Specifies the immediate value to be written to <Rd>. It must be in the range 0-65535.
*/
void MOVTT1(uint32_t instruction)
{
  uint32_t imm8 = getBits(instruction, 7, 0);
  uint32_t Rd = getBits(instruction, 11, 8);
  uint32_t imm3 = getBits(instruction, 14, 12);
  uint32_t imm4 = getBits(instruction, 19, 16);
  uint32_t i = getBits(instruction, 26, 26);
  
  uint32_t imm16 = (imm3 << 8) | imm8;

  imm16 |= (i << 11);
  imm16 |= (imm4 << 12);

  if(inITBlock())
  {
    if( checkCondition(cond) )
      executeMOVT(Rd, imm16);
    shiftITState();
  }
  else
    executeMOVT(Rd, imm16);

  coreReg[PC] += 4;
}

/* This instruction writes an immediate value to the top halfword of the destination register.
   It does not affect the contents of the bottom halfword.

   Input: Rd          destination register
          immediate   immediate value which will be writed to top halfword of Rd
*/
void executeMOVT(uint32_t Rd, uint32_t immediate)
{
  coreReg[Rd] = immediate << 16 | (coreReg[Rd] & 0xffff);
}