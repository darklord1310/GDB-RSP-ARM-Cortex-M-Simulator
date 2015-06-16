#ifndef ARMRegisters_H
#define ARMRegisters_H


#include <stdint.h>

typedef struct CoreRegister CoreRegister;
typedef struct RegisterData RegisterData;


#define numberOfRegister  15         //register start from R0 - R15, R0 to R12 are GPR, R13 is StackPointer, R14 is LinkRegister, R15 is ProgramCounter
#define registerSize      32         //all registers are 32 bits wide

struct RegisterData
{
  uint32_t data;
};


struct CoreRegister
{
  RegisterData *reg;     // pointer to pointer which point to the RegisterData
};


CoreRegister *coreReg;
CoreRegister *initCoreRegister();




#endif // ARMRegisters_H
