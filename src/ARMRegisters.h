#ifndef ARMRegisters_H
#define ARMRegisters_H

typedef struct CoreRegister CoreRegister;
typedef struct RegisterData RegisterData;


#define numberOfRegister 13					//register start from R0 - R12
#define registerSize	 32					//all registers are 32 bits wide

struct RegisterData
{
    int data;
};


struct CoreRegister
{
    RegisterData *reg;     // pointer to pointer which point to the RegisterData
};


CoreRegister *initCoreRegister();




#endif // ARMRegisters_H
