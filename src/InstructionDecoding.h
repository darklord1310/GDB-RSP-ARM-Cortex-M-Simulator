#ifndef InstructionDecoding_H
#define InstructionDecoding_H

#include "getBits.h"
#include "getMask.h"
#include <stdint.h>

typedef enum { INSTRUCTION32bits, INSTRUCTION16bits} instructionType;

typedef enum {SHITFADDSUBTRACTMOVECOMPARE, DATAPROCESSING, SPECIALDATAINSTRUCTIONANDBRANCHEXCHANGE,
              LOADFROMLITERALPOOL, LOADORSTORESINGLEDATA, GENERATEPCRELATIVEADDRESS,
              GENERATESPRELATIVEADDRESS, MISCELLANEOUS16BITSINSTRUCTION, STOREMULTIPLEREGISTERS,
              LOADMULTIPLEREGISTERS, CONDITIONALBRANCH, UNCONDITIONALBRANCH} Instruction16bits;

int is32or16instruction(uint32_t instruction);
int Categorize16bitsThumbInstruction(uint32_t instruction);
void ShiftAddSubtractMoveCompare(uint32_t instruction);
void ExecuteInstructionsFrom16bitsCategory(int category, uint32_t instruction);

#endif // InstructionDecoding_H
