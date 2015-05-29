#include "ARMRegisters.h"
#include "malloc.h"


CoreRegister *initCoreRegister()
{
	int i;
	
	CoreRegister *coreReg;
	coreReg = malloc(sizeof(CoreRegister));
	coreReg->reg = calloc( numberOfRegister, sizeof(RegisterData));
	
	for(i = 0 ; i < numberOfRegister ; i ++ )
    {
        coreReg->reg[i].data = 0;
    }
	
	return coreReg;
}



void destroyCoreRegister(CoreRegister *reg)
{
    free(reg);
}