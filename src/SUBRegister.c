#include "SUBRegister.h"
#include <assert.h>


/*Subtract Register To Register Encoding T1
    SUBS <Rd>,<Rn>,<Rm>     Outside IT block.
    SUB<c> <Rd>,<Rn>,<Rm>   Inside IT block.
      
   31 30 29 28 27 26 25 24 23 22 21 20 19 18 17 16 15 14 13 12 11 10 9 8 7 6 5 4 3 2 1 0
  |0  0   0| 1  1| 0  1|   Rm   |   Rn   |   Rd   |                unused               |

where:
          S           If present, specifies that the instruction updates the flags. Otherwise, the instruction does not
                      update the flags.
                      
          <c><q>      See Standard assembler syntax fields on page A6-7.
          
          <Rd>        Specifies the destination register. If <Rd> is omitted, this register is the same as <Rn> and
                      encoding T2 is preferred to encoding T1 if both are available (this can only happen inside
                      an IT block). If <Rd> is specified, encoding T1 is preferred to encoding T2.
                      
          <Rn>        Specifies the register that contains the first operand. If the SP is specified for <Rn>, see SUB
                      (SP minus register) on page A6-28.
                      
          <Rm>        Specifies the register that is optionally shifted and used as the second operand.
          
          <shift>     Specifies the shift to apply to the value read from <Rm>. If <shift> is omitted, no shift is
                      applied and all encodings are permitted. If <shift> is specified, only encoding T3 is
                      permitted. The possible shifts and how they are encoded are described in Shifts applied to a
                      register on page A6-12.
                      
          Inside an IT block, if ADD<c> <Rd>,<Rn>,<Rd> cannot be assembled using encoding T1, it is assembled using
          encoding T2 as though ADD<c> <Rd>,<Rn> had been written. To prevent this happening, use the .W qualifier.
*/
void SUBRegisterToRegisterT1(uint32_t instruction)
{
  uint32_t Rm = getBits(instruction,24,22);
  uint32_t Rn = getBits(instruction,21,19);
  uint32_t Rd = getBits(instruction,18,16);
  assert(Rm <= 0b111);
  assert(Rn <= 0b111);
  assert(Rd <= 0b111);
  
 if(inITBlock())
    executeSUBRegister(Rn, Rd, Rm, 0);
 else
    executeSUBRegister(Rn, Rd, Rm, 1);
}


/* This instruction subtract a register value and an optionally-shifted register value, and writes the result to the
   destination register. It can optionally update the condition flags based on the result.

   Input: Rn          register value which will be subtract with Rm  
          Rd          destination register
          Rm          register value which will be subtract with Rn
          S           if set will affect the status register
*/
void executeSUBRegister(uint32_t Rn, uint32_t Rd, uint32_t Rm, uint32_t S)
{
  coreReg[Rd] = coreReg[Rn] - coreReg[Rm];            //get the result of Rn - Rm
  
  if(S == 1)
  {
    updateZeroFlag(coreReg[Rd]);
    updateNegativeFlag(coreReg[Rd]);
    updateOverflowFlagSubtraction(coreReg[Rn], coreReg[Rm], coreReg[Rd]);
    updateCarryFlagSubtraction(coreReg[Rn], coreReg[Rm]);
  }
}