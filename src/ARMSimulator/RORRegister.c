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


#include "RORRegister.h"
#include "ShiftOperation.h"
#include "ITandHints.h"
#include "StatusRegisters.h"
#include "ARMRegisters.h"
#include "getAndSetBits.h"
#include "getMask.h"
#include "ModifiedImmediateConstant.h"
#include "Thumb16bitsTable.h"
#include "ConditionalExecution.h"


/*Rotate Right Register To Register Encoding T1
        RORS <Rdn>,<Rm>       Outside IT block.
        ROR<c> <Rdn>,<Rm>     Inside IT block.
        
   31 30 29 28 27 26 25 24 23 22 21 20 19 18 17 16 15 14 13 12 11 10 9 8 7 6 5 4 3 2 1 0
  |0   1  0  0  0  0| 0  1  1  1|   Rm   |   Rdn  |              unused                 |
   
where:
          S             If present, specifies that the instruction updates the flags. Otherwise, the instruction does not
                        update the flags.
                        
          <c><q>        See Standard assembler syntax fields on page A6-7.
          
          <Rd>          Specifies the destination register.
          
          <Rn>          Specifies the register that contains the first operand.
          
          <Rm>          Specifies the register whose bottom byte contains the amount to rotate by.
*/
void RORRegisterT1(uint32_t instruction)
{
  uint32_t Rm = getBits(instruction, 21, 19);
  uint32_t Rdn = getBits(instruction, 18, 16);
	
  if(inITBlock())
  {
    if( checkCondition(cond) )
      executeRORRegister(Rdn, Rdn, Rm, 0);
    
    shiftITState();
  }
  else
    executeRORRegister(Rdn, Rdn, Rm, 1);
  
  coreReg[PC] += 2;
}


void executeRORRegister(uint32_t Rd, uint32_t Rn, uint32_t Rm, uint32_t S)
{
  uint32_t timesToRotate = getBits(coreReg[Rm], 7 ,0);
  coreReg[Rd] = executeROR(timesToRotate, coreReg[Rn], S);
  
  if( S == 1)
  {
    updateNegativeFlag(coreReg[Rd]);
    updateZeroFlag(coreReg[Rd]);
    
    // overflow flag is not affected and the handling of carry flag is done in the executeROR function
  }

}