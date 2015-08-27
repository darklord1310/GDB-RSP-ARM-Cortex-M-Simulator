#include "CMPRegister.h"
#include "ITandHints.h"
#include "StatusRegisters.h"
#include "ARMRegisters.h"
#include "getAndSetBits.h"
#include "getMask.h"
#include "ModifiedImmediateConstant.h"
#include "Thumb16bitsTable.h"
#include "ConditionalExecution.h"


/*Compare Register Encoding T1

    CMP<c> <Rn>,<Rm>
       
   31 30 29 28 27 26 25 24 23 22 21 20 19 18 17 16 15 14 13 12 11 10 9 8 7 6 5 4 3 2 1 0
  |0   1  0  0  0  0| 1  0  1  0|   Rm  |   Rn    |                unused                  |
  
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
void CMPRegisterT1(uint32_t instruction)
{
  uint32_t Rm = getBits(instruction, 21, 19);
  uint32_t Rn = getBits(instruction, 18, 16);

  if(inITBlock())
  {
    if( checkCondition(cond) )
      executeCMPRegister(Rm, Rn, -1);
    
    shiftITState();
  }
  else
    executeCMPRegister(Rm, Rn, -1);
  
  coreReg[PC] += 2;
}



/*Compare Register Encoding T1

    CMP<c> <Rn>,<Rm>
       
   31 30 29 28 27 26 25 24 23 22 21 20 19 18 17 16 15 14 13 12 11 10 9 8 7 6 5 4 3 2 1 0
  |0   1  0  0  0  1| 0  1|N|     Rm     |   Rn   |              unused                |
  
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
void CMPRegisterT2(uint32_t instruction)
{
  uint32_t Rm = getBits(instruction, 22, 19);
  uint32_t Rn = getBits(instruction, 18, 16);
  uint32_t N = getBits(instruction, 23, 23);
  
  Rn = (N << 3) | Rn;
  
  if(inITBlock())
  {
    if( checkCondition(cond) )
      executeCMPRegister(Rm, Rn, -1);
    
    shiftITState();
  }
  else
    executeCMPRegister(Rm, Rn, -1); 
  
  coreReg[PC] += 2;
}



/*
  This function will execute the Compare Register Instruction for
  both 16bits and 32bits instruction, this function will be share
  among two
  
  Input : Rm           the source register
          Rn           the destination register
          shiftType    determine what type of shifting is needed, -1 if no shifting
*/
void executeCMPRegister(uint32_t Rm, uint32_t Rn, uint32_t shiftType)
{
  uint32_t temp = coreReg[Rn] - coreReg[Rm];

  updateZeroFlag(temp);
  updateCarryFlagSubtraction(coreReg[Rn] , coreReg[Rm]);
  updateNegativeFlag(temp);
  updateOverflowFlagSubtraction(coreReg[Rn], coreReg[Rm], temp);
}