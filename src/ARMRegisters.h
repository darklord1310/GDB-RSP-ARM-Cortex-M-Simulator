#ifndef ARMRegisters_H
#define ARMRegisters_H


#include <stdint.h>

#define NUM_OF_CORE_Register    17  //register start from R0 - R15, R0 to R12 are GPR, R13 is StackPointer, R14 is LinkRegister, R15 is ProgramCounter
#define SP                      13
#define LR                      14
#define PC                      15
#define xPSR                    16
#define NUM_OF_FPU_Register     17
#define fPSCR                   17

uint32_t coreReg[NUM_OF_CORE_Register];
uint64_t fpuReg[NUM_OF_FPU_Register]; 

void initCoreRegister();




#endif // ARMRegisters_H
