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


#include "REV.h"
#include "ITandHints.h"
#include "StatusRegisters.h"
#include "ARMRegisters.h"
#include "getAndSetBits.h"
#include "getMask.h"
#include "ModifiedImmediateConstant.h"
#include "ConditionalExecution.h"
#include "MemoryBlock.h"
#include "UnconditionalAndConditionalBranch.h"                          // this is included because need to use the signExtend function


/*Byte-Reverse Word Encoding T1
    REV<c> <Rd>,<Rm>
      
  31 30 29 28 27 26 25 24 23 22 21 20 19 18 17 16 15 14 13 12 11 10 9 8 7 6 5 4 3 2 1 0
  |1  0  1  1| 1  0  1  0| 0  0|   Rm   |    Rd  |                unused               |
  
where:
          <c><q>            See Standard assembler syntax fields on page A6-7.
          
          <Rd>              Specifies the destination register.
          
          <Rm>              Specifies the register that contains the operand. Its number must be encoded twice in
                            encoding T2, in both the Rm and Rm2 fields.
                                  
*/
void REVT1(uint32_t instruction)
{
  uint32_t Rm = getBits(instruction,21,19);
  uint32_t Rd = getBits(instruction,18,16); 

  if(inITBlock())
  {
    if( checkCondition(cond) )
      executeREV(Rm, Rd);
    
    shiftITState();
  }
  else
    executeREV(Rm, Rd);
  
  coreReg[PC] += 2;
}



void executeREV(uint32_t Rm, uint32_t Rd)
{
  uint32_t result31to24 = getBits(coreReg[Rm] , 7, 0);                    //bit 31 to bit 24
  uint32_t result23to16 = getBits(coreReg[Rm] , 15, 8);                   //bit 23 to bit 16
  uint32_t result15to8 = getBits(coreReg[Rm] , 23, 16);                   //bit 15 to bit 8
  uint32_t result7to0 = getBits(coreReg[Rm] , 31, 24);                    //bit 7 to bit 0
  
  coreReg[Rd] = setBits(coreReg[Rd], result31to24, 31,24);
  coreReg[Rd] = setBits(coreReg[Rd], result23to16, 23,16);
  coreReg[Rd] = setBits(coreReg[Rd], result15to8, 15,8);
  coreReg[Rd] = setBits(coreReg[Rd], result7to0, 7,0);
}



/*Byte-Reverse Packed Halfword Encoding T1
    REV16<c> <Rd>,<Rm>
      
  31 30 29 28 27 26 25 24 23 22 21 20 19 18 17 16 15 14 13 12 11 10 9 8 7 6 5 4 3 2 1 0
  |1  0  1  1| 1  0  1  0| 0  1|   Rm   |    Rd  |                unused               |
  
where:
          <c><q>            See Standard assembler syntax fields on page A6-7.
          
          <Rd>              Specifies the destination register.
          
          <Rm>              Specifies the register that contains the operand. Its number must be encoded twice in
                            encoding T2, in both the Rm and Rm2 fields.
                                  
*/
void REV16T1(uint32_t instruction)
{
  uint32_t Rm = getBits(instruction,21,19);
  uint32_t Rd = getBits(instruction,18,16); 

  if(inITBlock())
  {
    if( checkCondition(cond) )
      executeREV16(Rm, Rd);
    
    shiftITState();
  }
  else
    executeREV16(Rm, Rd);
  
  coreReg[PC] += 2;
}


void executeREV16(uint32_t Rm, uint32_t Rd)
{
  uint32_t result31to24 = getBits(coreReg[Rm] , 23, 16);                  //bit 31 to bit 24
  uint32_t result23to16 = getBits(coreReg[Rm] , 31, 24);                  //bit 23 to bit 16
  uint32_t result15to8 = getBits(coreReg[Rm] , 7, 0);                     //bit 15 to bit 8
  uint32_t result7to0 = getBits(coreReg[Rm] , 15, 8);                     //bit 7 to bit 0
  
  coreReg[Rd] = setBits(coreReg[Rd], result31to24, 31,24);
  coreReg[Rd] = setBits(coreReg[Rd], result23to16, 23,16);
  coreReg[Rd] = setBits(coreReg[Rd], result15to8, 15,8);
  coreReg[Rd] = setBits(coreReg[Rd], result7to0, 7,0);
}




/*Byte-Reverse Signed Halfword Encoding T1
    REVSH<c> <Rd>,<Rm>
      
  31 30 29 28 27 26 25 24 23 22 21 20 19 18 17 16 15 14 13 12 11 10 9 8 7 6 5 4 3 2 1 0
  |1  0  1  1| 1  0  1  0| 1  1|   Rm   |    Rd  |                unused               |
  
where:
          <c><q>            See Standard assembler syntax fields on page A6-7.
          
          <Rd>              Specifies the destination register.
          
          <Rm>              Specifies the register that contains the operand. Its number must be encoded twice in
                            encoding T2, in both the Rm and Rm2 fields.
                                  
*/
void REVSHT1(uint32_t instruction)
{
  uint32_t Rm = getBits(instruction,21,19);
  uint32_t Rd = getBits(instruction,18,16); 

  if(inITBlock())
  {
    if( checkCondition(cond) )
      executeREVSH(Rm, Rd);
    
    shiftITState();
  }
  else
    executeREVSH(Rm, Rd);
  
  coreReg[PC] += 2;
}


void executeREVSH(uint32_t Rm, uint32_t Rd)
{
  
  uint32_t result31to8 = signExtend( getBits(coreReg[Rm] , 7, 0) , 8);                 //bit 31 to bit 8
  uint32_t result7to0  = getBits( coreReg[Rm], 15, 8);
  
  coreReg[Rd] = setBits(coreReg[Rd], result31to8, 31,8);
  coreReg[Rd] = setBits(coreReg[Rd], result7to0, 7,0);
}