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


#include "SignedUnsignedLongMultiplyDivide.h"
#include <assert.h>
#include "ARMRegisters.h"
#include "getAndSetBits.h"
#include "StatusRegisters.h"
#include "ADDSPRegister.h"
#include "ModifiedImmediateConstant.h"
#include "ITandHints.h"
#include "ConditionalExecution.h"
#include <stdio.h>


/*Signed Multiply Long Encoding T1
    SMULL<c> <RdLo>,<RdHi>,<Rn>,<Rm>
      
   31 30 29 28 27 26 25 24 23 22 21 20 19 18 17 16 15 14 13 12 11 10 9 8 7 6 5 4 3 2 1 0
  |1   1  1  1  1| 0  1  1  1| 0  0  0|     Rn    |     RdLo  |    RdHi |0 0 0 0|   Rm  |

where:
        <c><q>        See Standard assembler syntax fields on page A6-7.
        
        <RdLo>        Stores the lower 32 bits of the result.
        
        <RdHi>        Stores the upper 32 bits of the result.
        
        <Rn>          Specifies the register that contains the first operand.
        
        <Rm>          Specifies the register that contains the second operand.
*/
void SMULLT1(uint32_t instruction)
{
  uint32_t Rm = getBits(instruction,3,0);
  uint32_t Rn = getBits(instruction,19,16);
  uint32_t RdLo = getBits(instruction,15,12);
  uint32_t RdHi = getBits(instruction,11,8);
  long long int result = (long int)coreReg[Rn] * (long int)coreReg[Rm];

  if(inITBlock())
  {
    if( checkCondition(cond) )
    {
      coreReg[RdLo] = getBits(result,31,0);
      coreReg[RdHi] = (uint32_t)(result >> 32);
    }

    shiftITState();
  }
  else
  {
    coreReg[RdLo] = getBits(result,31,0);
    coreReg[RdHi] = (uint32_t)(result >> 32);
  }

  coreReg[PC] += 4;
}



void SDIVT1(uint32_t instruction)
{

}


/*Unsigned Multiply Long Encoding T1
    UMULL<c> <RdLo>,<RdHi>,<Rn>,<Rm>
      
   31 30 29 28 27 26 25 24 23 22 21 20 19 18 17 16 15 14 13 12 11 10 9 8 7 6 5 4 3 2 1 0
  |1   1  1  1  1| 0  1  1  1| 0  1  0|     Rn    |     RdLo  |    RdHi |0 0 0 0|   Rm  |

where:
        <c><q>        See Standard assembler syntax fields on page A6-7.
        
        <RdLo>        Stores the lower 32 bits of the result.
        
        <RdHi>        Stores the upper 32 bits of the result.
        
        <Rn>          Specifies the register that contains the first operand.
        
        <Rm>          Specifies the register that contains the second operand.
*/
void UMULLT1(uint32_t instruction)
{
  uint32_t Rm = getBits(instruction,3,0);
  uint32_t Rn = getBits(instruction,19,16);
  uint32_t RdLo = getBits(instruction,15,12);
  uint32_t RdHi = getBits(instruction,11,8);
  uint64_t result = convertToUnsigned(coreReg[Rn],32) * convertToUnsigned(coreReg[Rm],32);
  
  if(inITBlock())
  {
    if( checkCondition(cond) )
    {
      coreReg[RdLo] = getBits(result,31,0);
      coreReg[RdHi] = (uint32_t)(result >> 32);
    }

    shiftITState();
  }
  else
  {
    coreReg[RdLo] = getBits(result,31,0);
    coreReg[RdHi] = (uint32_t)(result >> 32);
  }

  coreReg[PC] += 4;
}




/*Signed Divide Encoding T1
    SDIV<c> <Rd>,<Rn>,<Rm>
      
   31 30 29 28 27 26 25 24 23 22 21 20 19 18 17 16 15 14 13 12 11 10 9 8 7 6 5 4 3 2 1 0
  |1   1  1  1  1| 0  1  1  1  0  0| 1|     Rn    | 1  1  1  1|    Rd   |1 1 1 1|   Rm  |

where:
        <c><q>        See Standard assembler syntax fields on page A6-7.
        
        <Rd>          Specifies the destination register. If <Rd> is omitted, this register is the same as <Rn>.
        
        <Rn>          Specifies the register that contains the dividend.
        
        <Rm>          Specifies the register that contains the divisor.
*/
void UDIVT1(uint32_t instruction)
{

}




/*Signed Multiply Accumulate Long Encoding T1
    SMLAL<c> <RdLo>,<RdHi>,<Rn>,<Rm>
      
   31 30 29 28 27 26 25 24 23 22 21 20 19 18 17 16 15 14 13 12 11 10 9 8 7 6 5 4 3 2 1 0
  |1   1  1  1  1| 0  1  1  1| 1  0  0|     Rn    |     RdLo  |    RdHi |0 0 0 0|   Rm  |

where:
        <c><q>        See Standard assembler syntax fields on page A6-7.
        
        <RdLo>        Stores the lower 32 bits of the result.
        
        <RdHi>        Stores the upper 32 bits of the result.
        
        <Rn>          Specifies the register that contains the first operand.
        
        <Rm>          Specifies the register that contains the second operand.
*/
void SMLALT1(uint32_t instruction)
{
  uint32_t Rm = getBits(instruction,3,0);
  uint32_t Rn = getBits(instruction,19,16);
  uint32_t RdLo = getBits(instruction,15,12);
  uint32_t RdHi = getBits(instruction,11,8);
  uint64_t constant = ( ( ( (uint64_t)coreReg[RdHi] ) << 32) | coreReg[RdLo] );
  long long int result = (long int)coreReg[Rn] * (long int)coreReg[Rm] + constant;

  if(inITBlock())
  {
    if( checkCondition(cond) )
    {
      coreReg[RdLo] = getBits(result,31,0);
      coreReg[RdHi] = (uint32_t)(result >> 32);
    }

    shiftITState();
  }
  else
  {
    coreReg[RdLo] = getBits(result,31,0);
    coreReg[RdHi] = (uint32_t)(result >> 32);
  }

  coreReg[PC] += 4;
}




/*Unsigned Multiply Accumulate Long Encoding T1
    UMLAL<c> <RdLo>,<RdHi>,<Rn>,<Rm>
      
   31 30 29 28 27 26 25 24 23 22 21 20 19 18 17 16 15 14 13 12 11 10 9 8 7 6 5 4 3 2 1 0
  |1   1  1  1  1| 0  1  1  1| 1  1  0|     Rn    |     RdLo  |    RdHi |0 0 0 0|   Rm  |

where:
        <c><q>        See Standard assembler syntax fields on page A6-7.
        
        <RdLo>        Stores the lower 32 bits of the result.
        
        <RdHi>        Stores the upper 32 bits of the result.
        
        <Rn>          Specifies the register that contains the first operand.
        
        <Rm>          Specifies the register that contains the second operand.
*/
void UMLALT1(uint32_t instruction)
{
  uint32_t Rm = getBits(instruction,3,0);
  uint32_t Rn = getBits(instruction,19,16);
  uint32_t RdLo = getBits(instruction,15,12);
  uint32_t RdHi = getBits(instruction,11,8);
  uint64_t constant = ( ( ( (uint64_t)coreReg[RdHi] ) << 32) | coreReg[RdLo] );
  uint64_t result = convertToUnsigned(coreReg[Rn],32) * convertToUnsigned(coreReg[Rm],32) + constant;
  
  if(inITBlock())
  {
    if( checkCondition(cond) )
    {
      coreReg[RdLo] = getBits(result,31,0);
      coreReg[RdHi] = (uint32_t)(result >> 32);
    }

    shiftITState();
  }
  else
  {
    coreReg[RdLo] = getBits(result,31,0);
    coreReg[RdHi] = (uint32_t)(result >> 32);
  }

  coreReg[PC] += 4;
}


long long int convertToUnsigned(uint64_t value, uint32_t numberOfBits)
{
  int i;
  long long int result = 0;
  
  for(i = 0; i < numberOfBits; i++)
  {
    if(getBits(value,0,0) == 1)
      result = result + (pow(2,i));
    
    value = (value >> 1);
  }
  return result;
}



