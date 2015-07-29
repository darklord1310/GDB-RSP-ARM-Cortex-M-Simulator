#include "LDRRegister.h"
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
#include "ErrorSignal.h"



/*Load Register (register) Encoding T1 
 * 
    LDR<c> <Rt>,[<Rn>,<Rm>]
      
   31 30 29 28 27 26 25 24 23 22 21 20 19 18 17 16 15 14 13 12 11 10 9 8 7 6 5 4 3 2 1 0
  |0  1  0   1| 1  0  0|    Rm  |    Rn  |   Rt   |               unused               |

  where:
            <c><q>          See Standard assembler syntax fields on page A6-7.
            
            <Rt>            Specifies the destination register. This register is allowed to be the SP. It is also allowed to
                            be the PC, provided the instruction is either outside an IT block or the last instruction of an
                            IT block. If it is the PC, it causes a branch to the address (data) loaded into the PC.
                            
            <Rn>            Specifies the register that contains the base value. This register is allowed to be the SP.
            
            <Rm>            Contains the offset that is shifted left and added to the value of <Rn> to form the address.
            
            <shift>         Specifies the number of bits the value from <Rm> is shifted left, in the range 0-3. If this option
                            is omitted, a shift by 0 is assumed and both encodings are permitted. If this option is
                            specified, only encoding T2 is permitted.
          
*/
void LDRRegisterT1(uint32_t instruction)
{
  uint32_t Rm = getBits(instruction,24,22);  
  uint32_t Rn   = getBits(instruction,21,19);  
  uint32_t Rt   = getBits(instruction,18,16);  
  
  if(inITBlock())
  {
    if( checkCondition(cond) )
    {
      uint32_t address = coreReg[Rn] +  coreReg[Rm];                    
      coreReg[Rt] = executeLDR(address);                        //load a word from the address and store it into the register 
    }
    
    shiftITState();
  }
  else
  {
    uint32_t address = coreReg[Rn] + coreReg[Rm];                    
    coreReg[Rt] = executeLDR(address);                        //load a word from the address and store it into the register 
  }
  
}





/*Load Register Halfword (register) Encoding T1 
 * 
    LDRH<c> <Rt>,[<Rn>,<Rm>]
      
   31 30 29 28 27 26 25 24 23 22 21 20 19 18 17 16 15 14 13 12 11 10 9 8 7 6 5 4 3 2 1 0
  |0  1  0   1| 1  0  1|    Rm  |    Rn  |   Rt   |               unused               |

  where:
            <c><q>          See Standard assembler syntax fields on page A6-7.
            
            <Rt>            Specifies the destination register. This register is allowed to be the SP. It is also allowed to
                            be the PC, provided the instruction is either outside an IT block or the last instruction of an
                            IT block. If it is the PC, it causes a branch to the address (data) loaded into the PC.
                            
            <Rn>            Specifies the register that contains the base value. This register is allowed to be the SP.
            
            <Rm>            Contains the offset that is shifted left and added to the value of <Rn> to form the address.
            
            <shift>         Specifies the number of bits the value from <Rm> is shifted left, in the range 0-3. If this option
                            is omitted, a shift by 0 is assumed and both encodings are permitted. If this option is
                            specified, only encoding T2 is permitted.
          
*/
void LDRHRegisterT1(uint32_t instruction)
{
  uint32_t Rm = getBits(instruction,24,22);  
  uint32_t Rn   = getBits(instruction,21,19);  
  uint32_t Rt   = getBits(instruction,18,16);  
  
  if(inITBlock())
  {
    if( checkCondition(cond) )
    {
      uint32_t address = coreReg[Rn] +  coreReg[Rm];                    
      uint32_t data = (memoryBlock[virtualMemToPhysicalMem(address+1)] << 8) | memoryBlock[virtualMemToPhysicalMem(address)];
      coreReg[Rt] = data;
    }
    
    shiftITState();
  }
  else
  {
    uint32_t address = coreReg[Rn] + coreReg[Rm];                    
    uint32_t data = (memoryBlock[virtualMemToPhysicalMem(address+1)] << 8) | memoryBlock[virtualMemToPhysicalMem(address)];
    coreReg[Rt] = data;
  }  
  
}




/*Load Register Byte (register) Encoding T1 
 * 
    LDRB<c> <Rt>,[<Rn>,<Rm>]
      
   31 30 29 28 27 26 25 24 23 22 21 20 19 18 17 16 15 14 13 12 11 10 9 8 7 6 5 4 3 2 1 0
  |0  1  0   1| 1  0  1|    Rm  |    Rn  |   Rt   |               unused               |

  where:
            <c><q>          See Standard assembler syntax fields on page A6-7.
            
            <Rt>            Specifies the destination register. This register is allowed to be the SP. It is also allowed to
                            be the PC, provided the instruction is either outside an IT block or the last instruction of an
                            IT block. If it is the PC, it causes a branch to the address (data) loaded into the PC.
                            
            <Rn>            Specifies the register that contains the base value. This register is allowed to be the SP.
            
            <Rm>            Contains the offset that is shifted left and added to the value of <Rn> to form the address.
            
            <shift>         Specifies the number of bits the value from <Rm> is shifted left, in the range 0-3. If this option
                            is omitted, a shift by 0 is assumed and both encodings are permitted. If this option is
                            specified, only encoding T2 is permitted.
          
*/
void LDRBRegisterT1(uint32_t instruction)
{
  uint32_t Rm = getBits(instruction,24,22);  
  uint32_t Rn   = getBits(instruction,21,19);  
  uint32_t Rt   = getBits(instruction,18,16);  
  
  if(inITBlock())
  {
    if( checkCondition(cond) )
    {
      uint32_t address = coreReg[Rn] +  coreReg[Rm];                    
      uint32_t data =  memoryBlock[virtualMemToPhysicalMem(address)];
      coreReg[Rt] = data;
    }
    
    shiftITState();
  }
  else
  {
    uint32_t address = coreReg[Rn] + coreReg[Rm];                    
    uint32_t data =  memoryBlock[virtualMemToPhysicalMem(address)];
    coreReg[Rt] = data;
  }  
  
}




/*Load Register Signed Byte (register) Encoding T1 
 * 
    LDRSB<c> <Rt>,[<Rn>,<Rm>]
      
   31 30 29 28 27 26 25 24 23 22 21 20 19 18 17 16 15 14 13 12 11 10 9 8 7 6 5 4 3 2 1 0
  |0  1  0   1| 0  1  1|    Rm  |    Rn  |   Rt   |               unused               |

  where:
            <c><q>          See Standard assembler syntax fields on page A6-7.
            
            <Rt>            Specifies the destination register. This register is allowed to be the SP. It is also allowed to
                            be the PC, provided the instruction is either outside an IT block or the last instruction of an
                            IT block. If it is the PC, it causes a branch to the address (data) loaded into the PC.
                            
            <Rn>            Specifies the register that contains the base value. This register is allowed to be the SP.
            
            <Rm>            Contains the offset that is shifted left and added to the value of <Rn> to form the address.
            
            <shift>         Specifies the number of bits the value from <Rm> is shifted left, in the range 0-3. If this option
                            is omitted, a shift by 0 is assumed and both encodings are permitted. If this option is
                            specified, only encoding T2 is permitted.
          
*/
void LDRSBRegisterT1(uint32_t instruction)
{
  uint32_t Rm = getBits(instruction,24,22);  
  uint32_t Rn   = getBits(instruction,21,19);  
  uint32_t Rt   = getBits(instruction,18,16);  

  if(inITBlock())
  {
    if( checkCondition(cond) )
    {
      uint32_t address = coreReg[Rn] +  coreReg[Rm];                    
      uint32_t data =  memoryBlock[virtualMemToPhysicalMem(address)];
      
      if( getBits(data, 7,7) == 1)
        data = setBits(data,0b111111111111111111111111,31,8);
      
      coreReg[Rt] = data;
    }
    
    shiftITState();
  }
  else
  {
    uint32_t address = coreReg[Rn] + coreReg[Rm];                    
    uint32_t data =  memoryBlock[virtualMemToPhysicalMem(address)];
    
    if( getBits(data, 7,7) == 1)
      data = setBits(data,0b111111111111111111111111,31,8);
  
    coreReg[Rt] = data;
  }  
  
}




/*Load Register Signed Halfword (register) Encoding T1 
 * 
    LDRSH<c> <Rt>,[<Rn>,<Rm>]
      
   31 30 29 28 27 26 25 24 23 22 21 20 19 18 17 16 15 14 13 12 11 10 9 8 7 6 5 4 3 2 1 0
  |0  1  0   1| 1  1  1|    Rm  |    Rn  |   Rt   |               unused               |

  where:
            <c><q>          See Standard assembler syntax fields on page A6-7.
            
            <Rt>            Specifies the destination register. This register is allowed to be the SP. It is also allowed to
                            be the PC, provided the instruction is either outside an IT block or the last instruction of an
                            IT block. If it is the PC, it causes a branch to the address (data) loaded into the PC.
                            
            <Rn>            Specifies the register that contains the base value. This register is allowed to be the SP.
            
            <Rm>            Contains the offset that is shifted left and added to the value of <Rn> to form the address.
            
            <shift>         Specifies the number of bits the value from <Rm> is shifted left, in the range 0-3. If this option
                            is omitted, a shift by 0 is assumed and both encodings are permitted. If this option is
                            specified, only encoding T2 is permitted.
          
*/
void LDRSHRegisterT1(uint32_t instruction)
{
  uint32_t Rm = getBits(instruction,24,22);  
  uint32_t Rn   = getBits(instruction,21,19);  
  uint32_t Rt   = getBits(instruction,18,16);  
  
  if(inITBlock())
  {
    if( checkCondition(cond) )
    {
      uint32_t address = coreReg[Rn] +  coreReg[Rm];                    
      uint32_t data =  (memoryBlock[virtualMemToPhysicalMem(address+1)] << 8) | memoryBlock[virtualMemToPhysicalMem(address)];
      
      if( getBits(data, 15,15) == 1)
      data = setBits(data,0b1111111111111111,31,16);
      
      coreReg[Rt] = data;
    }
    
    shiftITState();
  }
  else
  {
    uint32_t address = coreReg[Rn] + coreReg[Rm];                    
    uint32_t data =  (memoryBlock[virtualMemToPhysicalMem(address+1)] << 8) | memoryBlock[virtualMemToPhysicalMem(address)];
    
    if( getBits(data, 15,15) == 1)
      data = setBits(data,0b1111111111111111,31,16);
    
    coreReg[Rt] = data;
  }    
  
}