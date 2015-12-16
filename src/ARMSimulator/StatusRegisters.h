/*  
    GDB RSP and ARM Simulator

    Copyright (C) 2015 Wong Yan Yin, <jet_wong@hotmail.com>,
    Jackson Teh Ka Sing, <jackson_dmc69@hotmail.com>

    This file is part of GDB RSP and ARM Simulator.

    This program is free software, you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY, without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with This program.  If not, see <http://www.gnu.org/licenses/>.
*/


#ifndef StatusRegisters_H
#define StatusRegisters_H

#define OVERFLOW_FLAG_POS 28
#define maskOffBit(target, bitNo) (target & ~(1 << bitNo))
#define shiftRightMsbBitToBitPosition(value, pos) (((value) & 0x80000000) >> (31 - pos))                         
                                          
#define setOverflow(x) (coreReg[xPSR] = ( maskOffBit(coreReg[xPSR], OVERFLOW_FLAG_POS) | (shiftRightMsbBitToBitPosition(x, OVERFLOW_FLAG_POS)) )  )

#define updateOverflowFlag4Addition(signForValue1,signForValue2,signForResult) (setOverflow(~(signForValue1 ^ signForValue2) | signForResult)


#define updateOverflowFlag4Subtraction(signForValue1,signForValue2,signForResult) (setOverflow((signForValue1 ^ signForValue2) | signForResult)
                  
#include <stdbool.h>
#include <stdint.h>
#include <math.h>
#include "SaturateOperation.h"
#include "fenv.h"
#pragma STDC FENV_ACCESS on


typedef enum {FPTYPE_NONZERO, FPTYPE_ZERO, FPTYPE_INFINITY, FPTYPE_QNAN, FPTYPE_SNAN} FPType;
typedef enum {VCMP, VCMPE} compareType;
typedef struct FPInfo FPInfo;

struct FPInfo
{
  FPType type;
  uint32_t signBit;
  float realNumber;
};


bool isNegative();
bool isZero();
bool isCarry();
bool isOverflow();
bool isQSet();
void setQFlag();
void setOverflowFlag();
void setZeroFlag();
void setNegativeFlag();
void setCarryFlag();
void resetOverflowFlag();
void resetCarryFlag();
void resetNegativeFlag();
void resetZeroFlag();
void updateZeroFlag(uint32_t value);
void updateNegativeFlag(uint32_t value);
void updateCarryFlagAddition(uint32_t value1, uint32_t value2);
void updateCarryFlagSubtraction(uint32_t value1, uint32_t value2);
void updateOverflowFlagAddition(uint32_t value1, uint32_t value2, uint32_t result);
void updateOverflowFlagSubtraction(uint32_t value1, uint32_t value2, uint32_t result);
void updateQFlag(int32_t max, int32_t min, int32_t result, int32_t sign);
int  bigEndian();
int inITBlock();
uint32_t getITCond();
void shiftITState();
int isLastInITBlock();
void executeFPUChecking();
uint32_t determineRegisterBasedOnSZ(uint32_t registerName, uint32_t Vx, uint32_t dpOperation);
uint64_t FPNeg(uint64_t value, int size);
uint64_t FPAbs(uint64_t value, int size);
uint32_t FPMulSinglePrecision(uint32_t value1, uint32_t value2, uint32_t FPControl);
uint32_t FPDivSinglePrecision(uint32_t value1, uint32_t value2, uint32_t FPControl);
uint32_t FPAddSinglePrecision(uint32_t value1, uint32_t value2, uint32_t FPControl);
uint32_t FPSubSinglePrecision(uint32_t value1, uint32_t value2, uint32_t FPControl);
uint32_t FPSqrtSinglePrecision(uint32_t value, uint32_t FPControl);
uint32_t FPHalfToSingle(uint16_t value, uint32_t FPControl);
uint16_t FPSingleToHalf(uint32_t value, uint32_t FPControl);
uint32_t FPMaxNormal(uint32_t signBit, int noOfBits);
uint32_t FPInfinity(uint32_t signBit, int noOfBits);
uint32_t FPZero(uint32_t sign, int noOfBits);
uint32_t FPDefaultNaN(int noOfBits);
uint32_t FPProcessNaN(FPType type, uint32_t operand, uint32_t FPControl);
uint32_t FPProcessNaNs(FPType type1, FPType type2, uint32_t v1, uint32_t v2, uint32_t FPControl, bool *done);
FPInfo FPUnpack(uint32_t FPValue, uint32_t FPControl, uint32_t noOfBits);
uint32_t FPRound(float value, uint32_t noOfBits, uint32_t FPControl);
void FPCompare(uint32_t value1, uint32_t value2, int compareInstructionType, uint32_t FPControl);
void raiseFPUnderflowException(uint32_t FPStatusRegisterSelection);
void raiseFPDIVZeroException(uint32_t FPStatusRegisterSelection);
void raiseFPInexactException(uint32_t FPStatusRegisterSelection);
void raiseFPInvalidException(uint32_t FPStatusRegisterSelection);
void raiseFPOverflowException(uint32_t FPStatusRegisterSelection);
void raiseFPInputDenormalizeException(uint32_t FPStatusRegisterSelection);
uint32_t readFPSCRorFPDSCR(uint32_t FPControl, int upperLimit, int lowerLimit);
void modifyFPSCRorFPDSCR(uint32_t FPControl, uint32_t bitsToSet, int upperLimit, int lowerLimit);
void getNumbersOfExponentAndFractionBits(int noOfBits, int *E, int *F);
int determineMinimumExp(int E);
void getFloatingPointNumberData(float value, uint32_t *sign, uint32_t *exponent ,double *mantissa);
void unpackFloatData(uint32_t value, uint32_t *sign, uint32_t *exp, uint32_t *frac, uint32_t noOfBits);
uint32_t FixedToFP(uint32_t value, uint32_t N, int fractionBits, bool signOrUnsigned, bool roundToNearest, uint32_t FPControl);
uint32_t FPToFixed(uint32_t value, uint32_t M, int fractionBits, bool signOrUnsigned, bool roundTowardsZero, uint32_t FPControl);
void selectRoundingMethodAccordingly(uint32_t FPControl);


#endif // StatusRegisters_H
