#include "StatusRegisters.h"
#include <stdio.h>

/*
  This function will initialize all the status register to 0
  
  31 30 29 28 27 26 25 24 23 22 21 20 19 18 17 16 15 14 13 12 11 10 9 8 7 6 5 4 3 2 1 0
 |N |Z |C |V |                           Reserved                                      |
  
  
  [31]	N	
        Negative or less than flag:
                                      1 = result negative
                                      0 = result positive.
        
  [30]	Z	
        Zero flag:
                    1 = result of 0
                    0 = nonzero result.
                    
  [29]	C	
        Carry or borrow flag:
                                1 = carry true or borrow false
                                0 = carry false or borrow true.
                                
  [28]	V	
        Overflow flag:
                        1 = overflow
                        0 = no overflow.
                        
  [27:0]	-	Reserved ( The bits are defined as UNK/SBZP )
          
*/
void initStatusRegister()
{
  StatusRegisters = 0x0000;
    
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

void setNegativeFlag()
{
  StatusRegisters = StatusRegisters | 0x80000000;

}

void setZeroFlag()
{
  StatusRegisters = StatusRegisters | 0x40000000;

}

void setOverflowFlag()
{
  StatusRegisters = StatusRegisters | 0x10000000;;

}
    


