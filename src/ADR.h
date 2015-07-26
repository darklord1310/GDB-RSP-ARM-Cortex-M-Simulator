#ifndef ADR_H
#define ADR_H

#include <stdint.h>

void ADRT1(uint32_t instruction);
uint32_t allignPC(uint32_t value, uint32_t allignIndex);
void executeADR(uint32_t Rd, uint32_t immediate);


#endif // ADR_H
