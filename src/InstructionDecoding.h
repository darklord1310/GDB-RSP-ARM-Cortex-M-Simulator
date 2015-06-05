#ifndef InstructionDecoding_H
#define InstructionDecoding_H


#include "getMask.h"

typedef enum { INSTRUCTION32bits, INSTRUCTION16bits} instructionType;

typedef enum { OP1IS00, OP1IS01, OP1IS10, OP1IS11} Opcode1;

void Instruction_16bits(unsigned int instruction);
void Instruction_32bits(unsigned int instruction);
int is32or16instruction(unsigned int instruction);
unsigned int getBits(unsigned int instruction, int higherRange, int lowerRange);

#endif // InstructionDecoding_H
