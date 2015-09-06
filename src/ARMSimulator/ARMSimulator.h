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
void executeDataProcessingModifiedImmediate(uint32_t instruction);
void executeDataProcessingPlainImmediate(uint32_t instruction);
void executeDataProcessingShiftedRegister(uint32_t instruction);
void executeLoadWord(uint32_t instruction);
void executeMultiplyAccumulate(uint32_t instruction);
void executeLongMultiplyAccumulateDivide(uint32_t instruction);

#endif // ARMSimulator_H
