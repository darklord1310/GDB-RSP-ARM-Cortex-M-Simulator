#include "POP.h"
#include "LDRRegister.h"
#include "LDRImmediate.h"
#include "ITandHints.h"
#include "StatusRegisters.h"
#include "ARMRegisters.h"
#include "getAndSetBits.h"
#include "getMask.h"
#include "ModifiedImmediateConstant.h"
#include "ConditionalExecution.h"
#include "MemoryBlock.h"




/*Pop Multiple Registers Encoding T1
    PUSH<c> <registers>
      
  31 30 29 28 27 26 25 24 23 22 21 20 19 18 17 16 15 14 13 12 11 10 9 8 7 6 5 4 3 2 1 0
  |1  0  1  1| 1| 1  0|P|       register_list    |                unused               |
  
where:
          <c><q>            See Standard assembler syntax fields on page A6-7.
          
          <registers>       Is a list of one or more registers, separated by commas and surrounded by 
                            { and }. It specifies the set of registers to be stored. The registers
                            are stored in sequence, the lowest-numbered register to the lowest memory
                            address, through to the highest-numbered register to the highest memory address.
                            
          The SP cannot be in the list.
          If the PC is in the list, the LR must not be in the list.
                            
*/
void POPT1(uint32_t instruction)
{
  uint32_t P = getBits(instruction, 24, 24);
  uint32_t register_list = getBits(instruction, 23, 16);
  uint16_t temp = P << 7;
  uint16_t registerlist = ( temp << 8 ) | register_list;
  
  if(inITBlock())
  {
    if( checkCondition(cond) )
    {
      uint32_t address = coreReg[SP];     
      loadMultipleRegisterFromMemory(address, registerlist, 1, SP);
    }
    shiftITState();
    coreReg[PC] += 2;
  }
  else
  {
    uint32_t address = coreReg[SP];      
    loadMultipleRegisterFromMemory(address, registerlist, 1, SP);
    coreReg[PC] += 2;
  }
  
 
}