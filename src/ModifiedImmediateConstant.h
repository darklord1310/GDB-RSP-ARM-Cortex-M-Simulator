#ifndef ModifiedImmediateConstant_H
#define ModifiedImmediateConstant_H


#include <stdint.h>

unsigned int ModifyControlLessThan4(unsigned int input_value);
unsigned int ModifyControlLessThan6(unsigned int input_value);
unsigned int ModifyControlLessThan8(unsigned int input_value);
unsigned int SetFirstBitAndShiftRight(unsigned int input_value, unsigned int timesOfShifting);
uint32_t ModifyImmediateConstant(uint32_t i, uint32_t imm3, uint32_t bit7, uint32_t input_value);

#endif // ModifiedImmediateConstant_H
