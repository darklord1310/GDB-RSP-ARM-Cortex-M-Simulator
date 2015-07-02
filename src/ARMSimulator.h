#ifndef ARMSimulator_H
#define ARMSimulator_H

#include <stdint.h>

typedef enum { INSTRUCTION32bits, INSTRUCTION16bits} instructionType;

int is32or16instruction(uint32_t instruction);
void Categorize16bitsThumbInstruction(uint32_t instruction);
void initializeAllTable();
void initializeSimulator();
void ARMSimulator(uint32_t instruction);

#endif // ARMSimulator_H
