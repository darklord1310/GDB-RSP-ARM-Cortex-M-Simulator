#include "SignedAndUnsignedBitFieldExtract.h"


/* Signed Bit Field Extract Encoding T1

SBFX<c> <Rd>,<Rn>,#<lsb>,#<width>

31 30 29 28 27 26 25 24 23 22 21 20 19 18 17 16 15 14 13 12 11 10 9 8 7 6 5 4 3 2 1 0
|1  1  1  1 0 |0| 1  1 |0  1  0 |0|     Rn     |0|  imm3   |    Rd  |imm2|0| widthm1 |

where :
          <c><q>        See Standard assembler syntax fields on page A6-7.

          <Rd>          Specifies the destination register.

          <Rn>          Specifies the register that contains the first operand.

          <lsb>         is the bit number of the least significant bit in the bitfield, in the range 0-31. This determines
                        the required value of lsbit.

          <width>       is the width of the bitfield, in the range 1 to 32-<lsb>. The required value of widthminus1 is
                        <width>-1.

This instruction extracts any number of adjacent bits at any position from one register, sign extends them to 32 bits,
and writes the result to the destination register
*/
void SBFXT1(uint32_t instruction)
{
  uint32_t Rd = getBits(instruction, 11, 8);
  uint32_t Rn = getBits(instruction, 19, 16);
  uint32_t widthm1 = getBits(instruction, 5, 0);    // <width> - 1
  uint32_t imm2 = getBits(instruction, 7, 6);
  uint32_t imm3 = getBits(instruction, 14, 12);

  uint32_t lsbit = (imm3 << 2) | imm2;              // <lsb>
  uint32_t msbit = lsbit + widthm1;
  uint32_t temp = getBits(coreReg[Rn], msbit, lsbit);
  uint32_t tempMSB = msbit + 1 - lsbit;

  if(inITBlock())
  {
    if( checkCondition(cond) )
      coreReg[Rd] = signExtend(temp, tempMSB);
    shiftITState();
  }
  else
    coreReg[Rd] = signExtend(temp, tempMSB);

  coreReg[PC] += 4;
}

/* This instruction  extracts any number of adjacent bits at any position from one register, sign extends
   them to 32 bits, and writes the result to the destination register

   Input: Rn                register that contains the value to be saturated
          Rd                destination register
          immediate         immediate value which will saturated signed value to a selectable signed range
          shiftDirection    logical left or right shift
          shiftImmediate    immediate value which will shift Rn
*/
/* void executeSBFX(uint32_t Rd, uint32_t Rn, uint32_t lsbit, uint32_t width)
{
  uint32_t msbit = lsbit + width;
  uint32_t temp = getBits(coreReg[Rn], msbit, lsbit);

  // sign extends
  if(getBits(coreReg[Rn], msbit, msbit))
    coreReg[Rd] = temp | 0x0;
  else
    coreReg[Rd] = temp & 0x0;
} */
