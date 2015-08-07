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
  
  coreReg[PC] += 2;
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
  
  coreReg[PC] += 2;
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
  
  coreReg[PC] += 2;
}




/*Store Multiple Increment After (Store Multiple Empty Ascending) Encoding T1
 * 
    STM<c> <Rn>!,<registers>
      
   31 30 29 28 27 26 25 24 23 22 21 20 19 18 17 16 15 14 13 12 11 10 9 8 7 6 5 4 3 2 1 0
  |1  1  0   0| 0|   Rn   |      Register List    |                unused               |

  where:
            <c><q>            See Standard assembler syntax fields on page A6-7.
            
            <Rn>              The base register. The SP can be used.
            
            !                 Causes the instruction to write a modified value back to <Rn>. If ! is omitted, the instruction
                              does not change <Rn>.
            
            <registers>       Is a list of one or more registers to be stored, separated by commas and surrounded by { and
                              }. The lowest-numbered register is stored to the lowest memory address, through to the
                              highest-numbered register to the highest memory address.
                              Encoding T2 does not support a list containing only one register. If an STM instruction with
                              just one register <Rt> in the list is assembled to Thumb and encoding T1 is not available, it
                              is assembled to the equivalent STR<c><q> <Rt>,[<Rn>]{,#4} instruction.
                              The SP and PC cannot be in the list.
          
          Encoding T2 is not available for instructions with the base register in the list and ! specified,
          and the use of such instructions is deprecated. If the base register is not the lowest-numbered
          register in the list, such an instruction stores an UNKNOWN value for the base register.
          
*/
void STMRegisterT1(uint32_t instruction)
{
  uint32_t Rn = getBits(instruction, 26,24);
  uint32_t registerList = getBits(instruction, 23,16);  

  if(inITBlock())
  {
    if( checkCondition(cond) )
    {                   
      writeMultipleRegisterToMemory(coreReg[Rn], registerList, 1, Rn);
    }
    shiftITState();
  }
  else
  {                 
    writeMultipleRegisterToMemory(coreReg[Rn], registerList, 1, Rn);
  }
  
  coreReg[PC] += 2;
}


/* This function will write multiple register to memory based on the register list given
 * 
 * Input:  address          the base address of the memory
 *         registerList     the number of register which the value will be written into memory
 *         writeBack        if 1 then means writeback is true, 0 means false
 *         Rn               the destination register which the value will be updated if writeback is 1
 * 
 */
void writeMultipleRegisterToMemory(uint32_t address, uint32_t registerList, uint32_t writeBack, uint32_t Rn)
{
  int sizeOfRegisterList = 8, i, bitCount = 0;
  
  for(i = 0; i < sizeOfRegisterList; i++)
  {
    if( getBits(registerList, i ,i) == 1)           //if the bit[i] of the registerList is 1, then write the value of r[i] into the address
    {
      writeByteToMemory(address, coreReg[i], 4);
      bitCount++;
      address+=4;
    }
  }
  
  if(writeBack == 1)                                //if writeback is 1 then update the Rn register
  {
    coreReg[Rn] = coreReg[Rn] + 4*bitCount;
  }
  
}

/*
 * LowestSetBit(x) is the minimum bit number of any of its bits that are ones. If all of its bits are zeros,
 * LowestSetBit(x) = N.
 * 
 */
int lowestSetBit(uint32_t value)
{
  int MSB = 32, i, counter = 0;
  
  for(i = 0; i < 32; i++)
  {
    if( getBits(value, i ,i) == 1 )
      counter++;
  }
  
  return counter;
  
}