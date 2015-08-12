#ifndef ARMSimulator_H
#define ARMSimulator_H

#include <stdint.h>

typedef enum { INSTRUCTION32bits, INSTRUCTION16bits} instructionType;

int is32or16instruction(uint32_t instruction);
void executeInstructionFrom16bitsTable(uint32_t opcode1, uint32_t instruction);
void armSimulate16(uint32_t instruction);
void armSimulate32(uint32_t instruction);
void initializeAllTable();
void initializeSimulator();
void ARMSimulator(uint32_t instruction);
void armStep();
uint32_t retrieveInstructionFromMemory();
void writeInstructionToMemoryGivenByAddress(uint32_t instruction, uint32_t address);


#endif // ARMSimulator_H
