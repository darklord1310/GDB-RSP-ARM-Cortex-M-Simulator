#include "SVC.h"
#include "ITandHints.h"
#include "StatusRegisters.h"
#include "ARMRegisters.h"
#include "getAndSetBits.h"
#include "getMask.h"
#include "ConditionalExecution.h"
#include "MemoryBlock.h"



/*Supervisor Call 
 * 
    SVC<c> #<imm8>
      
   31 30 29 28 27 26 25 24 23 22 21 20 19 18 17 16 15 14 13 12 11 10 9 8 7 6 5 4 3 2 1 0
  |1  1  0   1| 1  1  1  1|          imm8         |                unused               |

  where:
          <c><q>    See Standard assembler syntax fields on page A6-7.
          
          <imm>     Specifies an 8-bit immediate constant.
          
          
          The pre-UAL syntax SWI<c> is equivalent to SVC<c>.
          
*/
void SVC(uint32_t instruction)
{
  uint32_t imm8 = getBits(instruction,21,19);   
    
  
}