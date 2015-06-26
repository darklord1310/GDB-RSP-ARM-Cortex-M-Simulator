#ifndef ARMRegisters_H
#define ARMRegisters_H


#include <stdint.h>

#define numberOfRegister  17         //register start from R0 - R15, R0 to R12 are GPR, R13 is StackPointer, R14 is LinkRegister, R15 is ProgramCounter
#define SP                13
#define LR                14
#define PC                15
#define xPSR              16


uint32_t coreReg[numberOfRegister];


void initCoreRegister();




#endif // ARMRegisters_H
