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


#include "PUSH.h"
#include "ITandHints.h"
#include "StatusRegisters.h"
#include "ARMRegisters.h"
#include "getAndSetBits.h"
#include "getMask.h"
#include "ModifiedImmediateConstant.h"
#include "ConditionalExecution.h"
#include "MemoryBlock.h"
#include "STRRegister.h"
#include "ErrorSignal.h"
#include "CException.h"



/*Push Multiple Registers Encoding T1
    PUSH<c> <registers>
      
  31 30 29 28 27 26 25 24 23 22 21 20 19 18 17 16 15 14 13 12 11 10 9 8 7 6 5 4 3 2 1 0
  |1  0  1  1| 0| 1  0|M|       register_list    |                unused               |
  
where:
          <c><q>            See Standard assembler syntax fields on page A6-7.
          
          <registers>       Is a list of one or more registers, separated by commas and surrounded by 
                            { and }. It specifies the set of registers to be stored. The registers
                            are stored in sequence, the lowest-numbered register to the lowest memory
                            address, through to the highest-numbered register to the highest memory address.
          
          The SP cannot be in the list.
          If the PC is in the list, the LR must not be in the list.
*/
void PUSHT1(uint32_t instruction)
{
  uint8_t M = getBits(instruction, 24,24);
  uint16_t temp = M << 6;
  uint16_t register_list = ( temp << 8 ) | getBits(instruction, 23,16);
  
  if( bitCount(register_list) < 1)
  {
    placePCtoVectorTable(UsageFault);
    Throw(UsageFault);
  }
 

  if(inITBlock())
  {
    if( checkCondition(cond) )
    {
      uint32_t address = coreReg[SP] - 4*bitCount(register_list);     
      pushMultipleRegisterToMemory(address, register_list, 16);
    }
    shiftITState();
    coreReg[PC] += 2;
  }
  else
  {
    uint32_t address = coreReg[SP] - 4*bitCount(register_list);      
    pushMultipleRegisterToMemory(address, register_list, 16);
    coreReg[PC] += 2;
  }
}



/*Push Multiple Registers Encoding T2
    PUSH<c> <registers>
      
  31 30 29 28 27 26 25 24 23 22 21 20 19 18 17 16 15 14 13 12 11 10 9 8 7 6 5 4 3 2 1 0
  |1  1  1  0  1| 0  0| 1  0  0| 1| 0| 1  1  0  1| 0| M|0 |         register_list      |               
  
where:
          <c><q>            See Standard assembler syntax fields on page A6-7.
          
          <registers>       Is a list of one or more registers, separated by commas and surrounded by 
                            { and }. It specifies the set of registers to be stored. The registers
                            are stored in sequence, the lowest-numbered register to the lowest memory
                            address, through to the highest-numbered register to the highest memory address.
          
          The SP cannot be in the list.
          If the PC is in the list, the LR must not be in the list.
*/
void PUSHT2(uint32_t instruction)
{
  uint8_t M = getBits(instruction, 14,14);
  uint16_t register_list = ( ( ( ( 0b0 << 1) | M) << 1) << 13) | getBits(instruction, 12,0);
  uint32_t address = coreReg[SP] - 4*bitCount(register_list);
  
  if(bitCount(register_list) < 2)
  {
    placePCtoVectorTable(UsageFault);
    Throw(UsageFault);
  }
  
  if(inITBlock())
  {
    if( checkCondition(cond) )
      pushMultipleRegisterToMemory(address, register_list, 16);
    
    shiftITState();
  }
  else     
    pushMultipleRegisterToMemory(address, register_list, 16);
  
  coreReg[PC] += 4;
}



int bitCount(uint32_t value)
{
  int count = 0, i;

  for(i = 0; i < 32; i++)
  {
    if(getBits(value,i,i) == 1)  
      count++;
  }
  
  return count;
}



void pushMultipleRegisterToMemory(uint32_t address, uint32_t registerList, int sizeOfRegisterList)
{
  int i;
  
  for(i = 0; i < sizeOfRegisterList; i++)
  {
    if( getBits(registerList, i ,i) == 1)           //if the bit[i] of the registerList is 1, then write the value of r[i] into the address
    {
      writeByteToMemory(address, coreReg[i], 4);
      address+=4;
    }
  }
  
  coreReg[SP] = coreReg[SP] - 4*bitCount(registerList);
  
}