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
