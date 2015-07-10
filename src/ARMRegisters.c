#include "ARMRegisters.h"

/*
  This function will initialize all the R0 to R15 to zero
  R16 is initialized as 0x01000000
  
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
void initCoreRegister()
{
  int i;
  for(i = 0; i < NUM_OF_CORE_Register; i++)
  {
    if(i < 16)
      coreReg[i] = 0;
    else
      coreReg[i] = 0x01000000;
  }
}



