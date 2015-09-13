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
#include "ADR.h"
#include "LoadAndWriteMemory.h"



/*Store Register (immediate) Encoding T1
 * 
    STR<c> <Rt>, [<Rn>{,#<imm5>}]
      
   31 30 29 28 27 26 25 24 23 22 21 20 19 18 17 16 15 14 13 12 11 10 9 8 7 6 5 4 3 2 1 0
  |0  1  1   0  0|     imm5     |   Rn   |    Rt  |                unused               |

  where:
            <c><q>            See Standard assembler syntax fields on page A6-7.
            
            <Rt>              Specifies the source register. This register is allowed to be the SP.
            
            <Rn>              Specifies the base register. This register is allowed to be the SP.
            
            +/-               Is + or omitted to indicate that the immediate offset is added to the base register value
                              (add == TRUE), or – to indicate that the offset is to be subtracted (add == FALSE). Different
                              instructions are generated for #0 and #-0.
                              
            <imm>             Specifies the immediate offset added to or subtracted from the value of <Rn> to form the
                              address. Allowed values are multiples of 4 in the range 0-124 for encoding T1, multiples of
                              4 in the range 0-1020 for encoding T2, any value in the range 0-4095 for encoding T3, and
                              any value in the range 0-255 for encoding T4. For the offset addressing syntax, <imm> can be
                              omitted, meaning an offset of 0.
          
*/
void STRImmediateT1(uint32_t instruction)
{
  uint32_t imm5 = getBits(instruction, 26, 22);
  uint32_t Rn = getBits(instruction,21,19);
  uint32_t Rt = getBits(instruction,18,16);
  
  if(inITBlock())
  {
    if( checkCondition(cond) )
    {
      uint32_t address = coreReg[Rn] +  4*imm5;                    
      writeByteToMemory(address, coreReg[Rt],4);               //store a word to the address and store it into the memory
    }
    
    shiftITState();
  }
  else
  {
    uint32_t address = coreReg[Rn] + 4*imm5;                    
    writeByteToMemory(address, coreReg[Rt],4);               //store a word to the address and store it into the memory
  }
  
  
  coreReg[PC] += 2;
}




/*Store Register Byte (immediate) Encoding T1
 * 
    STRB<c> <Rt>,[<Rn>{,#<imm5>}]
      
   31 30 29 28 27 26 25 24 23 22 21 20 19 18 17 16 15 14 13 12 11 10 9 8 7 6 5 4 3 2 1 0
  |0  1  1   1  0|     imm5     |   Rn   |    Rt  |                unused               |

  where:
            <c><q>            See Standard assembler syntax fields on page A6-7.
            
            <Rt>              Specifies the source register. This register is allowed to be the SP.
            
            <Rn>              Specifies the base register. This register is allowed to be the SP.
            
            +/-               Is + or omitted to indicate that the immediate offset is added to the base register value
                              (add == TRUE), or – to indicate that the offset is to be subtracted (add == FALSE). Different
                              instructions are generated for #0 and #-0.
                              
            <imm>             Specifies the immediate offset added to or subtracted from the value of <Rn> to form the
                              address. Allowed values are multiples of 4 in the range 0-124 for encoding T1, multiples of
                              4 in the range 0-1020 for encoding T2, any value in the range 0-4095 for encoding T3, and
                              any value in the range 0-255 for encoding T4. For the offset addressing syntax, <imm> can be
                              omitted, meaning an offset of 0.
          
*/
void STRBImmediateT1(uint32_t instruction)
{
  uint32_t imm5 = getBits(instruction, 26, 22);
  uint32_t Rn = getBits(instruction,21,19);
  uint32_t Rt = getBits(instruction,18,16);
  
  if(inITBlock())
  {
    if( checkCondition(cond) )
    {
      uint32_t address = coreReg[Rn] +  imm5;                    
      writeByteToMemory(address, coreReg[Rt],1);               //store a byte to the address and store it into the memory
    }
    
    shiftITState();
  }
  else
  {
    uint32_t address = coreReg[Rn] + imm5;                    
    writeByteToMemory(address, coreReg[Rt],1);               //store a byte to the address and store it into the memory
  }
    
  coreReg[PC] += 2;
}



/*Store Register Halfword (immediate) Encoding T1
 * 
    STRH<c> <Rt>,[<Rn>{,#<imm5>}]
      
   31 30 29 28 27 26 25 24 23 22 21 20 19 18 17 16 15 14 13 12 11 10 9 8 7 6 5 4 3 2 1 0
  |1  0  0   0  0|     imm5     |   Rn   |    Rt  |                unused               |

  where:
            <c><q>            See Standard assembler syntax fields on page A6-7.
            
            <Rt>              Specifies the source register. This register is allowed to be the SP.
            
            <Rn>              Specifies the base register. This register is allowed to be the SP.
            
            +/-               Is + or omitted to indicate that the immediate offset is added to the base register value
                              (add == TRUE), or – to indicate that the offset is to be subtracted (add == FALSE). Different
                              instructions are generated for #0 and #-0.
                              
            <imm>             Specifies the immediate offset added to or subtracted from the value of <Rn> to form the
                              address. Allowed values are multiples of 4 in the range 0-124 for encoding T1, multiples of
                              4 in the range 0-1020 for encoding T2, any value in the range 0-4095 for encoding T3, and
                              any value in the range 0-255 for encoding T4. For the offset addressing syntax, <imm> can be
                              omitted, meaning an offset of 0.
          
*/
void STRHImmediateT1(uint32_t instruction)
{
  uint32_t imm5 = getBits(instruction, 26, 22);
  uint32_t Rn = getBits(instruction,21,19);
  uint32_t Rt = getBits(instruction,18,16);
  
  if(inITBlock())
  {
    if( checkCondition(cond) )
    {
      uint32_t address = coreReg[Rn] +  2*imm5;                    
      writeByteToMemory(address, coreReg[Rt],2);               //store a half word to the address and store it into the memory
    }
    
    shiftITState();
  }
  else
  {
    uint32_t address = coreReg[Rn] + 2*imm5;                    
    writeByteToMemory(address, coreReg[Rt],2);               //store a half word to the address and store it into the memory
  } 
  
  coreReg[PC] += 2;
}




/*Store Register (immediate) Encoding T1
 * 
    STR<c> <Rt>,[SP,#<imm8>]
      
   31 30 29 28 27 26 25 24 23 22 21 20 19 18 17 16 15 14 13 12 11 10 9 8 7 6 5 4 3 2 1 0
  |1  0  0   1  0|     imm5     |   Rn   |    Rt  |                unused               |

  where:
            <c><q>            See Standard assembler syntax fields on page A6-7.
            
            <Rt>              Specifies the source register. This register is allowed to be the SP.
            
            <Rn>              Specifies the base register. This register is allowed to be the SP.
            
            +/-               Is + or omitted to indicate that the immediate offset is added to the base register value
                              (add == TRUE), or – to indicate that the offset is to be subtracted (add == FALSE). Different
                              instructions are generated for #0 and #-0.
                              
            <imm>             Specifies the immediate offset added to or subtracted from the value of <Rn> to form the
                              address. Allowed values are multiples of 4 in the range 0-124 for encoding T1, multiples of
                              4 in the range 0-1020 for encoding T2, any value in the range 0-4095 for encoding T3, and
                              any value in the range 0-255 for encoding T4. For the offset addressing syntax, <imm> can be
                              omitted, meaning an offset of 0.
          
*/
void STRImmediateT2(uint32_t instruction)
{
  uint32_t imm8 = getBits(instruction,23,16);  
  uint32_t Rt   = getBits(instruction,26,24);

  if(inITBlock())
  {
    if( checkCondition(cond) )
    {
      uint32_t address = coreReg[SP] +  4*imm8;                    
      writeByteToMemory(address, coreReg[Rt],4);               //store a word to the address and store it into the memory
    }
    
    shiftITState();
  }
  else
  {
    uint32_t address = coreReg[SP] + 4*imm8;    
    writeByteToMemory(address, coreReg[Rt],4);               //store a word to the address and store it into the memory
  }
  
  coreReg[PC] += 2;
}



