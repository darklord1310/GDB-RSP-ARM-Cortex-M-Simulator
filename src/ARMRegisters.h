#ifndef ARMRegisters_H
#define ARMRegisters_H

typedef struct CoreRegister CoreRegister;
typedef struct RegisterData RegisterData;


#define numberOfRegister 13
#define registerSize	 32

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
