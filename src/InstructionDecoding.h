#ifndef InstructionDecoding_H
#define InstructionDecoding_H

#include "getBits.h"
#include "getMask.h"

typedef enum { INSTRUCTION32bits, INSTRUCTION16bits} instructionType;

typedef enum {SHITFADDSUBTRACTMOVECOMPARE, DATAPROCESSING, SPECIALDATAINSTRUCTIONANDBRANCHEXCHANGE,
              LOADFROMLITERALPOOL, LOADORSTORESINGLEDATA, GENERATEPCRELATIVEADDRESS,
              GENERATESPRELATIVEADDRESS, MISCELLANEOUS16BITSINSTRUCTION, STOREMULTIPLEREGISTERS,
              LOADMULTIPLEREGISTERS, CONDITIONALBRANCH, UNCONDITIONALBRANCH} Instruction16bits;

int is32or16instruction(unsigned int instruction);
void ShiftAddSubctractMoveCompare(unsigned int instruction);
int Categorize16bitsThumbInstruction(unsigned int instruction);


#endif // InstructionDecoding_H
