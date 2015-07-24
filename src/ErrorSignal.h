#ifndef ErrorSignal_H
#define ErrorSignal_H

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
  NMI,     
  HardFault,    
  MemManage,    
  BusFault,     
  UsageFault,    
  DebugMonitor,    
  SVCall,    
  Interrupt,  
} armException;


#endif // ErrorSignal_H
