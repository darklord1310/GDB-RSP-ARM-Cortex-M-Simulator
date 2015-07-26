#include "ErrorSignal.h"
#include "ARMRegisters.h"


/*  This function will set the address of the vector table
 *  according to the address given
 * 
 *  Input: address  is the address of where user want to set the vector table 
 *         default is at 0x00
 * 
 */
void setTheVectorTableAddress(uint32_t address)
{
  vectorTable = address;

}



/*  This function will place the program counter to the vector table
 *  according to the exception
 * 
 *  Input: exceptionReceived  is the exception that it encounters
 * 
 */
void placePCtoVectorTable(int exceptionReceived)
{
  switch(exceptionReceived)
  {
    case Reset     : coreReg[PC] = vectorTable + RESET;  
                     break;
    case Nmi       : coreReg[PC] = vectorTable + NMI;  
                     break;
    case HardFault : coreReg[PC] = vectorTable + HARDFAULT;  
                     break;
    case MemManage : coreReg[PC] = vectorTable + MEMMANAGE;  
                     break;
    case BusFault  : coreReg[PC] = vectorTable + BUSFAULT;  
                     break;
    case UsageFault: coreReg[PC] = vectorTable + USAGEFAULT;  
                     break;
    case SVCall    : coreReg[PC] = vectorTable + SVCALL;  
                     break;
    case PendSV    : coreReg[PC] = vectorTable + PENDSV;  
                     break;
    case SysTick   : coreReg[PC] = vectorTable + SYSTICK;  
                     break;
    case Interrupt : coreReg[PC] = vectorTable + INTERRUPT;  
                     break;
    
  }

}



void resetVectorTableAddress()
{
  vectorTable = VECTORTABLE;
}