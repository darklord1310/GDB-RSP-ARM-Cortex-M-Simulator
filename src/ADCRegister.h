#ifndef ADCRegister_H
#define ADCRegister_H


#include <stdint.h>


void ADCRegisterT1(uint32_t instruction);
void executeADCRegister(uint32_t Rn, uint32_t Rd, uint32_t Rm, uint32_t S);

#endif // ADCRegister_H
