#include "SBCRegister.h"
#include <assert.h>
#include "ARMRegisters.h"
#include "getAndSetBits.h"
#include "StatusRegisters.h"
#include "ModifiedImmediateConstant.h"
#include "ITandHints.h"
#include "ConditionalExecution.h"
#include "ShiftOperation.h"
#include <stdio.h>


/*Subtract with Carry Register To Register Encoding T1
  SBCS        <Rdn>,<Rm>     Outside IT block.
  SBC<c>      <Rdn>,<Rm>     Inside IT block.

   31 30 29 28 27 26 25 24 23 22 21 20 19 18 17 16 15 14 13 12 11 10 9 8 7 6 5 4 3 2 1 0
  |0   1  0  0  0  0| 0  1  1  0|   Rm   |   Rdn  |             unused                  |

where:
          S           If present, specifies that the instruction updates the flags. Otherwise, the instruction does not
                      update the flags.

          <c><q>      See Standard assembler syntax fields on page A6-7.

          <Rd>        Specifies the destination register. If <Rd> is omitted, this register is the same as <Rn> and
                      encoding T2 is preferred to encoding T1 if both are available (this can only happen inside
                      an IT block). If <Rd> is specified, encoding T1 is preferred to encoding T2.

          <Rn>        Specifies the register that contains the first operand. If the SP is specified for <Rn>, see ADD
                      (SP plus register) on page A6-28.

          <Rm>        Specifies the register that is optionally shifted and used as the second operand.

          <shift>     Specifies the shift to apply to the value read from <Rm>. If <shift> is omitted, no shift is
		      applied and both encodings are permitted. If <shift> is specified, only encoding T2 is
                      permitted. The possible shifts and how they are encoded are described in Shifts applied to a
                      register on page A6-12.
*/
void SBCRegisterT1(uint32_t instruction)
{
  uint32_t Rm =  getBits(instruction,21,19);
  uint32_t Rdn = getBits(instruction,18,16);

 if(inITBlock())
 {
    if( checkCondition(cond) )
      executeSBCRegister(Rm, Rdn, Rdn, 0, 0, 0);
    shiftITState();
 }
 else
    executeSBCRegister(Rm, Rdn, Rdn, 1, 0, 0);

  coreReg[PC] += 2;
}


/* Subtract with Carry Register Encoding T2

   SBC{S}<c>.W <Rd>,<Rn>,<Rm>{,<shift>}

   31 30 29 28 27 26 25 24 23 22 21 20 19 18 17 16 15 14 13 12 11 10 9 8 7 6 5 4 3 2 1 0
  |1  1  1  0  1 |0  1 |1  0  1  1 |S|     Rn     |0|   imm3  |   Rd   |imm2| t |   Rm  |

  t => type

where:
          S           If present, specifies that the instruction updates the flags. Otherwise, the instruction does not
                      update the flags.

          <c><q>      See Standard assembler syntax fields on page A6-7.

          <Rd>        Specifies the destination register. If <Rd> is omitted, this register is the same as <Rn> and
                      encoding T2 is preferred to encoding T1 if both are available (this can only happen inside
                      an IT block). If <Rd> is specified, encoding T1 is preferred to encoding T2.

          <Rn>        Specifies the register that contains the first operand. If the SP is specified for <Rn>, see ADD
                      (SP plus register) on page A6-28.

          <Rm>        Specifies the register that is optionally shifted and used as the second operand.

          <shift>     Specifies the shift to apply to the value read from <Rm>. If <shift> is omitted, no shift is
                      applied and all encodings are permitted. If <shift> is specified, only encoding T3 is
                      permitted. The possible shifts and how they are encoded are described in Shifts applied to a
                      register on page A6-12.
*/
void SBCRegisterT2(uint32_t instruction)
{
  uint32_t Rm =  getBits(instruction, 3, 0);
  uint32_t Rd = getBits(instruction, 11, 8);
  uint32_t Rn = getBits(instruction, 19, 16);
  uint32_t imm2 = getBits(instruction, 7, 6);
  uint32_t imm3 = getBits(instruction, 14, 12);
  uint32_t statusFlag = getBits(instruction, 20, 20);
  uint32_t shiftType = getBits(instruction, 5, 4);

  uint32_t shiftImm = (imm3 << 2 ) | imm2;

  if(inITBlock())
  {
    if( checkCondition(cond) )
      executeSBCRegister(Rm, Rd, Rn, statusFlag, shiftType, shiftImm);
    shiftITState();
  }
  else
    executeSBCRegister(Rm, Rd, Rn, statusFlag, shiftType, shiftImm);

  coreReg[PC] += 4;
}


/* Subtract with Carry (register) subtracts an optionally-shifted register value and the value of NOT(Carry flag)
   from a register value, and writes the result to the destination register. It can optionally update the condition
   flags based on the result.

   Input: Rn          register value which will be subtracted with Rm
          Rd          destination register
          Rm          register value which will be subtracted with Rn after shifted
          S           if set will affect the status register
          shiftType       determine what type of shifting is needed
          shiftImmediate  shift range from 0 to 31
*/
void executeSBCRegister(uint32_t Rm, uint32_t Rd, uint32_t Rn, uint32_t S, uint32_t shiftType, uint32_t shiftImmediate)
{
  uint32_t backupRn = coreReg[Rn];                                      //this is to avoid the value of Rn being overwritten in case
                                                                        //of Rn and Rd is pointing to the same register
  uint32_t carry = ~getBits(coreReg[xPSR], 29, 29) & 0x1;
  uint32_t shiftedRm, temp;

  shiftType = determineShiftOperation(shiftType, shiftImmediate);
  shiftedRm = executeShiftOperation(shiftType, shiftImmediate, coreReg[Rm], 0);

  temp = coreReg[Rn] - shiftedRm;
  coreReg[Rd] = temp - carry;                                       //get the result of Rn - Rm - Carry

  if(S == 1)
  {
    updateZeroFlag(coreReg[Rd]);
    updateNegativeFlag(coreReg[Rd]);

    updateOverflowFlagSubtraction(backupRn, shiftedRm, temp);
    if(isOverflow() == 0)
      updateOverflowFlagSubtraction(temp, carry , coreReg[Rd]);

    updateCarryFlagSubtraction(backupRn, shiftedRm);
    if(isCarry() == 1)
      updateCarryFlagSubtraction(temp, carry);
  }
}