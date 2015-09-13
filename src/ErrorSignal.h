/*  
    Program Name       : GDB RSP and ARM Simulator
    Author             : Wong Yan Yin, Jackson Teh Ka Sing 
    Copyright (C) 2015 TARUC

    This file is part of GDB RSP and ARM Simulator.

    GDB RSP and ARM Simulator is free software, you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    GDB RSP and ARM Simulator is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY, without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with GDB RSP and ARM Simulator.  If not, see <http://www.gnu.org/licenses/>.

*/


#ifndef ErrorSignal_H
#define ErrorSignal_H

#include <stdint.h>

typedef enum {
    GDB_SIGNAL_0,       //Signal 0
    GDB_SIGNAL_HUP,     //Hangup
    GDB_SIGNAL_INT,     //Interrupt
    GDB_SIGNAL_QUIT,    //Quit
    GDB_SIGNAL_ILL,     //Illegal instruction
    GDB_SIGNAL_TRAP,    //Trace/breakpoint trap
    GDB_SIGNAL_ABRT,    //Aborted
    GDB_SIGNAL_EMT,     //Emulation trap
    GDB_SIGNAL_FPE,     //Arithmetic exception
    GDB_SIGNAL_KILL     //Killed
} ErrorSignal;

typedef enum {
  Reset,
  Nmi,
  HardFault,
  MemManage,
  BusFault,
  UsageFault,
  DebugMonitor,
  SVCall,
  PendSV,
  SysTick,
  Interrupt,
  Watchpoint_Break
} armException;


#define VECTORTABLE 0x00000000    //default vector table address
#define RESET       0x00000004    //offset for Reset
#define NMI         0x00000008    //offset for NMI
#define HARDFAULT   0x0000000c    //offset for HardFault
#define MEMMANAGE   0x00000010    //offset for MemManage
#define BUSFAULT    0x00000014    //offset for BusFault
#define USAGEFAULT  0x00000018    //offset for UsageFault
#define SVCALL      0x0000002c    //offset for SVCall
#define PENDSV      0x00000038    //offset for PendSV
#define SYSTICK     0x0000003c    //offset for SysTick
#define INTERRUPT   0x0000003c    //offset for Interrupt

uint32_t vectorTable;
void resetVectorTableAddress();
void setTheVectorTableAddress(uint32_t address);
void placePCtoVectorTable(int exceptionReceived);


#endif // ErrorSignal_H
