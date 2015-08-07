#ifndef ADDSPRegister_H
#define ADDSPRegister_H

#include <stdint.h>


void ADDSPRegisterT1(uint32_t instruction);
void ADDSPRegisterT2(uint32_t instruction);
void executeADDSPRegister(uint32_t Rd, uint32_t Rm, uint32_t S, int shiftOrNoShift);
void ALUWritePC(uint32_t address);


#endif // ADDSPRegister_H
