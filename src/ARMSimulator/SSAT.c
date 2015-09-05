#include "SSAT.h"


/* Signed Saturate Encoding T1

SSAT<c> <Rd>,#<imm5>,<Rn>{,<shift>}

31 30 29 28 27 26 25 24 23 22 21 20 19 18 17 16 15 14 13 12 11 10 9 8 7 6 5 4 3 2 1 0
|1  1  1  1 0 |0| 1  1 |0  0||sh|0|     Rn     |0|  imm3   |    Rd  |imm2|0| sat_imm |

where :
          <c><q>        See Standard assembler syntax fields on page A6-7.

          <Rd>          Specifies the destination register.

          <imm5>        Specifies the bit position for saturation, in the range 1 to 32.

          <Rn>          Specifies the register that contains the value to be saturated.

          <shift>       Specifies the optional shift. If <shift> is omitted, LSL #0 is used.
                        If present, it must be one of:
                        LSL #N N must be in the range 0 to 31.
                        ASR #N N must be in the range 1 to 31.
*/
void SSATT1(uint32_t instruction)
{
  uint32_t Rd = getBits(instruction, 11, 8);
  uint32_t Rn = getBits(instruction, 19, 16);
  uint32_t sat_imm = getBits(instruction, 5, 0);    // imm5
  uint32_t imm2 = getBits(instruction, 7, 6);
  uint32_t imm3 = getBits(instruction, 14, 12);
  uint32_t sh = getBits(instruction, 21, 21);      // 0 => LSL, 1 => ASR

  uint32_t shiftImm = (imm3 << 2) | imm2;          // Shift immediate (N)

  if(inITBlock())
  {
    if( checkCondition(cond) )
      executeSSAT(Rd, Rn, sat_imm, sh, shiftImm);
    shiftITState();
  }
  else
    executeSSAT(Rd, Rn, sat_imm, sh, shiftImm);

  coreReg[PC] += 4;
}


/* This instruction saturates an optionally-shifted signed value to a selectable signed range.
   The Q flag is set if the operation saturates.

   Input: Rn                register that contains the value to be saturated
          Rd                destination register
          immediate         immediate value which will saturated signed value to a selectable signed range
          shiftDirection    logical left or right shift
          shiftImmediate    immediate value which will shift Rn
*/
void executeSSAT(uint32_t Rd, uint32_t Rn, uint32_t immediate, uint32_t shiftDirection, uint32_t shiftImmediate)
{
  int32_t shiftRn, temp, signedRange;

  signedRange = (int32_t)pow(2, immediate + 1) / 2;

  if(shiftDirection)
    shiftRn = coreReg[Rn] >> shiftImmediate;
  else
    shiftRn = coreReg[Rn] << shiftImmediate;

  temp = (shiftRn < -signedRange) ? -signedRange: (shiftRn > (signedRange - 1) ? (signedRange - 1): shiftRn);
  coreReg[Rd] = temp;
  
  updateQFlag(signedRange, shiftRn);
}
