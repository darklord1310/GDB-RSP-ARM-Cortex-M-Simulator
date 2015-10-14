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


#include "MULRegister.h"
#include "ITandHints.h"
#include "StatusRegisters.h"
#include "ARMRegisters.h"
#include "getAndSetBits.h"
#include "getMask.h"
#include "ModifiedImmediateConstant.h"
#include "Thumb16bitsTable.h"
#include "ConditionalExecution.h"


/*  
  Multiply Register to Register Encoding T1 
  
        MULS    <Rdm>,<Rn>,<Rdm>    Outside IT block.
        MUL<c>  <Rdm>,<Rn>,<Rdm>    Inside IT block
        
   31 30 29 28 27 26 25 24 23 22 21 20 19 18 17 16 15 14 13 12 11 10 9 8 7 6 5 4 3 2 1 0
  |0   1  0  0  0  0| 1  1  0  1|   Rn   |   Rdm  |             unused                  |
    
  where:
            S           If present, specifies that the instruction updates the flags. Otherwise, the instruction does not
                        update the flags.
                        
            <c><q>      See Standard assembler syntax fields on page A6-7.
            
            <Rd>        Specifies the destination register. If <Rd> is omitted, this register is the same as <Rn>.
            
            <Rn>        Specifies the register that contains the first operand.
            
            <Rm>        Specifies the register that contains the second operand.
  
*/
void MULRegisterT1(uint32_t instruction)
{
  uint32_t Rn = getBits(instruction, 21, 19);
  uint32_t Rdm = getBits(instruction, 18, 16);
	
  if( inITBlock() )
  {  
    if( checkCondition(cond) )
      executeMULRegister(Rdm, Rdm, Rn,0);  //status flag is not affected
    
    shiftITState();
  }
  else
    executeMULRegister(Rdm, Rdm, Rn, 1);   //status flag is affected
  
  
  coreReg[PC] += 2;
}




/*  
  Multiply Register to Register Encoding T2
  
      MUL<c> <Rd>,<Rn>,<Rm>
        
   31 30 29 28 27 26 25 24 23 22 21 20 19 18 17 16 15 14 13 12 11 10 9 8 7 6 5 4 3 2 1 0
  |1   1  1  1  1| 0  1  1  0| 0  0  0|     Rn    | 1  1  1  1|    Rd   |0 0 0 0|   Rm  |
    
  where:
            S           If present, specifies that the instruction updates the flags. Otherwise, the instruction does not
                        update the flags.
                        
            <c><q>      See Standard assembler syntax fields on page A6-7.
            
            <Rd>        Specifies the destination register. If <Rd> is omitted, this register is the same as <Rn>.
            
            <Rn>        Specifies the register that contains the first operand.
            
            <Rm>        Specifies the register that contains the second operand.
  
*/
void MULRegisterT2(uint32_t instruction)
{
  uint32_t Rn = getBits(instruction, 19, 16);
  uint32_t Rm = getBits(instruction, 3, 0);
  uint32_t Rd = getBits(instruction, 11, 8);
	
  if( inITBlock() )
  {  
    if( checkCondition(cond) )
      executeMULRegister(Rm, Rd, Rn,0);  
    
    shiftITState();
  }
  else
    executeMULRegister(Rm, Rd, Rn, 0);   
  
  
  coreReg[PC] += 4;
}



/*  Bitwise NOT (register) writes the bitwise inverse of a register value to the destination register. It can
    optionally update the condition flags based on the result.
  
    Input:  Rm              source register
            Rd              destination register
            S               indicator for affecting the flag or not

*/
void executeMULRegister(uint32_t Rm, uint32_t Rd, uint32_t Rn, uint32_t S)
{
  writeToCoreRegisters(Rd, coreReg[Rm] * coreReg[Rn] );
  
  if(S == 1)
  {
    updateZeroFlag(coreReg[Rd]);
    updateNegativeFlag(coreReg[Rd]);
  }
}


