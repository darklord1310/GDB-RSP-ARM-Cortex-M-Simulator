#include "CMNRegister.h"
#include "ITandHints.h"
#include "StatusRegisters.h"
#include "ARMRegisters.h"
#include "getAndSetBits.h"
#include "getMask.h"
#include "ShiftOperation.h"
#include "ConditionalExecution.h"


/*Compare Register Encoding T1

    CMN<c> <Rn>,<Rm>
       
   31 30 29 28 27 26 25 24 23 22 21 20 19 18 17 16 15 14 13 12 11 10 9 8 7 6 5 4 3 2 1 0
  |0   1  0  0  0  0| 1  0  1  1|   Rm  |   Rn    |                unused               |
  
  where:
          <c><q>      See Standard assembler syntax fields on page A6-7.
          
          <Rn>        Specifies the register that contains the first operand. The SP can be used.
          
          <Rm>        Specifies the register that is optionally shifted and used as the second operand. The SP can
                      be used, but use of the SP is deprecated.
                      
         <shift>      Specifies the shift to apply to the value read from <Rm>. If <shift> is omitted, no shift is
                      applied and all encodings are permitted. If shift is specified, only encoding T3 is permitted.
                      The possible shifts and how they are encoded are described in Shifts applied to a register on
                      page A6-12.
                      
*/
void CMNRegisterT1(uint32_t instruction)
{
  uint32_t Rm = getBits(instruction, 21, 19);
  uint32_t Rn = getBits(instruction, 18, 16);

  if(inITBlock())
  {
    if( checkCondition(cond) )
      executeCMNRegister(Rm, Rn, 0, 0);
    
    shiftITState();
  }
  else
    executeCMNRegister(Rm, Rn, 0, 0);
  
  coreReg[PC] += 2;
}


/* Compare Register Encoding T2

   CMN<c>.W <Rn>,<Rm>{,<shift>}

   31 30 29 28 27 26 25 24 23 22 21 20 19 18 17 16 15 14 13 12 11 10 9 8 7 6 5 4 3 2 1 0
  |1  1  1  0  1 |0  1 |1  0  0  0 |1|     Rn     |0|   imm3  |1  1  11|imm2| t |   Rm  |

  t => type

where:
          S           If present, specifies that the instruction updates the flags. Otherwise, the instruction does not
                      update the flags.

          <c><q>      See Standard assembler syntax fields on page A6-7.

          <Rn>        Specifies the register that contains the first operand. This register is allowed to be the SP.

          <Rm>        Specifies the register that is optionally shifted and used as the second operand.

          <shift>     Specifies the shift to apply to the value read from <Rm>. If <shift> is omitted, no shift is
                      applied and all encodings are permitted. If <shift> is specified, only encoding T3 is
                      permitted. The possible shifts and how they are encoded are described in Shifts applied to a
                      register on page A6-12.
*/
void CMNRegisterT2(uint32_t instruction)
{
  uint32_t Rm =  getBits(instruction, 3, 0);
  uint32_t Rn = getBits(instruction, 19, 16);
  uint32_t imm2 = getBits(instruction, 7, 6);
  uint32_t imm3 = getBits(instruction, 14, 12);
  uint32_t shiftType = getBits(instruction, 5, 4);

  uint32_t shiftImm = (imm3 << 2 ) | imm2;

  if(inITBlock())
  {
    if( checkCondition(cond) )
      executeCMNRegister(Rm, Rn, shiftType, shiftImm);
    shiftITState();
  }
  else
    executeCMNRegister(Rm, Rn, shiftType, shiftImm);

  coreReg[PC] += 4;
}


/*
  This function will execute the Compare Negative Register Instruction for
  both 16bits and 32bits instruction, this function will be share
  among two
  
  Input : Rm           the source register
          Rn           the destination register
          shiftType       determine what type of shifting is needed
          shiftImmediate  shift range from 0 to 31
*/
void executeCMNRegister(uint32_t Rm, uint32_t Rn, uint32_t shiftType, uint32_t shiftImmediate)
{
  uint32_t backupRn = coreReg[Rn];
  uint32_t shiftedRm, result;

  shiftType = determineShiftOperation(shiftType, shiftImmediate);
  shiftedRm = executeShiftOperation(shiftType, shiftImmediate, coreReg[Rm], 0);

  result = coreReg[Rn] + shiftedRm;

  updateZeroFlag(result);
  updateCarryFlagAddition(coreReg[Rn] , shiftedRm);
  updateNegativeFlag(result);
  updateOverflowFlagAddition(coreReg[Rn], shiftedRm, result);
}
