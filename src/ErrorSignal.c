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