#ifndef InstructionDecoding_H
#define InstructionDecoding_H


#include "getMask.h"

typedef enum { INSTRUCTION32bits, INSTRUCTION16bits} instructionType;


void Instruction_16bits(unsigned int instruction);
void Instruction_32bits(unsigned int instruction);
int is32or16instruction(unsigned int instruction);
unsigned int getBits(unsigned int instruction, int higherRange, int lowerRange);

#endif // InstructionDecoding_H
