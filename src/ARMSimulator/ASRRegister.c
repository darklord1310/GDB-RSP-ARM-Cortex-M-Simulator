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



#include "ASRRegister.h"
#include "ITandHints.h"
#include "StatusRegisters.h"
#include "ARMRegisters.h"
#include "getAndSetBits.h"
#include "getMask.h"
#include "ConditionalExecution.h"
#include "ShiftOperation.h"


/*Arithmetic Shift Right Register To Register Encoding T1
        ASRS <Rdn>,<Rm>       Outside IT block.
        ASR<c> <Rdn>,<Rm>     Inside IT block
        
   31 30 29 28 27 26 25 24 23 22 21 20 19 18 17 16 15 14 13 12 11 10 9 8 7 6 5 4 3 2 1 0
  |0   1  0  0  0  0| 0  1  0  0|   Rm   |   Rdn  |             unused                  |
   
where:
          S             If present, specifies that the instruction updates the flags. Otherwise, the instruction does not
                        update the flags.
                        
          <c><q>        See Standard assembler syntax fields on page A6-7.
          
          <Rd>          Specifies the destination register.
          
          <Rn>          Specifies the register that contains the first operand.
          
          <Rm>          Specifies the register whose bottom byte contains the amount to shift by.
*/
void ASRRegisterToRegisterT1(uint32_t instruction)
{
  uint32_t Rm = getBits(instruction, 21, 19);
  uint32_t Rdn = getBits(instruction, 18, 16);
  
  if(inITBlock())
  {  
    if( checkCondition(cond) )
      executeASRRegister(Rm, Rdn, Rdn, 0);  //status flag is not affected
    
    shiftITState();
  }
  else
    executeASRRegister(Rm, Rdn, Rdn, 1);   //status flag is affected
  
  coreReg[PC] += 2;

}


/* Arithmetic Shift Right Register Encoding T2

   ASR{S}<c>.W <Rd>,<Rn>,<Rm>

   31 30 29 28 27 26 25 24 23 22 21 20 19 18 17 16 15 14 13 12 11 10 9 8 7 6 5 4 3 2 1 0
  |1  1  1  1  1 |0  1  0 |0| 1  0 |S|     Rn     |1  1  1  1 |   Rd    |0|0 0 0|   Rm  |

where:
          S           If present, specifies that the instruction updates the flags. Otherwise, the instruction does not
                      update the flags.

          <c><q>      See Standard assembler syntax fields on page A6-7.

          <Rd>        Specifies the destination register.
          
          <Rn>        Specifies the register that contains the first operand.

          <Rm>        Specifies the register whose bottom byte contains the amount to shift by.
*/
void ASRRegisterT2(uint32_t instruction)
{
  uint32_t Rm =  getBits(instruction, 3, 0);
  uint32_t Rd = getBits(instruction, 11, 8);
  uint32_t Rn = getBits(instruction, 19, 16);
  uint32_t statusFlag = getBits(instruction, 20, 20);

  if(inITBlock())
  {
    if( checkCondition(cond) )
      executeASRRegister(Rm, Rd, Rn, statusFlag);
    shiftITState();
  }
  else
    executeASRRegister(Rm, Rd, Rn, statusFlag);

  coreReg[PC] += 4;
}


/* This instruction shifts a register value right by a variable number of bits, shifting in copies
   of its sign bit, and writes the result to the destination register. The variable number of bits is read from the
   bottom byte of a register. It can optionally update the condition flags based on the result.

   Inputs: 
            S              If present, specifies that the instruction updates the flags. Otherwise, the instruction does not
                           update the flags.
            Rd             Specifies the destination register.
            Rn             Specifies the register that contains the first operand.
            Rm             Specifies the register whose bottom byte contains the amount to shift by
*/
void executeASRRegister(uint32_t Rm, uint32_t Rd, uint32_t Rn, uint32_t S)
{
  int i, lastBitShifted;
  unsigned int timesToShift = getBits( coreReg[Rm] ,7, 0);        //get the lowest byte from the Rm register
  unsigned int mask = ( getBits( coreReg[Rn], 31,31 ) ) << 31;    //create the mask to perform arithmetic shift
  uint32_t temp = coreReg[Rn];

  if(timesToShift <= 32)                                          
  {
    for(i = 0; i < timesToShift; i++)
    {
      if( i == timesToShift - 1)                                  //this is to get the last bit of Rm before shifted out
        lastBitShifted = getBits(temp, 0,0);
      temp = ( temp >> 1 ) | mask;
    }
  }
  else
  {
    int MSB = getBits( coreReg[Rn], 31,31 );                      //if the time to shift is larger than 32 times, then is either
    if( MSB == 1)                                                 //return 0 or 0xffffffff and the lastBitShifted must be the MSB
      temp = 0xffffffff;
    else
      temp = 0;
    lastBitShifted = MSB;             
  }

  coreReg[Rd] = temp;
  
  if( S == 1)
  {
    updateNegativeFlag(coreReg[Rd]);
    updateZeroFlag(coreReg[Rd]);
    if(timesToShift != 0)
    {
      if(lastBitShifted == 1)
        setCarryFlag();
      else
        resetCarryFlag();
    }
  }
}