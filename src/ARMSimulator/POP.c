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



#include "POP.h"
#include "LoadAndWriteMemory.h"
#include "ITandHints.h"
#include "StatusRegisters.h"
#include "ARMRegisters.h"
#include "getAndSetBits.h"
#include "getMask.h"
#include "ModifiedImmediateConstant.h"
#include "ConditionalExecution.h"
#include "MemoryBlock.h"
#include "PUSH.h"
#include "CException.h"
#include "ErrorSignal.h"


/*Pop Multiple Registers Encoding T1
    POP<c> <registers>
      
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
  
  if( bitCount(register_list) < 1)
  {
    placePCtoVectorTable(UsageFault);
    Throw(UsageFault);
  }
  
  
  if(inITBlock())
  {
    if( checkCondition(cond) )
    {
      uint32_t address = coreReg[SP];     
      loadMultipleRegisterFromMemory(address, registerlist, 1, SP, 16);
    }
    shiftITState();
    coreReg[PC] += 2;
  }
  else
  {
    uint32_t address = coreReg[SP];      
    loadMultipleRegisterFromMemory(address, registerlist, 1, SP, 16);
    coreReg[PC] += 2;
  }
}









/*Pop Multiple Registers Encoding T2
    POP<c> <registers>
      
  31 30 29 28 27 26 25 24 23 22 21 20 19 18 17 16 15 14 13 12 11 10 9 8 7 6 5 4 3 2 1 0
  |1  1  1  0  1| 0  0| 0  1  0| 1| 1| 1  1  0  1|P |M | 0|        register_list       |
  
where:
          <c><q>            See Standard assembler syntax fields on page A6-7.
          
          <registers>       Is a list of one or more registers, separated by commas and surrounded by 
                            { and }. It specifies the set of registers to be stored. The registers
                            are stored in sequence, the lowest-numbered register to the lowest memory
                            address, through to the highest-numbered register to the highest memory address.
                            
          The SP cannot be in the list.
          If the PC is in the list, the LR must not be in the list.
                            
*/
void POPT2(uint32_t instruction)
{
  uint32_t M = getBits(instruction, 14, 14);
  uint32_t P = getBits(instruction, 15, 15);
  uint32_t registerList = getBits(instruction, 12, 0);
  registerList = ( ( (P << 1) | M) << 13) | registerList;
  
  if(inITBlock())
  {
    if( checkCondition(cond) )
    {  
      loadMultipleRegisterFromMemory(coreReg[SP], registerList, 1, SP, 16);
    }
    shiftITState();
  }
  else
  {  
    loadMultipleRegisterFromMemory(coreReg[SP], registerList, 1, SP, 16);
  }
  
  if(P != 1)
    coreReg[PC] += 4;
}