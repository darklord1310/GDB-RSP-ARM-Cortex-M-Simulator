#include "LDRLiteral.h"
#include "ITandHints.h"
#include "StatusRegisters.h"
#include "ARMRegisters.h"
#include "getAndSetBits.h"
#include "getMask.h"
#include "ModifiedImmediateConstant.h"
#include "Thumb16bitsTable.h"
#include "ConditionalExecution.h"
#include "ROM.h"
#include <stdio.h>
#include "LDRImmediate.h"


/*Load Register(literal) Encoding T1 
 * 
    LDR<c> <Rt>,<label>
      
   31 30 29 28 27 26 25 24 23 22 21 20 19 18 17 16 15 14 13 12 11 10 9 8 7 6 5 4 3 2 1 0
  |0  1   0  0  1|   Rt   |          imm8         |               unused               |

  where:
              <c><q>            See Standard assembler syntax fields on page A6-7.
              
              <Rt>              Specifies the destination register. This register is allowed to be the SP. It is also allowed to
                                be the PC, provided the instruction is either outside an IT block or the last instruction of an
                                IT block. If it is the PC, it causes a branch to the address (data) loaded into the PC.
                                
              <Rn>              Specifies the base register. This register is allowed to be the SP. If this register is the PC, see
                                LDR (literal) on page A6-90.
                                
              +/-               Is + or omitted to indicate that the immediate offset is added to the base register value
                                (add == TRUE), or – to indicate that the offset is to be subtracted (add == FALSE). Different
                                instructions are generated for #0 and #-0.
                                
              <imm>             Specifies the immediate offset added to or subtracted from the value of <Rn> to form the
                                address. Allowed values are multiples of 4 in the range 0-124 for encoding T1, multiples of
                                4 in the range 0-1020 for encoding T2, any value in the range 0-4095 for encoding T3, and
                                any value in the range 0-255 for encoding T4. For the offset addressing syntax, <imm> can be
                                omitted, meaning an offset of 0.
          
*/
void LDRLiteralT1(uint32_t instruction)
{
  uint32_t imm8 = getBits(instruction,23,16);  
  uint32_t Rt   = getBits(instruction,26,24);  
  printf("Rt: %x\n", Rt);
  printf("imm8: %x\n", imm8);
  
  uint32_t address = coreReg[PC] + imm8;
  printf("address: %x\n", address);
  uint32_t wordLoaded = loadWordFromMemory(address);
  coreReg[Rt] = wordLoaded;
  
}