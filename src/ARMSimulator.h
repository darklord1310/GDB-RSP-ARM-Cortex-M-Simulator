#ifndef ARMSimulator_H
#define ARMSimulator_H

#include "getBits.h"
#include "getMask.h"
#include <stdint.h>
#include "StatusRegisters.h"
#include "ARMRegisters.h"
#include "Thumb16bitsTable.h"

typedef enum { INSTRUCTION32bits, INSTRUCTION16bits} instructionType;

int is32or16instruction(uint32_t instruction);
void Categorize16bitsThumbInstruction(uint32_t instruction);

#endif // ARMSimulator_H
