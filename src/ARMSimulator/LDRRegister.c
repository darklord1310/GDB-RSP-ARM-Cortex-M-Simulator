/*  
    Program Name       : GDB RSP and ARM Simulator
    Author             : Wong Yan Yin, Jackson Teh Ka Sing 
    Copyright (C) 2015 TARUC

    This file is part of GDB RSP and ARM Simulator.

    GDB RSP and ARM Simulator is free software, you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    GDB RSP and ARM Simulator is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY, without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with GDB RSP and ARM Simulator.  If not, see <http://www.gnu.org/licenses/>.

*/



#include "LDRRegister.h"
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
#include "LoadAndWriteMemory.h"
#include "ShiftOperation.h"
#include "STRRegister.h"

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
      coreReg[Rt] = loadByteFromMemory(address, 4);                        //load a word from the address and store it into the register 
    }
    
    shiftITState();
  }
  else
  {
    uint32_t address = coreReg[Rn] + coreReg[Rm];                    
    coreReg[Rt] = loadByteFromMemory(address, 4);                        //load a word from the address and store it into the register 
  }
  
  coreReg[PC] += 2;
}




/*Load Register (register) Encoding T2
 * 
    LDR<c>.W <Rt>,[<Rn>,<Rm>{,LSL #<imm2>}]
      
   31 30 29 28 27 26 25 24 23 22 21 20 19 18 17 16 15 14 13 12 11 10 9 8 7 6 5 4  3 2 1 0
  | 1  1  1  1  1| 0  0| 0  0|1   0| 1|     Rn    |      Rt   |0|  0 0 0 0 0|imm2|  Rm   |  

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
void LDRRegisterT2(uint32_t instruction)
{
  uint32_t temp;
  uint32_t Rm   = getBits(instruction,3,0);  
  uint32_t imm2   = getBits(instruction,5,4);
  uint32_t Rt   = getBits(instruction,15,12);
  uint32_t Rn   = getBits(instruction,19,16);  
  
  temp = executeShiftOperation(LSL, imm2, coreReg[Rm], 0);            //no update carry flag
  uint32_t address = coreReg[Rn] +  temp;
      
  if(inITBlock())
  {
    if( checkCondition(cond) )
    {
      if(Rt == PC)
      {
        if( getBits(address,1,0) == 0b00)
          coreReg[Rt] = loadByteFromMemory(address, 4);
        else
        {
          placePCtoVectorTable(UsageFault);
          Throw(UsageFault);
        }
      }
      else
        coreReg[Rt] = loadByteFromMemory(address, 4);                        
    }
    shiftITState();
  }
  else
  {
    if(Rt == PC)
    {
      if( getBits(address,1,0) == 0b00)
        coreReg[Rt] = loadByteFromMemory(address, 4);
      else
      {
        placePCtoVectorTable(UsageFault);
        Throw(UsageFault);
      }
    }
    else
      coreReg[Rt] = loadByteFromMemory(address, 4);                       
  }
  
  if(Rt != PC)
    coreReg[PC] += 4;
}




/*Load Register Unpriviledged Encoding T1
 * 
    LDRT<c> <Rt>,[<Rn>,#<imm8>]
      
   31 30 29 28 27 26 25 24 23 22 21 20 19 18 17 16 15 14 13 12 11 10 9 8 7 6 5 4 3 2 1 0
  | 1  1  1  1  1| 0  0| 0  0|1   0| 1|     Rn    |      Rt   |1|  1 1 0|      imm8     |  

  where:
            <c><q>          See Standard assembler syntax fields on page A6-7.
            
            <Rt>            Specifies the destination register.
            
            <Rn>            Specifies the base register. This register is allowed to be the SP.
            
            <imm>           Specifies the immediate offset added to the value of <Rn> to form the address. The range of
                            allowed values is 0-255. <imm> can be omitted, meaning an offset of 0.
          
*/
void LDRTT1(uint32_t instruction)
{
  uint32_t imm8 = getBits(instruction,7,0);
  uint32_t Rt   = getBits(instruction,15,12);
  uint32_t Rn   = getBits(instruction,19,16);  
  
  if(Rt == PC || Rt == SP)
    Throw(UsageFault);
  
  uint32_t address = coreReg[Rn] +  imm8;
  
  if(inITBlock())
  {
    if( checkCondition(cond) )
        coreReg[Rt] = loadByteFromMemory(address, 4);
      
    shiftITState();
  }
  else
    coreReg[Rt] = loadByteFromMemory(address, 4);                       
  
  coreReg[PC] += 4;
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
      coreReg[Rt] = loadByteFromMemory(address, 2);
    }
    
    shiftITState();
  }
  else
  {
    uint32_t address = coreReg[Rn] + coreReg[Rm];                    
    coreReg[Rt] = loadByteFromMemory(address, 2);
  }  
  
  coreReg[PC] += 2;
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
      coreReg[Rt] = loadByteFromMemory(address, 1);
    }
    
    shiftITState();
  }
  else
  {
    uint32_t address = coreReg[Rn] + coreReg[Rm];                    
    coreReg[Rt] = loadByteFromMemory(address, 1);
  }  
 
  coreReg[PC] += 2; 
}



/*Load Register Byte (register) Encoding T2
 * 
    LDRB<c>.W <Rt>,[<Rn>,<Rm>{,LSL #<imm2>}]
      
   31 30 29 28 27 26 25 24 23 22 21 20 19 18 17 16 15 14 13 12 11 10 9 8 7 6 5  4 3 2 1 0
  | 1  1  1  1  1| 0  0| 0  0  0  0  1|     Rn    |     Rt    | 0| 0 0 0 0 0|imm2|  Rm   |

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
void LDRBRegisterT2(uint32_t instruction)
{
  uint32_t Rm = getBits(instruction,3,0);
  uint32_t imm2 = getBits(instruction,5,4);
  uint32_t Rt = getBits(instruction,15,12);
  uint32_t Rn = getBits(instruction,19,16);
  uint32_t address = coreReg[Rn] +  executeShiftOperation(LSL, imm2, coreReg[Rm], 0);
  
  if(inITBlock())
  {
    if( checkCondition(cond) )
      coreReg[Rt] = loadByteFromMemory(address, 1);
    
    shiftITState();
  }
  else
    coreReg[Rt] = loadByteFromMemory(address, 1); 

  coreReg[PC] += 4;
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
      uint32_t data =  loadByteFromMemory(address, 1);
      data = signExtend(data, 8);
      
      coreReg[Rt] = data;
    }
    
    shiftITState();
  }
  else
  {
    uint32_t address = coreReg[Rn] + coreReg[Rm];                    
    uint32_t data =  loadByteFromMemory(address, 1);
    data = signExtend(data, 8);
  
    coreReg[Rt] = data;
  }  
  
  coreReg[PC] += 2;
}



/*Load Register Signed Byte (register) Encoding T2
 * 
    LDRSB<c>.W <Rt>,[<Rn>,<Rm>{,LSL #<imm2>}]
      
   31 30 29 28 27 26 25 24 23 22 21 20 19 18 17 16 15 14 13 12 11 10 9 8 7 6 5  4 3 2 1 0
  | 1  1  1  1  1| 0  0| 1| 0  0  0  1|     Rn    |     Rt    |0 | 0 0 0 0 0|imm2|   Rm  |

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
void LDRSBRegisterT2(uint32_t instruction)
{
  uint32_t Rm   = getBits(instruction,3,0);  
  uint32_t imm2   = getBits(instruction,5,4);
  uint32_t Rt   = getBits(instruction,15,12);
  uint32_t Rn   = getBits(instruction,19,16);  
  uint32_t address = coreReg[Rn] +  executeShiftOperation(LSL, imm2, coreReg[Rm], 0);
      
  if(inITBlock())
  {
    if( checkCondition(cond) )
      coreReg[Rt] = signExtend( loadByteFromMemory(address, 1), 8);                        
    
    shiftITState();
  }
  else
    coreReg[Rt] = signExtend( loadByteFromMemory(address, 1), 8);                       

  coreReg[PC] += 4;
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
      uint32_t data =  loadByteFromMemory(address, 2);
      data = signExtend(data, 16);
      
      coreReg[Rt] = data;
    }
    
    shiftITState();
  }
  else
  {
    uint32_t address = coreReg[Rn] + coreReg[Rm];                    
    uint32_t data =  loadByteFromMemory(address, 2);
    data = signExtend(data, 16);
    
    coreReg[Rt] = data;
  }    
  
  coreReg[PC] += 2;
}



/*Load Multiple Increment After Encoding T1 
 * 
  LDM<c> <Rn>!,<registers> <Rn> not included in <registers>
  LDM<c> <Rn>,<registers> <Rn> included in <registers>
      
   31 30 29 28 27 26 25 24 23 22 21 20 19 18 17 16 15 14 13 12 11 10 9 8 7 6 5 4 3 2 1 0
  |1  1  0   0| 1|   Rn   |       register_list   |                 unused              |

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
  uint32_t Rn = getBits(instruction, 26,24);
  uint32_t registerList = getBits(instruction, 23,16);  
  
  if(inITBlock())
  {
    if( checkCondition(cond) )
    {
      int writeBack = determineWriteBack(Rn, registerList,1);
      loadMultipleRegisterFromMemory(coreReg[Rn], registerList, writeBack, Rn, 8);
    }
    shiftITState();
  }
  else
  {
    int writeBack = determineWriteBack( Rn, registerList,1);              
    loadMultipleRegisterFromMemory(coreReg[Rn], registerList, writeBack, Rn, 8);
  }  

  coreReg[PC] += 2;
}





/*Load Multiple Increment After Encoding T2
 * 
    LDM<c>.W <Rn>{!},<registers>
      
   31 30 29 28 27 26 25 24 23 22 21 20 19 18 17 16 15 14 13 12 11 10 9 8 7 6 5 4 3 2 1 0
  |1  1   1  0  1| 0  0| 0  1  0|W | 1|      Rn   |P | M| 0|       register_list        |      

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
void LDMRegisterT2(uint32_t instruction)
{
  uint32_t Rn = getBits(instruction, 19,16);
  uint32_t registerList = getBits(instruction, 12,0);
  uint32_t W = getBits(instruction, 21,21);
  uint32_t P = getBits(instruction, 15,15);
  uint32_t M = getBits(instruction, 14,14);
  registerList = ( ( ( (P << 1) | M) << 1) << 13) | registerList; 

  if(inITBlock())
  {
    if( checkCondition(cond) )
    {
      int writeBack = determineWriteBack(Rn, registerList,W);
      loadMultipleRegisterFromMemory(coreReg[Rn], registerList, writeBack, Rn, 16);
    }
    shiftITState();
  }
  else
  {
    int writeBack = determineWriteBack( Rn, registerList,W);  
    loadMultipleRegisterFromMemory(coreReg[Rn], registerList, writeBack, Rn, 16);
  }  

  if(P != 1)
    coreReg[PC] += 4;
  
}




/*Load Multiple Decrement Before
 * 
    LDMDB<c> <Rn>{!},<registers>
      
   31 30 29 28 27 26 25 24 23 22 21 20 19 18 17 16 15 14 13 12 11 10 9 8 7 6 5 4 3 2 1 0
  |1  1   1  0  1| 0  0| 1  0  0|W | 1|      Rn   |P | M| 0|       register_list        |      

  where:
            <c><q>          See Standard assembler syntax fields on page A6-7.
            
            <Rn>            The base register. The SP can be used.
            
            !               Causes the instruction to write a modified value back to <Rn>. Encoded as W = 1.
                            If ! is omitted, the instruction does not change <Rn> in this way. Encoded as W = 0.
                            
            <registers>     Is a list of one or more registers, separated by commas and surrounded by { and }. It specifies
                            the set of registers to be loaded. The registers are loaded with the lowest-numbered register
                            from the lowest memory address, through to the highest-numbered register from the highest
                            memory address. If the PC is specified in the register list, the instruction causes a branch to
                            the address (data) loaded into the PC.
                            
            Encoding T1 does not support a list containing only one register. If an LDMDB instruction with
            just one register <Rt> in the list is assembled to Thumb, it is assembled to the equivalent
            LDR<c><q> <Rt>,[<Rn>,#-4]{!} instruction.
            The SP cannot be in the list.
            If the PC is in the list, the LR must not be in the list and the instruction must either be outside
            an IT block or the last instruction in an IT block.
          
*/
void LDMDB(uint32_t instruction)
{
  uint32_t Rn = getBits(instruction, 19,16);
  uint32_t registerList = getBits(instruction, 12,0);
  uint32_t W = getBits(instruction, 21,21);
  uint32_t P = getBits(instruction, 15,15);
  uint32_t M = getBits(instruction, 14,14);
  registerList = ( ( ( (P << 1) | M) << 1) << 13) | registerList; 
  uint32_t address = coreReg[Rn] - 4*getBitCount(registerList, 16);
  if(inITBlock())
  {
    if( checkCondition(cond) )
    {
      int writeBack = determineWriteBack(Rn, registerList, W);
      loadMultipleRegisterFromMemory(address, registerList, 0, Rn, 16);
      if(writeBack == 1)
        coreReg[Rn] = coreReg[Rn] - 4*getBitCount(registerList, 16);
    }
    shiftITState();
  }
  else
  {
    int writeBack = determineWriteBack( Rn, registerList, W);              
    loadMultipleRegisterFromMemory(address, registerList, 0, Rn, 16);
    if(writeBack == 1)
      coreReg[Rn] = coreReg[Rn] - 4*getBitCount(registerList, 16);
  }  

  if(P != 1)
    coreReg[PC] += 4;
}




/* This function will load multiple register from memory based to the register list given
 * 
 * Input:  address              the base address of the memory
 *         registerList         the number of register which the value will be read and load into registers
 *         writeBack            if 1 then means writeback is true, 0 means false
 *         Rn                   the destination register which the value will be updated if writeback is 1
 *         sizeOfRegisterList   the size of register list/ number of bits of registerList  
 */
void loadMultipleRegisterFromMemory(uint32_t address, uint32_t registerList, uint32_t writeBack, uint32_t Rn, int sizeOfRegisterList)
{
  int i, bitCount = 0;
  
  for(i = 0; i < sizeOfRegisterList; i++)
  {
    if( getBits(registerList, i ,i) == 1)           //if the bit[i] of the registerList is 1, then load the value of the address into r[i]
    {
      if(i != PC)
        coreReg[i] = loadByteFromMemory(address, 4);
      else
        coreReg[i] = maskOffBit( loadByteFromMemory(address, 4), 0);
      bitCount++;
      address+=4;
    }
  }
  
  if(writeBack == 1)                                //if writeback is 1 then update the Rn register
  {
    coreReg[Rn] = coreReg[Rn] + 4*bitCount;
  }
  
}


int determineWriteBack(uint32_t Rn, uint32_t registerList, uint32_t W)
{
  if( W == 1 && getBits(registerList, Rn, Rn) == 0)    //if Rn is not included , then writeBack is 1, else writeBack is 0
    return 1;
  else 
    return 0;
  
}