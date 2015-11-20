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


#ifndef ARMRegisters_H
#define ARMRegisters_H


#include <stdint.h>

#define NUM_OF_CORE_Register        18  //register start from R0 - R15, R0 to R12 are GPR, R13 is StackPointer, R14 is LinkRegister, R15 is ProgramCounter
#define SP                          13
#define LR                          14
#define PC                          15
#define xPSR                        16
#define fPSCR                       17
#define NUM_OF_FPUD_Register        16
#define NUM_OF_FPUS_Register        32

/*
    Below shows all the registers under the system control block (SCB) registers.
    But not all registers below are implemented for now, only those are which are needed are implemented as for now
    
    0xE000ED00    CPUID    RO     IMPLEMENTATION      CPUID Base Register on page B3-655.
                                    DEFINED

    0xE000ED04    ICSR     RW     0x00000000          Interrupt Control and State Register, ICSR on page B3-655.
    
    0xE000ED08    VTOR     RW     0x00000000a         Vector Table Offset Register, VTOR on page B3-657.
    
    0xE000ED0C    AIRCR    RW       -b                Application Interrupt and Reset Control Register, AIRCR on page B3-658.
    
    0xE000ED10    SCR      RW     0x00000000          System Control Register, SCR on page B3-659.
    
    0xE000ED14    CCR      RW     IMPLEMENTATION      Configuration and Control Register, CCR on page B3-660.
                                    DEFINED

    0xE000ED18    SHPR1    RW     0x00000000          System Handler Priority Register 1, SHPR1 on page B3-662.
    
    0xE000ED1C    SHPR2    RW     0x00000000          System Handler Priority Register 2, SHPR2 on page B3-662.
    
    0xE000ED20    SHPR3    RW     0x00000000          System Handler Priority Register 3, SHPR3 on page B3-663.
    
    0xE000ED24    SHCSR    RW     0x00000000          System Handler Control and State Register, SHCSR on page B3-663.
    
    0xE000ED28    CFSR     RW     0x00000000          Configurable Fault Status Register, CFSR on page B3-665.
                                                      The following describe the subregisters of the CFSR:
                                                        • MemManage Status Register, MMFSR on page B3-666.
                                                        • BusFault Status Register, BFSR on page B3-667.
                                                        • UsageFault Status Register, UFSR on page B3-668.
                                                        
    0xE000ED2C    HFSR     RW     0x00000000          HardFault Status Register, HFSR on page B3-669.
    
    0xE000ED30    DFSR     RW     0x00000000c         Debug Fault Status Register, DFSR on page C1-758.
    
    0xE000ED34    MMFAR    RW      UNKNOWN            MemManage Fault Address Register, MMFAR on page B3-669.
    
    0xE000ED38    BFAR     RW      UNKNOWN            BusFault Address Register, BFAR on page B3-670.
    
    0xE000ED3C    AFSR     RW      UNKNOWN            Auxiliary Fault Status Register, AFSR on page B3-670, IMPLEMENTATION
                                                      DEFINED.
                                                      
    0xE000ED40-     -       -         -               Reserved for CPUID registers, see Chapter B4 The CPUID Scheme.
    0xE000ED84

    0xE000ED88    CPACR    RW     0x00000000          Coprocessor Access Control Register
    
    0xE000EF34    FPCCR    RW     0xC0000000          Floating-point Context Control Register on page 4-49
    
    0xE000EF38    FPCAR    RW         -               Floating-point Context Address Register on page 4-50
    
        -         FPSCR    RW         -               Floating-point Status Control Register on page 4-50
        
    0xE000EF3C    FPDSCR   RW     0x00000000          Floating-point Default Status Control Register on page 4-52
    
    0xE000EF40    MVFR0    RO     0x10110021 or       Media and FP Feature Register 0, MVFR0 on page B4-720
                                  0x10110221b

    0xE000EF44    MVFR1    RO     0x11000011 or       Media and FP Feature Register 1, MVFR1 on page B4-721
                                  0x12000011c

    0xE000EF48    MVFR2    RO     0x00000040 or       Media and FP Feature Register 2, MVFR2 on page B4-722
                                  0x00000000d

    
*/
#define CPACR                       0xE000ED88
#define FPCCR                       0xE000EF34
#define FPCAR                       0xE000EF38
#define FPDSCR                      0xE000EF3C
#define AIRCR                       0xE000ED0C
#define CCR                         0xE000ED14


uint32_t coreReg[NUM_OF_CORE_Register];
uint32_t fpuSinglePrecision[NUM_OF_FPUS_Register];
uint64_t fpuDoublePrecision[NUM_OF_FPUD_Register];


void initCoreRegister();
void writeSinglePrecision(int regNum, uint32_t valueToWrite);
void writeDoublePrecision(int regNum, uint64_t valueToWrite);
void writeToCoreRegisters(int regNum, uint32_t valueToWrite);


#endif // ARMRegisters_H
