#ifndef ARMRegisters_H
#define ARMRegisters_H


#include <stdint.h>

#define NUM_OF_CORE_Register    18  //register start from R0 - R15, R0 to R12 are GPR, R13 is StackPointer, R14 is LinkRegister, R15 is ProgramCounter
#define SP                      13
#define LR                      14
#define PC                      15
#define xPSR                    16
#define fPSCR                   17
#define NUM_OF_FPUD_Register    16
#define NUM_OF_FPUS_Register    32


uint32_t coreReg[NUM_OF_CORE_Register];
uint32_t fpuSinglePrecision[NUM_OF_FPUS_Register]; 
uint64_t fpuDoublePrecision[NUM_OF_FPUD_Register];


void initCoreRegister();
void writeSinglePrecision(int regNum, uint32_t valueToWrite);
void writeDoublePrecision(int regNum, uint64_t valueToWrite);



#endif // ARMRegisters_H
