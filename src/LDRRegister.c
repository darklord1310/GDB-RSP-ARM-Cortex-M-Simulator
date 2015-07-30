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



/*Load Multiple Increment After Encoding T1 
 * 
  LDM<c> <Rn>!,<registers> <Rn> not included in <registers>
  LDM<c> <Rn>,<registers> <Rn> included in <registers>
      
   31 30 29 28 27 26 25 24 23 22 21 20 19 18 17 16 15 14 13 12 11 10 9 8 7 6 5 4 3 2 1 0
  |1  1  0   0| 1|   Rn   |    register_list   |                 unused                |

  where:
            <c><q>          See Standard assembler syntax fields on page A6-7.
            
            <Rn>            The base register. If it is the SP and ! is specified, the instruction is treated as
                            described in POP on page A6-186.
                            
            !               Causes the instruction to write a modified value back to <Rn>. If ! is omitted, the
                            instruction does not change <Rn> in this way.
                            
            <registers>     Is a list of one or more registers to be loaded, separated by commas and surrounded
                            by { and }. The lowest-numbered register is loaded from the lowest memory
                            address, through to the highest-numbered register from the highest memory address.
                            If the PC is specified in the register list, the instruction causes a branch to the
                            address (data) loaded into the PC.
                            Encoding T2 does not support a list containing only one register. If an LDMIA
                            instruction with just one register <Rt> in the list is assembled to Thumb and encoding
                            T1 is not available, it is assembled to the equivalent LDR<c><q> <Rt>,[<Rn>]{,#4}
                            instruction.
                            The SP cannot be in the list.
                            If the PC is in the list, the LR must not be in the list and the instruction must either
                            be outside an IT block or the last instruction in an IT block.
                            
            LDMIA and LDMFD are pseudo-instructions for LDM. LDMFD refers to its use for popping data from Full
            Descending stacks.
          
*/
void LDMRegisterT1(uint32_t instruction)
{
    
  
}