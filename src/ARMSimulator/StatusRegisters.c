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


#include "StatusRegisters.h"
#include "ARMRegisters.h"
#include "getAndSetBits.h"
#include "getMask.h"
#include <stdio.h>
#include <assert.h>
#include "ARMRegisters.h"
#include "ErrorSignal.h"
#include "ConditionalExecution.h"
#include <math.h>

/*
  To check if it is in IT block or not

  Return:   1     if is inside IT block
            0     if is outside IT block

*/
int inITBlock()
{
  uint32_t IT26to25 = getBits(coreReg[xPSR], 26,25);
  uint32_t IT15to10 = getBits(coreReg[xPSR], 15,10);
  if(IT15to10 == 0 && IT26to25 == 0)            //outside IT block
    return 0;
  else
    return 1;
}



int isLastInITBlock()
{
  uint32_t IT1to0 = getBits(coreReg[xPSR], 26,25);        //get the IT[1:0] from coreReg[xPSR]
  uint32_t IT7to2 = getBits(coreReg[xPSR], 15,10);        //get the IT[7:2] from coreReg[xPSR]
  uint32_t IT = (IT7to2 << 2) | IT1to0;                   //combine the IT[1:0] and IT[7:2]

  if( getBits(IT, 3,0) == 0b1000 )
    return 1;
  else
    return 0;

}


void shiftITState()
{
  uint32_t IT1to0 = getBits(coreReg[xPSR], 26,25);        //get the IT[1:0] from coreReg[xPSR]
  uint32_t IT7to2 = getBits(coreReg[xPSR], 15,10);        //get the IT[7:2] from coreReg[xPSR]
  uint32_t IT = (IT7to2 << 2) | IT1to0;                   //combine the IT[1:0] and IT[7:2]
  uint32_t IT4to0 = getBits(IT,4,0) << 1;                 //get the IT[4:0] and perform the shifting
  cond = setBits(cond , getBits(IT4to0, 4, 4), 0, 0);     //update the condition

  IT = setBits(IT, IT4to0, 4, 0);                         //set the IT bit 4 to 0 with the value shifted
  if( getBits(IT, 3,0) == 0)
  {
    coreReg[xPSR] = setBits( coreReg[xPSR], 0b00,26,25);
    coreReg[xPSR] = setBits( coreReg[xPSR], 0b000000,15,10);     //set to IT state to 0 if IT[3:0] == 0
  }
  else
  {
    coreReg[xPSR] = setBits( coreReg[xPSR], getBits(IT, 1, 0) , 26 , 25);
    coreReg[xPSR] = setBits( coreReg[xPSR], getBits(IT, 7, 2) , 15 , 10);
  }
}


/*
  This function will get the bits 15 to 12 which
  is the IT[7:4] indicating the base condition

*/
uint32_t getITCond()
{
  return getBits(coreReg[xPSR], 15,12);

}

bool isNegative()
{
  if( getBits(coreReg[xPSR], 31, 31) )
    return true;
  else
    return false;
}

bool isZero()
{
  if( getBits(coreReg[xPSR], 30, 30) )
    return true;
  else
    return false;
}

bool isCarry()
{
  if( getBits(coreReg[xPSR], 29, 29) )
    return true;
  else
    return false;
}

bool isOverflow()
{
  if( getBits(coreReg[xPSR], 28, 28) )
    return true;
  else
    return false;
}

void setCarryFlag()
{
  coreReg[xPSR] = coreReg[xPSR] | 0x20000000;
}

void resetCarryFlag()
{
  coreReg[xPSR] = coreReg[xPSR] & 0xdfffffff;
}

void setNegativeFlag()
{
  coreReg[xPSR] = coreReg[xPSR] | 0x80000000;

}

void resetNegativeFlag()
{
  coreReg[xPSR] = coreReg[xPSR] & 0x7fffffff;
}

void setZeroFlag()
{
  coreReg[xPSR] = coreReg[xPSR] | 0x40000000;

}

void resetZeroFlag()
{
  coreReg[xPSR] = coreReg[xPSR] & 0xbfffffff;
}

void setOverflowFlag()
{
  coreReg[xPSR] = coreReg[xPSR] | 0x10000000;

}

void resetOverflowFlag()
{
  coreReg[xPSR] = coreReg[xPSR] & 0xefffffff;
}


void updateZeroFlag(uint32_t value)
{
  if(value == 0)
    setZeroFlag();
  else
    resetZeroFlag();
}

void updateNegativeFlag(uint32_t value)
{
  if( getBits(value,31,31) == 1)
    setNegativeFlag();
  else
    resetNegativeFlag();
}


/* This function will determine whether data accesses are big-endian or little-endian 
   
   31 30 29 28 27 26 25 24 23 22 21 20 19 18 17 16 15 14 13 12 11 10 9  8 7 6 5 4 3 2 1 0
  |                 VECTKEY VECTKEYSTAT           |||                                    |
                                                   |
                                                   |
                                                ENDIANNESS
                                                 
   ENDIANNESS, bit[15]        Indicates the memory system endianness:
                                  0 Little endian.
                                  1 Big endian.

  This bit is static or configured by a hardware input on reset.
  This bit is read only.

   return 1       if big-endian
   return 0       if little-endian
 */
int bigEndian()
{
  return(getBits(readSCBRegisters(AIRCR) ,15,15) );
}



/* This will update the carry flag based on the addition result
   of value1 and value2

*/
void updateCarryFlagAddition(uint32_t value1, uint32_t value2)
{
  int bit0 = 0, intermediateCarry = 0, i,adder;

  long long int v1 = (long long int)value1;
  long long int v2 = (long long int)value2;

  if(v1 + v2 >= 0x100000000)
    setCarryFlag();
  else
    resetCarryFlag();

}


/* This will update the carry flag based on the subtraction result
   of value1 and value2

*/
void updateCarryFlagSubtraction(uint32_t value1, uint32_t value2)
{
  if( value1 >= value2)
    setCarryFlag();
  else
    resetCarryFlag();
}


/*
Overflow Rule for addition

    Overflow occurs if

    (+A) + (+B) = −C
    (−A) + (−B) = +C

*/
void updateOverflowFlagAddition(uint32_t value1, uint32_t value2, uint32_t result)
{
  int signForValue1 = getBits(value1,31,31);
  int signForValue2 = getBits(value2,31,31);
  int signForResult = getBits(result,31,31);

  if(   ( signForValue1 == 0 && signForValue2 == 0 && signForResult == 1) || ( signForValue1 == 1 && signForValue2 == 1 && signForResult == 0)   )
    setOverflowFlag();
  else
    resetOverflowFlag();
}

/*
Overflow Rule for subtraction

    Overflow occurs if

    (+A) − (−B) = −C
    (−A) − (+B) = +C
*/
void updateOverflowFlagSubtraction(uint32_t value1, uint32_t value2, uint32_t result)
{
  int signForValue1 = getBits(value1,31,31);
  int signForValue2 = getBits(value2,31,31);
  int signForResult = getBits(result,31,31);

  if(   ( signForValue1 == 0 && signForValue2 == 1 && signForResult == 1) || ( signForValue1 == 1 && signForValue2 == 0 && signForResult == 0)   )
    setOverflowFlag();
  else
    resetOverflowFlag();
}


bool isQSet()
{
  if( getBits(coreReg[xPSR], 27, 27) )
    return true;
  else
    return false;
}


void setQFlag()
{
  coreReg[xPSR] = coreReg[xPSR] | 0x08000000;
}

/*
  To update the Q flag based on the result and signed range given

  Input: max            max range of the saturation value
         min            min range of the saturation value
         result         value after saturated
         sign
            0           means unsigned saturation
            1           means signed saturation
*/
void updateQFlag(int32_t max, int32_t min, int32_t result, int32_t sign)
{
  if(sign)
  {
    if((result > max) || (result < min))
        setQFlag();
  }
  else
  {
    if((result > max) || (result < 0))
      setQFlag();
  }
}



/*
  This function actually should not be included here, it should be included in
  a separate module, but due to the troublesome to include the module header 
  to all the test files, it is place here instead
  
  This function will check whether the FPU is enable or not
  If FPU is not enable but is trying to use it, then throw error
  
  31 30 29 28 27 26 25 24 23 22 21 20 19 18 17 16 15 14 13 12 11 10 9  8 7 6 5 4 3 2 1 0
  |        Reserved      |CP11| CP10|                      Reserved                     |


*/
void executeFPUChecking()
{
  if(getBits( loadByteFromMemory(0xE000ED88, 4) , 23,20) != 0b1111)
    ThrowError();
}


/*  This function will determine and return the correct value for d/n/m based on the dp_operation

    register Name       can be either D/N/M
    Vx                  can be either Vd/Vn/Vm
    
    
    d = if dp_operation then UInt(D:Vd) else UInt(Vd:D);
    n = if dp_operation then UInt(N:Vn) else UInt(Vn:N);
    m = if dp_operation then UInt(M:Vm) else UInt(Vm:M);
*/
uint32_t determineRegisterBasedOnSZ(uint32_t registerName, uint32_t Vx, uint32_t dpOperation)
{
  assert(Vx <= 0b1111);
  
  if(dpOperation)
    return ( (registerName << 4) | Vx);
  else
    return ( (Vx << 1) | registerName);
}



uint64_t FPNeg(uint64_t value, int size)
{
  uint32_t signBit = getBits(value,size-1,size-1);
  
  if(signBit)
    value = setBits(value,0b0,size-1,size-1);
  else
    value = setBits(value,0b1,size-1,size-1);
  
  return value;
}


uint32_t FPMulSinglePrecision(uint32_t value1, uint32_t value2)
{
  float v1 = *(float *)&value1;
  float v2 = *(float *)&value2;
  float ans = v1 * v2;

  return ( *(uint32_t *)&ans );
}

uint32_t FPDivSinglePrecision(uint32_t value1, uint32_t value2)
{
  float v1 = *(float *)&value1;
  float v2 = *(float *)&value2;
  float ans = v1 / v2;

  return ( *(uint32_t *)&ans );
}

uint32_t FPAddSinglePrecision(uint32_t value1, uint32_t value2)
{
  float v1 = *(float *)&value1;
  float v2 = *(float *)&value2;
  float ans = v1 + v2;

  return ( *(uint32_t *)&ans );
}

uint32_t FPSubSinglePrecision(uint32_t value1, uint32_t value2)
{
  float v1 = *(float *)&value1;
  float v2 = *(float *)&value2;
  float ans = v1 - v2;

  return ( *(uint32_t *)&ans );
}

uint64_t FPAbs(uint64_t value, int size)
{
  value = setBits(value,0b0,size-1,size-1);       //set the sign bit to 0 (which means makes it a positive value)
  
  return value;
}

uint32_t FPSqrtSinglePrecision(uint32_t value)
{
  float v1 = *(float *)&value;
  float ans = sqrt(v1);

  return ( *(uint32_t *)&ans );
}


/*
    This function will raise the corresponding FP exceptions
    Once the exception is raised, it is not going to overwrite by 0b0
*/
void setFPException()
{
  int fe = fetestexcept (FE_ALL_EXCEPT);

  if (fe & FE_DIVBYZERO) 
    coreReg[fPSCR] = setBits(coreReg[fPSCR], 0b1, 1, 1);
  if (fe & FE_INEXACT)   
    coreReg[fPSCR] = setBits(coreReg[fPSCR], 0b1, 4, 4);
  if (fe & FE_INVALID)   
    coreReg[fPSCR] = setBits(coreReg[fPSCR], 0b1, 0, 0);
  if (fe & FE_OVERFLOW)  
    coreReg[fPSCR] = setBits(coreReg[fPSCR], 0b1, 2, 2);
  if (fe & FE_UNDERFLOW) 
    coreReg[fPSCR] = setBits(coreReg[fPSCR], 0b1, 3, 3);
}