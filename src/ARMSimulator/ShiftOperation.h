#ifndef ShiftOperation_H
#define ShiftOperation_H

typedef enum {OMITTED,LSL,LSR,ASR,RRX,ROR}SRType;


#include <stdint.h>

int determineShiftOperation(int shiftType, uint32_t shiftAmount);
uint32_t executeShiftOperation(int shiftType, uint32_t shiftAmount, uint32_t valueToShift, uint32_t S);
uint32_t executeLSR(uint32_t shiftAmount, uint32_t valueToShift, uint32_t S);
uint32_t executeLSL(uint32_t shiftAmount, uint32_t valueToShift, uint32_t S);
uint32_t executeASR(uint32_t shiftAmount, uint32_t valueToShift, uint32_t S);
uint32_t executeROR(uint32_t shiftAmount, uint32_t valueToShift, uint32_t S);
uint32_t executeRRX(uint32_t valueToShift, uint32_t S);

#endif // ShiftOperation_H
