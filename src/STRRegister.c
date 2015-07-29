#include "STRRegister.h"
#include "STRImmediate.h"
#include "ITandHints.h"
#include "StatusRegisters.h"
#include "ARMRegisters.h"
#include "getAndSetBits.h"
#include "getMask.h"
#include "ModifiedImmediateConstant.h"
#include "Thumb16bitsTable.h"
#include "ConditionalExecution.h"
#include "MemoryBlock.h"
#include "ErrorSignal.h"



/*Store Register (register) Encoding T1
 * 
    STR<c> <Rt>,[<Rn>,<Rm>]
      
   31 30 29 28 27 26 25 24 23 22 21 20 19 18 17 16 15 14 13 12 11 10 9 8 7 6 5 4 3 2 1 0
  |0  1  0   1| 0  0  0|    Rm  |    Rn  |   Rt   |                unused               |

  where:
            <c><q>            See Standard assembler syntax fields on page A6-7.
            
            <Rt>              Specifies the source register. This register is allowed to be the SP.
            
            <Rn>              Specifies the register that contains the base value. This register is allowed to be the SP.
            
            <Rm>              Contains the offset that is shifted left and added to the value of <Rn> to form the address.
                              <shift> Specifies the number of bits the value from <Rm> is shifted left, in the range 0-3. If this option
                              is omitted, a shift by 0 is assumed and both encodings are permitted. If this option is
                              specified, only encoding T2 is permitted.
          
*/
void STRRegisterT1(uint32_t instruction)
{
  uint32_t Rm = getBits(instruction,24,22);
  uint32_t Rn = getBits(instruction,21,19);
  uint32_t Rt = getBits(instruction,18,16);
  
  if(inITBlock())
  {
    if( checkCondition(cond) )
    {
      uint32_t address = coreReg[Rn] + coreReg[Rm];                    
      writeByteToMemory(address, coreReg[Rt],4);               //store a word to the address and store it into the memory
    }
    shiftITState();
  }
  else
  {
    uint32_t address = coreReg[Rn] + coreReg[Rm];                    
    writeByteToMemory(address, coreReg[Rt],4);               //store a word to the address and store it into the memory
  }
}





/*Store Register (register) Encoding T1
 * 
    STR<c> <Rt>,[<Rn>,<Rm>]
      
   31 30 29 28 27 26 25 24 23 22 21 20 19 18 17 16 15 14 13 12 11 10 9 8 7 6 5 4 3 2 1 0
  |0  1  0   1| 0  0  1|    Rm  |    Rn  |   Rt   |                unused               |

  where:
            <c><q>            See Standard assembler syntax fields on page A6-7.
            
            <Rt>              Specifies the source register. This register is allowed to be the SP.
            
            <Rn>              Specifies the register that contains the base value. This register is allowed to be the SP.
            
            <Rm>              Contains the offset that is shifted left and added to the value of <Rn> to form the address.
                              <shift> Specifies the number of bits the value from <Rm> is shifted left, in the range 0-3. If this option
                              is omitted, a shift by 0 is assumed and both encodings are permitted. If this option is
                              specified, only encoding T2 is permitted.
          
*/
void STRHRegisterT1(uint32_t instruction)
{
  uint32_t Rm = getBits(instruction,24,22);
  uint32_t Rn = getBits(instruction,21,19);
  uint32_t Rt = getBits(instruction,18,16);
  
  if(inITBlock())
  {
    if( checkCondition(cond) )
    {
      uint32_t address = coreReg[Rn] + coreReg[Rm];                    
      writeByteToMemory(address, coreReg[Rt],2);               //store half word to the address and store it into the memory
    }
    shiftITState();
  }
  else
  {
    uint32_t address = coreReg[Rn] + coreReg[Rm];                    
    writeByteToMemory(address, coreReg[Rt],2);               //store half word to the address and store it into the memory
  }
}




/*Store Register Byte (register) Encoding T1
 * 
    STRB<c> <Rt>,[<Rn>,<Rm>]
      
   31 30 29 28 27 26 25 24 23 22 21 20 19 18 17 16 15 14 13 12 11 10 9 8 7 6 5 4 3 2 1 0
  |0  1  0   1| 0  0  1|    Rm  |    Rn  |   Rt   |                unused               |

  where:
            <c><q>            See Standard assembler syntax fields on page A6-7.
            
            <Rt>              Specifies the source register. This register is allowed to be the SP.
            
            <Rn>              Specifies the register that contains the base value. This register is allowed to be the SP.
            
            <Rm>              Contains the offset that is shifted left and added to the value of <Rn> to form the address.
                              <shift> Specifies the number of bits the value from <Rm> is shifted left, in the range 0-3. If this option
                              is omitted, a shift by 0 is assumed and both encodings are permitted. If this option is
                              specified, only encoding T2 is permitted.
          
*/
void STRBRegisterT1(uint32_t instruction)
{
  uint32_t Rm = getBits(instruction,24,22);
  uint32_t Rn = getBits(instruction,21,19);
  uint32_t Rt = getBits(instruction,18,16);
  
  if(inITBlock())
  {
    if( checkCondition(cond) )
    {
      uint32_t address = coreReg[Rn] + coreReg[Rm];                    
      writeByteToMemory(address, coreReg[Rt],1);               //store a byte to the address and store it into the memory
    }
    shiftITState();
  }
  else
  {
    uint32_t address = coreReg[Rn] + coreReg[Rm];                    
    writeByteToMemory(address, coreReg[Rt],1);               //store a byte to the address and store it into the memory
  }
}