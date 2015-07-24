#include "LDRImmediate.h"
#include "ITandHints.h"
#include "StatusRegisters.h"
#include "ARMRegisters.h"
#include "getAndSetBits.h"
#include "getMask.h"
#include "ModifiedImmediateConstant.h"
#include "Thumb16bitsTable.h"
#include "ConditionalExecution.h"
#include "MemoryBlock.h"


/*Load Register(Immediate) Encoding T1 
 * 
    LDR<c> <Rt>, [<Rn>{,#<imm5>}]
      
   31 30 29 28 27 26 25 24 23 22 21 20 19 18 17 16 15 14 13 12 11 10 9 8 7 6 5 4 3 2 1 0
  |0  1  1   0  1|      imm5    |    Rn  |   Rt   |                unused               |

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
void LDRImmediateT1(uint32_t instruction)
{
  uint32_t imm5 = getBits(instruction,26,22);  
  uint32_t Rn   = getBits(instruction,21,19);  
  uint32_t Rt   = getBits(instruction,18,16);  
  printf("Rn: %x\n", Rn);
  printf("Rt: %x\n", Rt);
  printf("imm5: %x\n", imm5);
  //uint32_t address = coreReg[Rn] + imm5;
  //uint32_t wordLoaded = loadWordFromMemory(address);
  //coreReg[Rt] = wordLoaded;
  
}


uint32_t loadWordFromMemory(uint32_t address)
{
  uint32_t upper16bits = ( memoryBlock[ virtualMemToPhysicalMem(address+3) ] << 8 ) | memoryBlock[ virtualMemToPhysicalMem(address+2) ];
  uint32_t lower16bits = ( memoryBlock[ virtualMemToPhysicalMem(address+1) ] << 8 ) | memoryBlock[ virtualMemToPhysicalMem(address) ];
  
  return (  (upper16bits << 16) | lower16bits );
  
}