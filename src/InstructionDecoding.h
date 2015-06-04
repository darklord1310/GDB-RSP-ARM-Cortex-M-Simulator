#ifndef InstructionDecoding_H
#define InstructionDecoding_H


#include "MOV_instruction.h"

typedef enum { bit_32, bit_16} instructionType;


void Instruction_16bits(unsigned int instruction);
void Instruction_32bits(unsigned int instruction);
int is32or16instruction(unsigned int instruction);
unsigned int getFirst3BitsFromInstruction(unsigned int instruction);
unsigned int getFirst4BitsFromInstruction(unsigned int instruction);
unsigned int getFirst5BitsFromInstruction(unsigned int instruction);
unsigned int getFirst6BitsFromInstruction(unsigned int instruction);
unsigned int getFirstFewBitsFromInstruction(unsigned int instruction, int getUntil);

#endif // InstructionDecoding_H
