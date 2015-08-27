#include "ITandHints.h"
#include <assert.h>
#include "getAndSetBits.h"
#include "getMask.h"
#include "ARMRegisters.h"
#include "StatusRegisters.h"
#include "ConditionalExecution.h"

/*If-Then Encoding T1 
    
    IT{x{y{z}}} <firstcond>       Not allowed in IT block
      
   31 30 29 28 27 26 25 24 23 22 21 20 19 18 17 16 15 14 13 12 11 10 9 8 7 6 5 4 3 2 1 0
  | 1  0  1  1| 1  1  1  1| firstcond |    mask   |                unused               |

where:
        <x>             Specifies the condition for the second instruction in the IT block.
        
        <y>             Specifies the condition for the third instruction in the IT block.
        
        <z>             Specifies the condition for the fourth instruction in the IT block.
        
        <q>             See Standard assembler syntax fields on page A6-7.
        
        <firstcond>     Specifies the condition for the first instruction in the IT block.
                        Each of <x>, <y>, and <z> can be either:
                        
                            T Then. The condition attached to the instruction is <firstcond>.
                            
                            E Else. The condition attached to the instruction is the inverse of <firstcond>. 
                            The condition code is the same as <firstcond>, except that the least significant 
                            bit is inverted. E must not be specified if <firstcond> is AL.
                            
    
    The values of <x>, <y>, and <z> determine the value of the mask field as shown below
                            
    <x>       <y>       <z>             mask[3]           mask[2]             mask[1]           mask[0]
  omitted   omitted   omitted               1               0                   0                 0
     T      omitted   omitted         firstcond[0]          1                   0                 0
     E      omitted   omitted       NOT firstcond[0]        1                   0                 0
     T         T      omitted         firstcond[0]      firstcond[0]            1                 0
     E         T      omitted       NOT firstcond[0]    firstcond[0]            1                 0
     T         E      omitted         firstcond[0]      NOT firstcond[0]        1                 0
     E         E      omitted       NOT firstcond[0]    NOT firstcond[0]        1                 0
     T         T         T            firstcond[0]      firstcond[0]          firstcond[0]        1
     E         T         T          NOT firstcond[0]    firstcond[0]          firstcond[0]        1
     T         E         T            firstcond[0]      NOT firstcond[0]      firstcond[0]        1
     E         E         T          NOT firstcond[0]    NOT firstcond[0]      firstcond[0]        1
     T         T         E            firstcond[0]      firstcond[0]          NOT firstcond[0]    1
     E         T         E          NOT firstcond[0]    firstcond[0]          NOT firstcond[0]    1
     T         E         E            firstcond[0]      NOT firstcond[0]      NOT firstcond[0]    1
     E         E         E          NOT firstcond[0]    NOT firstcond[0]      NOT firstcond[0]    1
     
     
    Shift until the mask[3:0] is 0b0000, then means out of the IT block
*/
void ITandHints(uint32_t instruction)
{
  uint32_t IT7to2 = getBits(instruction,23,18);               //IT[7:2]
  uint32_t IT1to0 = getBits(instruction,17,16);               //IT[1:0]

  coreReg[xPSR] = setBits(coreReg[xPSR], IT7to2, 15, 10);
  coreReg[xPSR] = setBits(coreReg[xPSR], IT1to0, 26, 25);
  
  cond = getITCond();                                         //update the condition
  
  coreReg[PC] += 2;
}