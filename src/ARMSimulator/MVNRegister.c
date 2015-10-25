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

#include "MVNRegister.h"
#include "ITandHints.h"
#include "StatusRegisters.h"
#include "ARMRegisters.h"
#include "getAndSetBits.h"
#include "getMask.h"
#include "ModifiedImmediateConstant.h"
#include "Thumb16bitsTable.h"
#include "ConditionalExecution.h"
#include "ShiftOperation.h"

/*  
  Move Not Register to Register Encoding T1 
  
      MVNS    <Rd>,<Rm>     Outside IT block.
      MVN<c>  <Rd>,<Rm>     Inside IT block.
        
   31 30 29 28 27 26 25 24 23 22 21 20 19 18 17 16 15 14 13 12 11 10 9 8 7 6 5 4 3 2 1 0
  |0   1  0  0  0  0| 1  1  1  1|   Rm   |   Rdn  |             unused                  |
    
  where:
            S           If present, specifies that the instruction updates the flags. Otherwise, the instruction does not
                        update the flags.
                        
            <c><q>      See Standard assembler syntax fields on page A6-7.
            
            <Rd>        Specifies the destination register.
            
            <Rm>        Specifies the register that is optionally shifted and used as the source register.
            
            <shift>     Specifies the shift to apply to the value read from <Rm>. If <shift> is omitted, no shift is
                        applied and both encodings are permitted. If <shift> is specified, only encoding T2 is
                        permitted. The possible shifts and how they are encoded are described in Shifts applied to a
                        register on page A6-12.
  
*/
void MVNRegisterT1(uint32_t instruction)
{
  uint32_t Rm = getBits(instruction, 21, 19);
  uint32_t Rd = getBits(instruction, 18, 16);
	
  if(inITBlock())
  {  
    if( checkCondition(cond) )
    {
      uint32_t result = executeShiftOperation(OMITTED, 0, coreReg[Rm], 0);
      writeToCoreRegisters(Rd,  ~result );
      //no update flag here
    }
   
    shiftITState();
  }
  else
  {
    uint32_t result = executeShiftOperation(OMITTED, 0, coreReg[Rm], 1);
    writeToCoreRegisters(Rd,  ~result );

    updateZeroFlag(coreReg[Rd]);
    updateNegativeFlag(coreReg[Rd]);
    // overflow flag will not be affected and the handling of carry flag is inside the executeShiftOperation
  }
  
  coreReg[PC] += 2;
}





/*  
  Move Not Register to Register Encoding T2
  
      MVN{S}<c>.W <Rd>,<Rm>{,shift>}
        
   31 30 29 28 27 26 25 24 23 22 21 20 19 18 17 16 15 14 13 12 11 10 9 8 7  6 5  4 3 2 1 0
  |1   1  1  0  1| 0  1| 0  0  1  1| S| 1  1  1  1| 0|  imm3  |    Rd  |imm2 |type|   Rm  |                 
    
  where:
            S           If present, specifies that the instruction updates the flags. Otherwise, the instruction does not
                        update the flags.
                        
            <c><q>      See Standard assembler syntax fields on page A6-7.
            
            <Rd>        Specifies the destination register.
            
            <Rm>        Specifies the register that is optionally shifted and used as the source register.
            
            <shift>     Specifies the shift to apply to the value read from <Rm>. If <shift> is omitted, no shift is
                        applied and both encodings are permitted. If <shift> is specified, only encoding T2 is
                        permitted. The possible shifts and how they are encoded are described in Shifts applied to a
                        register on page A6-12.
  
*/
void MVNRegisterT2(uint32_t instruction)
{
  uint32_t Rd = getBits(instruction,11,8);
  uint32_t Rm = getBits(instruction,3,0);
  uint32_t type = getBits(instruction,5,4);
  uint32_t imm2 = getBits(instruction,7,6);
  uint32_t imm3 = getBits(instruction,14,12);
  uint32_t S = getBits(instruction,20,20);
  uint32_t shiftAmount = (imm3 << 2) | imm2;
  
  if(inITBlock())
  {  
    if( checkCondition(cond) )
    {
      int shiftType = determineShiftOperation(type, shiftAmount);
      uint32_t result = executeShiftOperation(shiftType, shiftAmount, coreReg[Rm], S);
      writeToCoreRegisters(Rd,  ~result );
      if(S == 1)
      {
        updateZeroFlag(coreReg[Rd]);
        updateNegativeFlag(coreReg[Rd]);
        // overflow flag will not be affected and the handling of carry flag is inside the executeShiftOperation
      }  
    }

    shiftITState();
  }
  else
  {
    int shiftType = determineShiftOperation(type, shiftAmount);
    uint32_t result = executeShiftOperation(shiftType, shiftAmount, coreReg[Rm], S);
    writeToCoreRegisters(Rd,  ~result );
    
    if(S == 1)
    {
      updateZeroFlag(coreReg[Rd]);
      updateNegativeFlag(coreReg[Rd]);
      // overflow flag will not be affected and the handling of carry flag is inside the executeShiftOperation
    }
  }  
  
  coreReg[PC] += 4;
}






