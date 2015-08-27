#include "LDRLiteral.h"
#include "ITandHints.h"
#include "StatusRegisters.h"
#include "ARMRegisters.h"
#include "getAndSetBits.h"
#include "getMask.h"
#include "ModifiedImmediateConstant.h"
#include "Thumb16bitsTable.h"
#include "ConditionalExecution.h"
#include "MemoryBlock.h"
#include <stdio.h>
#include "ErrorSignal.h"
#include "ADR.h"
#include "LoadAndWriteMemory.h"


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
  
  if(inITBlock())
  {
    if( checkCondition(cond) )
    {
      uint32_t temp = alignPC(coreReg[PC] + 4, 4);              // the PC need to add with 4 and align it
                                                                // and the value is written into temp
      
      uint32_t imm10 = imm8 << 2;                               // the imm8 need to shift 2 times to the left and bit1:0 is force to 0
      
      uint32_t address = temp + imm10;                          // so the temp(which is the PC) + imm10 is the address where we need to get
                                                                // a word from the memory
      
      coreReg[Rt] = loadByteFromMemory(address, 4);             //load a word from the address and store it into the register 
    }

    shiftITState();
  }
  else
  {
    uint32_t temp = alignPC(coreReg[PC] + 4, 4);              // the PC need to add with 4 and align it
                                                              // and the value is written into temp
    
    uint32_t imm10 = imm8 << 2;                               // the imm8 need to shift 2 times to the left and bit1:0 is force to 0
    
    uint32_t address = temp + imm10;                          // so the temp(which is the PC) + imm10 is the address where we need to get
                                                              // a word from the memory
    
    coreReg[Rt] = loadByteFromMemory(address, 4);             //load a word from the address and store it into the register 
  }
  
  coreReg[PC] += 2;
}





/*Load Register(literal) Encoding T2 
 * 
    LDR<c>.W <Rt>,<label>
    LDR<c>.W <Rt>,[PC,#-0] Special case
      
   31 30 29 28 27 26 25 24 23 22 21 20 19 18 17 16 15 14 13 12 11 10 9 8 7 6 5 4 3 2 1 0
  |1  1   1  1  1| 0  0| 0|U | 1  0|1|  1  1  1  1|     Rt    |           imm12         |

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
void LDRLiteralT2(uint32_t instruction)
{
  uint32_t imm12 = getBits(instruction,11,0);  
  uint32_t Rt   = getBits(instruction,15,12);
  uint32_t U = getBits(instruction,23,23);
  uint32_t address;

  if(Rt == PC)                                                    //if the Rt is PC
  {
    if(inITBlock() && isLastInITBlock())                          //if it is last or inside the IT block, then only execute, else throw error
    {
      if( checkCondition(cond) )
      {
        uint32_t temp = alignPC(coreReg[PC] + 4, 4);              // the PC need to add with 4 and align it
                                                                  // and the value is written into temp
        if(U == 1)
          address = temp + imm12;
        else
          address = temp - imm12;
        
        if(getBits(address,1,0) == 0b00)
          coreReg[Rt] = loadByteFromMemory(address, 4);             //load a word from the address and store it into the register 
        else
        {
          placePCtoVectorTable(UsageFault);
          Throw(UsageFault);
        }
      }
      shiftITState();
    }
    else
    {
      placePCtoVectorTable(UsageFault);
      Throw(UsageFault);
    }
  }
  else
  {
    if(inITBlock())
    {
      if( checkCondition(cond) )
      {
        uint32_t temp = alignPC(coreReg[PC] + 4, 4);              // the PC need to add with 4 and align it
                                                                  // and the value is written into temp
        if(U == 1)
          address = temp + imm12;
        else
          address = temp - imm12;
        
        coreReg[Rt] = loadByteFromMemory(address, 4);             //load a word from the address and store it into the register 
      }
      
      shiftITState();
    }
    else
    {
      uint32_t temp = alignPC(coreReg[PC] + 4, 4);              // the PC need to add with 4 and align it
                                                                // and the value is written into temp
      if(U == 1)
        address = temp + imm12;
      else
        address = temp - imm12;
      
      coreReg[Rt] = loadByteFromMemory(address, 4);             //load a word from the address and store it into the register 
    }
    coreReg[PC] += 4;  
  }

}