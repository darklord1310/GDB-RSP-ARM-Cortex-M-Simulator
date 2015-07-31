#ifndef ADR_H
#define ADR_H

#include <stdint.h>

void ADRT1(uint32_t instruction);
void executeADR(uint32_t Rd, uint32_t immediate);
uint32_t alignPC(uint32_t value, uint32_t alignIndex);

#endif // ADR_H
