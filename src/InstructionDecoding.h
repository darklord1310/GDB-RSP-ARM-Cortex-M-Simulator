#ifndef InstructionDecoding_H
#define InstructionDecoding_H

#include "getBits.h"
#include "getMask.h"

typedef enum { INSTRUCTION32bits, INSTRUCTION16bits} instructionType;

typedef enum {SHITFADDSUBTRACTMOVECOMPARE, DATAPROCESSING, SPECIALDATAINSTRUCTIONANDBRANCHEXCHANGE,
              LOADFROMLITERALPOOL, LOADORSTORESINGLEDATA, GENERATEPCRELATIVEADDRESS,
              GENERATESPRELATIVEADDRESS, MISCELLANEOUS16BITSINSTRUCTION, STOREMULTIPLEREGISTERS,
              LOADMULTIPLEREGISTERS, CONDITIONALBRANCH, UNCONDITIONALBRANCH} Instruction16bits;

typedef enum { IMMEDIATE, REGISTER} ImmediateOrRegister;

int is32or16instruction(unsigned int instruction);
int Categorize16bitsThumbInstruction(unsigned int instruction);
void ShiftAddSubtractMoveCompare(unsigned int instruction);
void ExecuteInstructionsFrom16bitsCategory(int category, unsigned int instruction);

#endif // InstructionDecoding_H
