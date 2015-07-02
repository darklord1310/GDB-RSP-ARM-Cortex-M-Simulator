#include "ConditionalExecution.h"
#include <assert.h>
#include "getAndSetBits.h"
#include "getMask.h"
#include "ARMRegisters.h"
#include "StatusRegisters.h"

/* This function will handle for the conditional execution for thumb instructions
   Eg  if ADDNE, then this function will check if the condition is achieve or not
       if yes, return 1
       if no,  return 0

15 14 13 12 11 10 9 8 7  6  5  4  3 2 1 0
 1  0  1  1  1  1 1 1| firstcond|  mask  |
 
 Input  : cond    is the 4bits of firstcond 

 Return : 1    if condition is met
          0    if condition is not met
*/
int checkCondition(uint32_t cond)
{
  assert(cond<15);
  
  switch(cond)
  {
    case EQ : if( isZero() )
                return 1;
              else
                return 0;
    case NE : if( !isZero() )
                return 1;
              else
                return 0;
    case CS : if( isCarry() )
                return 1;
              else
                return 0;
    case CC : if( !isCarry() )
                return 1;
              else
                return 0;
    case MI : if( isNegative() )
                return 1;
              else
                return 0;
    case PL : if( !isNegative() )
                return 1;
              else
                return 0;
    case VS : if( isOverflow() )
                return 1;
              else
                return 0;
    case VC : if( !isOverflow() )
                return 1;
              else
                return 0;
    case HI : if( isCarry() && !isZero() )
                return 1;
              else
                return 0;
    case LS : if( !isCarry() && isZero() )
                return 1;
              else
                return 0;
    case GE : if( getBits(coreReg[xPSR],31,31) == getBits(coreReg[xPSR],28,28))
                return 1;
              else
                return 0;
    case LT : if( getBits(coreReg[xPSR],31,31) != getBits(coreReg[xPSR],28,28) )
                return 1;
              else
                return 0;
    case GT : if( !isZero() && (getBits(coreReg[xPSR],31,31) == getBits(coreReg[xPSR],28,28) ) )
                return 1;
              else 
                return 0;
    case LE : if( isZero() && (getBits(coreReg[xPSR],31,31) != getBits(coreReg[xPSR],28,28) ) )
                return 1;
              else 
                return 0;
    case AL : return 1;         
  }
  
  
}