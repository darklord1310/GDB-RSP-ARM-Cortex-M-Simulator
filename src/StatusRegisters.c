#include "StatusRegisters.h"
#include <stdio.h>
#include <assert.h>

/*
  This function will initialize all the status register to 0
  
  31 30 29 28 27 26  25 24 23 22 21 20 19 18 17 16 15 14 13 12 11 10 9 8 7 6 5 4 3 2 1 0
 |N |Z |C |V |Q|IT[1:0]|T|  Reserved  |  GE[3:0]  |      IT[7:2]    |      Reserved     |                             
  
  [31]	N	
        Negative or less than flag:
                                      1 = result negative
                                      0 = result positive.
        
  [30]	Z	
        Zero flag:
                    1 = result of 0
                    0 = nonzero result.
                    
  [29]	C	(unsigned overflow)
        Carry or borrow flag:
                                1 = carry true or borrow false
                                0 = carry false or borrow true.
                                
  [28]	V	(signed overflow)
        Overflow flag:
                        1 = overflow
                        0 = no overflow.
                        
  [24]  T     indicator to show whether in ARM/Thumb state, 1 for Thumb, 0 for ARM
  
  IT[7:5]     encodes the base condition (that is, the top 3 bits of the condition specified by the IT instruction) for
              the current IT block, if any. It contains 0b000 when no IT block is active.
              
  IT[4:0]     encodes the number of instructions that are due to be conditionally executed, and whether the
              condition for each is the base condition code or the inverse of the base condition code.
              It contains 0b00000 when no IT block is active.

*/
void initStatusRegister()
{
  StatusRegisters = 0x01000000;              //the T bits is set to 1 because we are always in Thumb state
  
}

int inITBlock()
{
  uint32_t IT26to25 = getBits(StatusRegisters, 26,25);
  uint32_t IT15to10 = getBits(StatusRegisters, 15,10);
  if(IT15to10 == 0 && IT26to25 == 0)            //outside IT block
    return 0;
  else
    return 1;
}

bool isNegative()
{
  if( getBits(StatusRegisters, 31, 31) )
    return true;
  else
    return false;
}

bool isZero()
{
  if( getBits(StatusRegisters, 30, 30) )
    return true;
  else
    return false;
}

bool isCarry()
{
  if( getBits(StatusRegisters, 29, 29) )
    return true;
  else
    return false;
}

bool isOverflow()
{
  if( getBits(StatusRegisters, 28, 28) )
    return true;
  else
    return false;
}

void setCarryFlag()
{
  StatusRegisters = StatusRegisters | 0x20000000;
}

void resetCarryFlag()
{
  StatusRegisters = StatusRegisters & 0xdfffffff;
}

void setNegativeFlag()
{
  StatusRegisters = StatusRegisters | 0x80000000;

}

void resetNegativeFlag()
{
  StatusRegisters = StatusRegisters & 0x7fffffff;
}

void setZeroFlag()
{
  StatusRegisters = StatusRegisters | 0x40000000;

}

void resetZeroFlag()
{
  StatusRegisters = StatusRegisters & 0xbfffffff;
}

void setOverflowFlag()
{
  StatusRegisters = StatusRegisters | 0x10000000;

}

void resetOverflowFlag()
{
  StatusRegisters = StatusRegisters & 0xefffffff;
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

/* This will update the carry flag based on the addition result
   of value1 and value2

*/
void updateCarryFlagAddition(uint32_t value1, uint32_t value2)
{
  int bit0 = 0, intermediateCarry = 0, i,adder;
  
  for(i = 0; i < 32; i++)
  {
    adder = intermediateCarry + getBits(value1,bit0,bit0) + getBits(value2,bit0,bit0);
    if(adder >= 2)
      intermediateCarry = 1;
    else
      intermediateCarry = 0;
    bit0++;
  }

  if( intermediateCarry == 1)
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





