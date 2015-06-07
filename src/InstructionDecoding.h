#ifndef InstructionDecoding_H
#define InstructionDecoding_H

#include "getBits.h"
#include "getMask.h"

typedef enum { INSTRUCTION32bits, INSTRUCTION16bits} instructionType;


int is32or16instruction(unsigned int instruction);


#endif // InstructionDecoding_H
