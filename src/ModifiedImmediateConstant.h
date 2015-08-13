#ifndef ModifiedImmediateConstant_H
#define ModifiedImmediateConstant_H


#include <stdint.h>

unsigned int ModifyControlLessThan4(unsigned int input_value);
unsigned int ModifyControlLessThan6(unsigned int input_value);
unsigned int ModifyControlLessThan8(unsigned int input_value);
unsigned int SetFirstBitAndShiftRight(unsigned int input_value, unsigned int timesOfShifting);
uint32_t ModifyImmediateConstant(uint32_t ModifyControl, uint32_t input_value, uint32_t affectCarry);

#endif // ModifiedImmediateConstant_H
