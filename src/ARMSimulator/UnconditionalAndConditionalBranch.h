#ifndef UnconditionalAndConditionalBranch_H
#define UnconditionalAndConditionalBranch_H

#include <stdint.h>

void UnconditionalBranchT1(uint32_t instruction);
void ConditionalBranchT1(uint32_t instruction);

uint32_t signExtend(uint32_t value, int numberOfBits);

#endif // UnconditionalAndConditionalBranch_H
