/*  
    GDB RSP and ARM Simulator

    Copyright (C) 2015 Wong Yan Yin, <jet_wong@hotmail.com>,
    Jackson Teh Ka Sing, <jackson_dmc69@hotmail.com>

    This file is part of GDB RSP and ARM Simulator.

    This program is free software, you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY, without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with This program.  If not, see <http://www.gnu.org/licenses/>.
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



/*Store Register Byte (immediate) Encoding T2
 * 
    STRB<c>.W <Rt>,[<Rn>,#<imm12>]
      
   31 30 29 28 27 26 25 24 23 22 21 20 19 18 17 16 15 14 13 12 11 10 9 8 7 6 5 4 3 2 1 0
  | 1  1  1  1  1| 0  0| 0  1  0  0  0|     Rn    |     Rt    |          imm12          |

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
void STRBImmediateT2(uint32_t instruction)
{
  uint32_t imm12 = getBits(instruction, 11, 0);
  uint32_t Rt = getBits(instruction,15,12);
  uint32_t Rn = getBits(instruction,19,16);
  uint32_t address = coreReg[Rn] +  imm12; 

  if(Rn == 0b1111 || Rt == 0b1111)
  {
    placePCtoVectorTable(UsageFault);
    Throw(UsageFault);
  }

  if(inITBlock())
  {
    if( checkCondition(cond) )        
      writeByteToMemory(address, coreReg[Rt],1);               //store a byte to the address and store it into the memory
    
    shiftITState();
  }
  else               
    writeByteToMemory(address, coreReg[Rt],1);               //store a byte to the address and store it into the memory
    
  coreReg[PC] += 4;
}


/*Store Register Byte (immediate) Encoding T3
 * 
    STRB<c> <Rt>,[<Rn>,#-<imm8>]
    STRB<c> <Rt>,[<Rn>],#+/-<imm8>
    STRB<c> <Rt>,[<Rn>,#+/-<imm8>]!
      
   31 30 29 28 27 26 25 24 23 22 21 20 19 18 17 16 15 14 13 12 11 10 9 8 7 6 5 4 3 2 1 0
  | 1  1  1  1  1| 0  0| 0  0  0  0  0|     Rn    |     Rt    | 1| P|U|W|     imm8      |

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
void STRBImmediateT3(uint32_t instruction)
{
  uint32_t imm8 = getBits(instruction, 7, 0);
  uint32_t Rt = getBits(instruction,15,12);
  uint32_t Rn = getBits(instruction,19,16);
  uint32_t W = getBits(instruction,8,8);
  uint32_t U = getBits(instruction,9,9);
  uint32_t P = getBits(instruction,10,10);
  uint32_t address;

  if(U == 1)
    address = coreReg[Rn] + imm8;
  else
    address = coreReg[Rn] - imm8;

  if(P == 1 && W == 0 && U == 1)                    //if this condition meet, this is actually a STRBT instruction
    STRBT(instruction);
    
  int check = isOffPostOrPreIndex(P,W);
  
  if(check == UNDEFINED || Rn == 0b1111)
  {
    placePCtoVectorTable(UsageFault);
    Throw(UsageFault);
  }
  
  if(inITBlock())
  {
    if( checkCondition(cond) )
    {
      if(check == OFFINDEX)
        writeByteToMemory(address, coreReg[Rt],1);
      else if(check == PREINDEX)
      {
        writeByteToMemory(address, coreReg[Rt],1);
        coreReg[Rn] = address;
      }
      else 
      {
        writeByteToMemory(coreReg[Rn], coreReg[Rt],1);
        coreReg[Rn] = address;
      }
    }      
                   
    shiftITState();
  }
  else
  {
    if(check == OFFINDEX)
      writeByteToMemory(address, coreReg[Rt],1);
    else if(check == PREINDEX)
    {
      writeByteToMemory(address, coreReg[Rt],1);
      coreReg[Rn] = address;
    }
    else 
    {
      writeByteToMemory(coreReg[Rn], coreReg[Rt],1);
      coreReg[Rn] = address;
    }
  }         
    
  coreReg[PC] += 4;
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





/*Store Register Halfword (immediate) Encoding T2
 * 
    STRH<c>.W <Rt>,[<Rn>{,#<imm12>}]
      
   31 30 29 28 27 26 25 24 23 22 21 20 19 18 17 16 15 14 13 12 11 10 9 8 7 6 5 4 3 2 1 0
  |1   1  1  1  1| 0  0| 0  1  0  1  0|     Rn    |      Rt   |          imm12          |

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
void STRHImmediateT2(uint32_t instruction)
{
  uint32_t imm12 = getBits(instruction, 11, 0);
  uint32_t Rn = getBits(instruction,19,16);
  uint32_t Rt = getBits(instruction,15,12);
  
  if(inITBlock())
  {
    if( checkCondition(cond) )
    {
      uint32_t address = coreReg[Rn] +  imm12;                    
      writeByteToMemory(address, coreReg[Rt],2);               //store a half word to the address and store it into the memory
    }
    
    shiftITState();
  }
  else
  {
    uint32_t address = coreReg[Rn] + imm12;                    
    writeByteToMemory(address, coreReg[Rt],2);               //store a half word to the address and store it into the memory
  } 
  
  coreReg[PC] += 4;
}



/*Store Register Halfword (immediate) Encoding T3
 * 
    STRH<c> <Rt>,[<Rn>,#-<imm8>]
    STRH<c> <Rt>,[<Rn>],#+/-<imm8>
    STRH<c> <Rt>,[<Rn>,#+/-<imm8>]!
      
   31 30 29 28 27 26 25 24 23 22 21 20 19 18 17 16 15 14 13 12 11 10 9 8 7 6 5 4 3 2 1 0
  |1   1  1  1  1| 0  0| 0  0  0  1  0|     Rn    |      Rt   | 1|P| U|W|      imm8     |

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
void STRHImmediateT3(uint32_t instruction)
{
  uint32_t imm8 = getBits(instruction, 7, 0);
  uint32_t Rt = getBits(instruction,15,12);
  uint32_t Rn = getBits(instruction,19,16);
  uint32_t W = getBits(instruction,8,8);
  uint32_t U = getBits(instruction,9,9);
  uint32_t P = getBits(instruction,10,10);
  uint32_t address;

  if(U == 1)
    address = coreReg[Rn] + imm8;
  else
    address = coreReg[Rn] - imm8;

  if(P == 1 && W == 0 && U == 1)                    //if this condition meet, this is actually a STRHT instruction
    STRHT(instruction);
    
  int check = isOffPostOrPreIndex(P,W);
  
  if(check == UNDEFINED || Rn == 0b1111)
  {
    placePCtoVectorTable(UsageFault);
    Throw(UsageFault);
  }
  
  if(inITBlock())
  {
    if( checkCondition(cond) )
    {
      if(check == OFFINDEX)
        writeByteToMemory(address, coreReg[Rt],2);
      else if(check == PREINDEX)
      {
        writeByteToMemory(address, coreReg[Rt],2);
        coreReg[Rn] = address;
      }
      else 
      {
        writeByteToMemory(coreReg[Rn], coreReg[Rt],2);
        coreReg[Rn] = address;
      }
    }      
                   
    shiftITState();
  }
  else
  {
    if(check == OFFINDEX)
      writeByteToMemory(address, coreReg[Rt],2);
    else if(check == PREINDEX)
    {
      writeByteToMemory(address, coreReg[Rt],2);
      coreReg[Rn] = address;
    }
    else 
    {
      writeByteToMemory(coreReg[Rn], coreReg[Rt],2);
      coreReg[Rn] = address;
    }
  }         
    
  coreReg[PC] += 4;
}


/*Store Register (immediate) Encoding T2
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




/*Store Register (immediate) Encoding T3
 * 
    STR<c>.W <Rt>,[<Rn>,#<imm12>]
      
   31 30 29 28 27 26 25 24 23 22 21 20 19 18 17 16 15 14 13 12 11 10 9 8 7 6 5 4 3 2 1 0
  |1   1  1  1  1| 0  0| 0  1  1  0  0|     Rn    |     Rt    |          imm12          |

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
void STRImmediateT3(uint32_t instruction)
{
  uint32_t imm12 = getBits(instruction,11,0);  
  uint32_t Rt   = getBits(instruction,15,12);
  uint32_t Rn   = getBits(instruction,19,16);
  uint32_t address = coreReg[Rn] +  imm12; 
  
  if(inITBlock())
  {
    if( checkCondition(cond) )      
      writeByteToMemory(address, coreReg[Rt],4);              
    
    shiftITState();
  }
  else
    
    writeByteToMemory(address, coreReg[Rt],4);             
  
  coreReg[PC] += 4;
}



/*Store Register (immediate) Encoding T4
 * 
    STR<c> <Rt>,[<Rn>,#-<imm8>]
    STR<c> <Rt>,[<Rn>],#+/-<imm8>
    STR<c> <Rt>,[<Rn>,#+/-<imm8>]!
      
   31 30 29 28 27 26 25 24 23 22 21 20 19 18 17 16 15 14 13 12 11 10 9 8 7 6 5 4 3 2 1 0
  |1   1  1  1  1| 0  0| 0  0  1  0  0|     Rn    |     Rt    | 1|P |U|W|      imm8     |

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
void STRImmediateT4(uint32_t instruction)
{
  uint32_t imm8 = getBits(instruction, 7, 0);
  uint32_t Rt = getBits(instruction,15,12);
  uint32_t Rn = getBits(instruction,19,16);
  uint32_t W = getBits(instruction,8,8);
  uint32_t U = getBits(instruction,9,9);
  uint32_t P = getBits(instruction,10,10);
  uint32_t address;

  if(U == 1)
    address = coreReg[Rn] + imm8;
  else
    address = coreReg[Rn] - imm8;

  if(P == 1 && W == 0 && U == 1)                    //if this condition meet, this is actually a STRT instruction
    STRT(instruction);
    
  int check = isOffPostOrPreIndex(P,W);
  
  if(check == UNDEFINED || Rn == 0b1111)
  {
    placePCtoVectorTable(UsageFault);
    Throw(UsageFault);
  }
  
  if(inITBlock())
  {
    if( checkCondition(cond) )
    {
      if(check == OFFINDEX)
        writeByteToMemory(address, coreReg[Rt],4);
      else if(check == PREINDEX)
      {
        writeByteToMemory(address, coreReg[Rt],4);
        coreReg[Rn] = address;
      }
      else 
      {
        writeByteToMemory(coreReg[Rn], coreReg[Rt],4);
        coreReg[Rn] = address;
      }
    }      
                   
    shiftITState();
  }
  else
  {
    if(check == OFFINDEX)
      writeByteToMemory(address, coreReg[Rt],4);
    else if(check == PREINDEX)
    {
      writeByteToMemory(address, coreReg[Rt],4);
      coreReg[Rn] = address;
    }
    else 
    {
      writeByteToMemory(coreReg[Rn], coreReg[Rt],4);
      coreReg[Rn] = address;
    }
  }         
    
  coreReg[PC] += 4;
  
}


void STRBT(uint32_t instruction)
{
  
  
}

void STRHT(uint32_t instruction)
{
  
  
}

void STRT(uint32_t instruction)
{
  
  
}