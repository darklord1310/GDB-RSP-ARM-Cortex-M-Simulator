#include "ADDSPRegister.h"
#include "ITandHints.h"
#include "StatusRegisters.h"
#include "ARMRegisters.h"
#include "getAndSetBits.h"
#include "getMask.h"
#include "ModifiedImmediateConstant.h"
#include "ConditionalExecution.h"
#include "MemoryBlock.h"
#include <stdio.h>
#include "ADR.h"

/*Add SP with Register Encoding T1
    ADD<c> <Rdm>, SP, <Rdm>
      
  31 30 29 28 27 26 25 24 23 22 21 20 19 18 17 16 15 14 13 12 11 10 9 8 7 6 5 4 3 2 1 0
  |0   1  0  0  0  1| 0  0|DN|1  1  0  1|   Rdm  |                unused               |

  setflags = FALSE
  
where:
              S                 If present, specifies that the instruction updates the flags. Otherwise, the instruction does not
                                update the flags.
                                
              <c><q>            See Standard assembler syntax fields on page A6-7.
              
              <Rd>              Specifies the destination register. If <Rd> is omitted, this register is SP.
                                The use of the PC as <Rd> in encoding T1 is deprecated.
                                
              <Rm>              Specifies the register that is optionally shifted and used as the second operand.
                                The use of the SP as <Rm> in encoding T1 is deprecated.
                                The use of the PC as <Rm> in encoding T1 and encoding T2 is deprecated.
                                
              <shift>           Specifies the shift to apply to the value read from <Rm>. If <shift> is omitted, no shift is
                                applied and all encodings are permitted. If <shift> is specified, only encoding T3 is
                                permitted. The possible shifts and how they are encoded are described in Shifts applied to a
                                register on page A6-12.
                                
              If <Rd> is SP or omitted, <shift> is only permitted to be LSL #0, LSL #1, LSL #2 or LSL #3.
                      
              Inside an IT block, if ADD<c> <Rd>,<Rn>,<Rd> cannot be assembled using encoding T1, it is assembled using
              encoding T2 as though ADD<c> <Rd>,<Rn> had been written. To prevent this happening, use the .W qualifier.
*/
void ADDSPRegisterT1(uint32_t instruction)
{
  uint32_t DN = getBits(instruction,23,23);
  uint32_t Rdm = getBits(instruction,18,16);
  uint32_t d = (DN << 3) | Rdm;

  if(inITBlock())
  {
    if( checkCondition(cond) )
      executeADDSPRegister(d, d, 0, -1);
    //here no need to shift IT State because it will be shifted when return back to its caller which is ADDRegister function
  }
  else
    executeADDSPRegister(d, d, 0, -1);
  
}



/*Add SP with Register Encoding T2
    ADD<c> SP,<Rm>
      
  31 30 29 28 27 26 25 24 23 22 21 20 19 18 17 16 15 14 13 12 11 10 9 8 7 6 5 4 3 2 1 0
  |0   1  0  0  0  1| 0  0|1|     Rm    | 1  0  1|                unused               |

  setflags = FALSE
  
where:
              S                 If present, specifies that the instruction updates the flags. Otherwise, the instruction does not
                                update the flags.
                                
              <c><q>            See Standard assembler syntax fields on page A6-7.
              
              <Rd>              Specifies the destination register. If <Rd> is omitted, this register is SP.
                                The use of the PC as <Rd> in encoding T1 is deprecated.
                                
              <Rm>              Specifies the register that is optionally shifted and used as the second operand.
                                The use of the SP as <Rm> in encoding T1 is deprecated.
                                The use of the PC as <Rm> in encoding T1 and encoding T2 is deprecated.
                                
              <shift>           Specifies the shift to apply to the value read from <Rm>. If <shift> is omitted, no shift is
                                applied and all encodings are permitted. If <shift> is specified, only encoding T3 is
                                permitted. The possible shifts and how they are encoded are described in Shifts applied to a
                                register on page A6-12.
                                
              If <Rd> is SP or omitted, <shift> is only permitted to be LSL #0, LSL #1, LSL #2 or LSL #3.
                      
              Inside an IT block, if ADD<c> <Rd>,<Rn>,<Rd> cannot be assembled using encoding T1, it is assembled using
              encoding T2 as though ADD<c> <Rd>,<Rn> had been written. To prevent this happening, use the .W qualifier.
*/
void ADDSPRegisterT2(uint32_t instruction)
{
  uint32_t Rm = getBits(instruction,22,19);
  uint32_t Rd = 0b1101;

  if(inITBlock())
  {
    if( checkCondition(cond) )
      executeADDSPRegister(Rd, Rm, 0, -1);
    //here no need to shift IT State because it will be shifted when return back to its caller which is ADDRegister function  
  }
  else
    executeADDSPRegister(Rd, Rm, 0, -1);
}




void executeADDSPRegister(uint32_t Rd, uint32_t Rm, uint32_t S, int shiftOrNoShift)
{
  if( shiftOrNoShift == -1)     //if no shifting no need to add with carry flag
  {
    if(Rd == PC)
    {
      uint32_t address = coreReg[Rm] + coreReg[SP] + 4;
      coreReg[PC] = maskOffBit(address, 0);
    }
    else if(Rm == PC)
    {
      coreReg[Rd] = alignPC(coreReg[Rm] + 2, 4) + coreReg[SP];
    }
    else
    {
      coreReg[Rd] = coreReg[Rm] + coreReg[SP];
    }
  }

}


