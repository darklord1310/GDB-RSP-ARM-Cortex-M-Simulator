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


uint32_t FPMulSinglePrecision(uint32_t value1, uint32_t value2, uint32_t FPControl)
{
  FPInfo v1 = FPUnpack(value1, FPControl);
  FPInfo v2 = FPUnpack(value2, FPControl);
  
  float ans = v1.realNumber * v2.realNumber;

  return ( *(uint32_t *)&ans );
}

uint32_t FPDivSinglePrecision(uint32_t value1, uint32_t value2, uint32_t FPControl)
{
  FPInfo v1 = FPUnpack(value1, FPControl);
  FPInfo v2 = FPUnpack(value2, FPControl);
  
  float ans = v1.realNumber / v2.realNumber;

  return ( *(uint32_t *)&ans );
}

uint32_t FPAddSinglePrecision(uint32_t value1, uint32_t value2, uint32_t FPControl)
{
  FPInfo v1 = FPUnpack(value1, FPControl);
  FPInfo v2 = FPUnpack(value2, FPControl);
  
  float ans = v1.realNumber + v2.realNumber;

  return ( *(uint32_t *)&ans );
}

uint32_t FPSubSinglePrecision(uint32_t value1, uint32_t value2, uint32_t FPControl)
{
  FPInfo v1 = FPUnpack(value1, FPControl);
  FPInfo v2 = FPUnpack(value2, FPControl);
  
  float ans = v1.realNumber - v2.realNumber;

  return ( *(uint32_t *)&ans );
}

uint64_t FPAbs(uint64_t value, int size)
{
  value = setBits(value,0b0,size-1,size-1);       //set the sign bit to 0 (which means makes it a positive value)
  
  return value;
}

uint32_t FPSqrtSinglePrecision(uint32_t value, uint32_t FPControl)
{
  FPInfo v1 = FPUnpack(value, FPControl);
  
  float ans = sqrt(v1.realNumber);

  return ( *(uint32_t *)&ans );
}


/*  This function will raise the FPDIVZero exception
 *  FPStatusRegisterSelection      : To select either the FPSCR or FPDSCR is used  
 */
void raiseFPDIVZeroException(uint32_t FPStatusRegisterSelection)
{
  if(FPStatusRegisterSelection == fPSCR)
    coreReg[fPSCR] = setBits(coreReg[fPSCR], 0b1, 1, 1);
  else
    writeSCBRegisters(FPDSCR, setBits(readSCBRegisters(FPDSCR), 0b1, 1, 1));     
}


/*  This function will raise the FPInexact exception
 *  FPStatusRegisterSelection      : To select either the FPSCR or FPDSCR is used  
 */
void raiseFPInexactException(uint32_t FPStatusRegisterSelection)
{
  if(FPStatusRegisterSelection == fPSCR)
    coreReg[fPSCR] = setBits(coreReg[fPSCR], 0b1, 4, 4);
  else
    writeSCBRegisters(FPDSCR, setBits(readSCBRegisters(FPDSCR), 0b1, 4, 4)); 
}


/*  This function will raise the FPInvalid exception
 *  FPStatusRegisterSelection      : To select either the FPSCR or FPDSCR is used  
 */
void raiseFPInvalidException(uint32_t FPStatusRegisterSelection)
{
  if(FPStatusRegisterSelection == fPSCR)
    coreReg[fPSCR] = setBits(coreReg[fPSCR], 0b1, 0, 0);
  else
    writeSCBRegisters(FPDSCR, setBits(readSCBRegisters(FPDSCR), 0b1, 0, 0));  
}


/*  This function will raise the FPOverflow exception
 *  FPStatusRegisterSelection      : To select either the FPSCR or FPDSCR is used  
 */
void raiseFPOverflowException(uint32_t FPStatusRegisterSelection)
{
  if(FPStatusRegisterSelection == fPSCR)
    coreReg[fPSCR] = setBits(coreReg[fPSCR], 0b1, 2, 2);
  else
    writeSCBRegisters(FPDSCR, setBits(readSCBRegisters(FPDSCR), 0b1, 2, 2)); 
}


/*  This function will raise the FPInputDenormalize exception
 *  FPStatusRegisterSelection      : To select either the FPSCR or FPDSCR is used  
 */
void raiseFPInputDenormalizeException(uint32_t FPStatusRegisterSelection)
{
  if(FPStatusRegisterSelection == fPSCR)
    coreReg[fPSCR] = setBits(coreReg[fPSCR], 0b1, 7, 7); 
  else
    writeSCBRegisters(FPDSCR, setBits(readSCBRegisters(FPDSCR), 0b1, 7, 7));
}

/*  This function will raise the FPUnderflow exception
 *  FPStatusRegisterSelection      : To select either the FPSCR or FPDSCR is used  
 */
void raiseFPUnderflowException(uint32_t FPStatusRegisterSelection)
{
  if(FPStatusRegisterSelection == fPSCR)
    coreReg[fPSCR] = setBits(coreReg[fPSCR], 0b1, 3, 3);
  else
    writeSCBRegisters(FPDSCR, setBits(readSCBRegisters(FPDSCR), 0b1, 3, 3)); 
}


void modifyFPSCRorFPDSCR(uint32_t FPControl, uint32_t bitsToSet, int upperLimit, int lowerLimit)
{
  if(fPSCR)
    coreReg[fPSCR] = setBits(coreReg[fPSCR], bitsToSet, upperLimit, lowerLimit);
  else
    writeSCBRegisters(FPDSCR, setBits(readSCBRegisters(FPDSCR), bitsToSet, upperLimit, lowerLimit));
}


uint32_t readFPSCRorFPDSCR(uint32_t FPControl, int upperLimit, int lowerLimit)
{
  if(fPSCR)
    return getBits(coreReg[fPSCR], upperLimit, lowerLimit);
  else
    return getBits(readSCBRegisters(FPDSCR) ,upperLimit, lowerLimit );
}

/*
    This function will raise the corresponding FP exceptions
    Once the exception is raised, it is not going to overwrite by 0b0
*/
void handleFPException()
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


uint32_t FPInfinity(uint32_t signBit, int noOfBits)
{
  uint32_t E,F;
  uint32_t exp,frac,result;
  
  getNumbersOfExponentAndFractionBits(noOfBits, &E, &F);
  
  if(noOfBits == 16)
    result = ( ( (signBit << E) | 0b11111 ) << F );
  else
    result = ( ( (signBit << E) | 0b11111111 ) << F );
  
  return result; 
}


uint32_t FPMaxNormal(uint32_t signBit, int noOfBits)
{
  uint32_t E,F;
  uint32_t exp,frac,result;
  
  getNumbersOfExponentAndFractionBits(noOfBits, &E, &F);
  
  if(noOfBits == 16)
    result = ( ( ( ( (signBit << E-1) | 0b1111 ) << 1 ) | 0b0 ) << F ) | 0b1111111111;
  else
    result = ( ( ( ( (signBit << E-1) | 0b1111111 ) << 1) | 0b0 ) << F ) | 0b11111111111111111111111;
  
  return result;
}


uint32_t FPDefaultNaN(int noOfBits)
{
  uint32_t E,F;
  uint32_t sign,exp,frac,result;
  
  getNumbersOfExponentAndFractionBits(noOfBits, &E, &F);

  sign = 0b0;
  
  if(noOfBits == 16)
    return ( ( (sign << 5) | 0b111111 ) << F-1) ;
  else
    return ( ( (sign << 8) | 0b111111111 ) << F-1) ;
}


uint32_t FPZero(uint32_t sign, int noOfBits)
{
  uint32_t E,F;
  
  getNumbersOfExponentAndFractionBits(noOfBits, &E, &F);

  return ( sign << E+F ) ;
}




uint32_t FPHalfToSingle(uint16_t value, uint32_t FPControl)
{
  uint32_t result;
  FPInfo v1 = FPUnpack(value, FPControl);
  if(v1.type == FPTYPE_SNAN || v1.type == FPTYPE_QNAN)
  {
    if( readFPSCRorFPDSCR(FPControl, 25, 25) == 1)
      result = FPDefaultNaN(32);
    else
      result = ( ( ( (v1.signBit << 9) | 0b111111111 ) << 9) | getBits(value,8,0) ) << 13;
    if(v1.type == FPTYPE_SNAN)
      raiseFPInvalidException(FPControl);      //raise invalid op exception  
  }
  else if(v1.type == FPTYPE_INFINITY)
    result = FPInfinity(v1.signBit,32);
  else if(v1.type == FPTYPE_ZERO)
    result = (v1.signBit) << 31;
  else
    result = FPRound(value, 32, FPControl);
  
  return result;
}



/*
 *  The format is assumed to have an implicit lead bit with value 1 unless the exponent field is stored with all zeros.
 *  Thus only 10 bits of the significand appear in the memory format but the total precision is 11 bits. 
 */
uint16_t FPSingleToHalf(uint32_t value, uint32_t FPControl)
{
  uint16_t result;
  FPInfo v1 = FPUnpack(value, FPControl);

  if (v1.type == FPTYPE_SNAN || v1.type == FPTYPE_QNAN )
  {
    if( readFPSCRorFPDSCR(FPControl, 26, 26) == 1) // AH bit set
      result = v1.signBit << 16;
    else if( readFPSCRorFPDSCR(FPControl, 25, 25) == 1) // DN bit set
      result = FPDefaultNaN(16);
    else
      result = ( ( (v1.signBit << 6) | 0b111111) << 9) | getBits(value,21,13);
    
    if(v1.type == FPTYPE_SNAN || readFPSCRorFPDSCR(FPControl, 26, 26) == 1 ) 
      raiseFPInvalidException(FPControl);
  }
  else if( v1.type == FPTYPE_INFINITY )
  { 
    if( readFPSCRorFPDSCR(FPControl, 26, 26) == 1)    // AH bit set
    {
      result = (v1.signBit << 15) | 0b111111111111111;
      raiseFPInvalidException(FPControl);
    }
    else
      result = FPInfinity(v1.signBit, 16);
  }
  else if(v1.type == FPTYPE_ZERO)
    result = v1.signBit << 15;
  else
    result = FPRound(v1.realNumber, 16, FPControl);
  
  return result;
}



/* This function will compare the 2 values and update the 
   FPSCR accordingly.
   
        Comparison result     N   Z   C   V
              Equal           0   1   1   0
            Less than         1   0   0   0
            Greater than      0   0   1   0
             Unordered        0   0   1   1
             
    Note:
    If instruction is VCMPE, either NaN operand will causes an Invalid Operation exception 
    If instruction is VCMP,  raise Invalid Operation Exception if only either operand is a signaling NaN.
    
*/
void FPCompare(uint32_t value1, uint32_t value2, int compareInstructionType, uint32_t FPControl)
{
  FPInfo v1, v2;

  v1 = FPUnpack(value1, FPControl);
  v2 = FPUnpack(value2, FPControl);
  if(v1.type == FPTYPE_QNAN || v1.type == FPTYPE_SNAN || v2.type == FPTYPE_QNAN || v2.type == FPTYPE_SNAN)
  {
    modifyFPSCRorFPDSCR(FPControl, 0b0011, 31, 28);
    if(v1.type == FPTYPE_SNAN || v2.type == FPTYPE_SNAN || compareInstructionType == VCMPE)
      raiseFPInvalidException(FPControl);
  }
  else
  {
    if(v1.realNumber == v2.realNumber)
      modifyFPSCRorFPDSCR(FPControl, 0b0110, 31, 28);
    else if(v1.realNumber < v2.realNumber)
      modifyFPSCRorFPDSCR(FPControl, 0b1000, 31, 28);
    else
      modifyFPSCRorFPDSCR(FPControl, 0b0010, 31, 28);
  }
}


FPInfo FPUnpack(uint32_t FPValue, uint32_t FPControl)
{
  FPInfo info;
  uint32_t sign;
  uint32_t exp32;
  uint32_t frac32;
  
  sign = getBits(FPValue,31,31);
  exp32 = getBits(FPValue,30,23);
  frac32 = getBits(FPValue,22,0);
  
  if(exp32 == 0)
  {
    if(frac32 == 0 || getBits(FPValue,24,24) == 1)
    {
      info.type = FPTYPE_ZERO;
      info.realNumber = 0.0;
      if(frac32 != 0)
        raiseFPInputDenormalizeException(FPControl);          // Raise Input denormalize exception
    }
    else
    {
      info.type = FPTYPE_NONZERO;
      info.realNumber = *(float *)&FPValue;
    }
  }
  else if(exp32 == 0b11111111)
  {
    if(frac32 == 0)
    {
      info.type = FPTYPE_INFINITY;
      info.realNumber = pow(2.0,1000000);
    }
    else
    {
      if(getBits(frac32,22,22) == 1)
        info.type = FPTYPE_QNAN;
      else
        info.type = FPTYPE_SNAN;
      info.realNumber = 0.0;
    }
  }
  else
  {
    info.type = FPTYPE_NONZERO;
    info.realNumber = *(float *)&FPValue;
  }
  
  info.signBit = sign;
  
  return info;
}



uint32_t FPToFixed(uint32_t value, int M, int fractionBits, int signOrUnsigned, int roundTowardsZero, uint32_t FPControl)
{
  FPInfo v1;
  float intResult, error;
  bool roundUp;
  
  if(roundTowardsZero == 1)
    modifyFPSCRorFPDSCR(FPControl,0b11,23,22);
  
  v1 = FPUnpack(value, FPControl);
  
  if(v1.type == FPTYPE_SNAN || v1.type == FPTYPE_QNAN)
    raiseFPInvalidException(FPControl);
  
  v1.realNumber = v1.realNumber * pow(2,fractionBits);
  intResult = floor(v1.realNumber);
  error = v1.realNumber - intResult;
  
  switch( readFPSCRorFPDSCR(FPControl, 23, 22) )
  {
    case 0b00 : roundUp = (error > 0.5 || (error == 0.5 && getBits( *(uint32_t *)&intResult,0,0) == 1) );
                break;
                  
    case 0b01 : roundUp = (error != 0.0);
                break;
                  
    case 0b10 : roundUp = 0;
                break;
                  
    case 0b11 : roundUp = (error != 0.0 && intResult < 0);
                break;
  }
  
  if(roundUp == true)
    intResult += 1;
  
  
  
}




uint32_t FPRound(float value, uint32_t noOfBits, uint32_t FPControl)
{
  int roundUp, overflowToInf,E,F;
  float mantissa, exponent, biasedExp, intMant, error,minimumExp;
  uint32_t result, valueInUint32, sign;
  valueInUint32 = *(uint32_t *)&value;
  
  getNumbersOfExponentAndFractionBits(noOfBits, &E, &F);
  minimumExp = determineMinimumExp(E);
  getFloatingPointNumberData(value, &sign, &exponent ,&mantissa);

  //deal with flush to zero
  if( readFPSCRorFPDSCR(FPControl, 24, 24) == 1 && (exponent < minimumExp) && noOfBits != 16)
  {
    result = FPZero(sign, noOfBits);
    coreReg[fPSCR] = setBits(coreReg[fPSCR],0b1,3,3);
  }
  else
  {
    if( (exponent - minimumExp + 1) < 0)
      biasedExp = 0;
    else
      biasedExp = exponent - minimumExp + 1;

    if(biasedExp == 0)
      mantissa = mantissa / pow(2, (minimumExp - exponent) );
    
    intMant = floor(mantissa * pow(2,F) );
    error = mantissa * pow(2,F) - intMant;

    if(biasedExp == 0 && (error != 0.0 || readFPSCRorFPDSCR(FPControl, 11, 11) == 1) )
      raiseFPUnderflowException(FPControl);

    switch( readFPSCRorFPDSCR(FPControl, 23, 22) )
    {
      case 0b00 : roundUp = (error > 0.5 || (error == 0.5 && getBits( *(uint32_t *)&intMant,0,0) == 1) );
                  overflowToInf = 1;
                  break;
                  
      case 0b01 : roundUp = (error != 0.0 && sign == 0);
                  overflowToInf = (sign == 0);
                  break;
                  
      case 0b10 : roundUp = (error != 0.0 && sign == 1);
                  overflowToInf = (sign == 1);
                  break;
                  
      case 0b11 : roundUp = 0;
                  overflowToInf = 0;  
                  break;
    }
    printf("roundUp: %x\n", roundUp);
    if(roundUp == 1)
    {
      intMant += 1;
      if(intMant == pow(2,F) )
        biasedExp = 1;
      if(intMant == pow(2,F+1) )
      {
        biasedExp += 1;
        intMant = intMant / 2;
      }
    }
    printf("biasedExp: %f\n", biasedExp);
    printf("intMant: %f\n", intMant);
    if(noOfBits != 16 || readFPSCRorFPDSCR(FPControl, 26, 26) == 0)
    { 
      if(biasedExp >= (pow(2,E) - 1) )
      {
        result = (overflowToInf == 1) ? FPInfinity(sign,noOfBits) : FPMaxNormal(sign,noOfBits);
        raiseFPOverflowException(FPControl);
        error = 1.0;
      }
      else
      {
        uint32_t ex = *(uint32_t *)&biasedExp;
        uint32_t mant = *(uint32_t *)&intMant;
        result = ( ( ( sign << E ) | getBits(ex,E-1,0) ) << F) | getBits(mant,F-1,0);
        // if( getBits(valueInUint32,30,23) )
          // result = setBits( ( ( ( ( (sign) << 5) | getBits(valueInUint32,30,26) ) << 10 ) | getBits(valueInUint32,22,13) ) , 0b1, 0 ,0 );     //set the leading 1
        // else
          // result = ( ( ( (sign) << 5) | getBits(valueInUint32,30,26) ) << 10 ) | getBits(valueInUint32,22,13); 
      }
    }
    else
    {
      if(biasedExp >= pow(2,E-1))
      {
        result = (sign << 15) | 0b111111111111111;
        raiseFPInvalidException(FPControl);
        error = 0.0;
      }
      else
      {
        if( getBits(valueInUint32,30,23) )
          result = setBits( ( ( ( ( (sign) << 5) | getBits(valueInUint32,30,26) ) << 10 ) | getBits(valueInUint32,22,13) ) , 0b1, 0 ,0 );     //set the leading 1
        else
          result = ( ( ( (sign) << 5) | getBits(valueInUint32,30,26) ) << 10 ) | getBits(valueInUint32,22,13); 
      }
    }

    if(error != 0.0)
      raiseFPInexactException(FPControl);
  }

  return result;
}




//this function will return the numbers of exponent and fraction bits based on the
//number of bits passing in
void getNumbersOfExponentAndFractionBits(int noOfBits, int *E, int *F)
{
  if(noOfBits == 16)
    *E = 5;
  else if(noOfBits == 32)
    *E = 8;
  else
    *E = 11;
  
  *F = noOfBits - *E - 1;
}


// return the minimum exponent based on the number of exponent bits passing in
float determineMinimumExp(int E)
{
  return (2 - pow(2,(E-1)) );
}


//get the values of sign, unrounded mantissa and exponent from the float passing in
void getFloatingPointNumberData(float value, uint32_t *sign, float *exponent ,float *mantissa)
{
  if(value < 0.0)
  {
    *sign = 1;
    *mantissa = value * -1;
  }
  else
  {
    *sign = 0;
    *mantissa = value;
  }
  
  *exponent = 0;
  
  while(*mantissa < 1.0)
  {
    *mantissa = *mantissa * 2.0;
    *exponent = *exponent - 1;
  }
  
  while(*mantissa >= 2.0)
  {
    *mantissa = *mantissa / 2.0;
    *exponent = *exponent + 1;
  }
}







