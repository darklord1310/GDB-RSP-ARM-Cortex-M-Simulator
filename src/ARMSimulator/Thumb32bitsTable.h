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


#ifndef Thumb32bitsTable_H
#define Thumb32bitsTable_H

#include <stdint.h>
#include "LSLImmediate.h"
#include "LSRImmediate.h"
#include "ASRImmediate.h"
#include "MOVImmediate.h"
#include "CMPImmediate.h"
#include "ADDImmediate.h"
#include "SUBImmediate.h"
#include "ADDRegister.h"
#include "SUBRegister.h"
#include "ITandHints.h"
#include "ANDRegister.h"
#include "LSLRegister.h"
#include "LSRRegister.h"
#include "ASRRegister.h"
#include "CMPRegister.h"
#include "CMNRegister.h"
#include "EORRegister.h"
#include "ORRRegister.h"
#include "RORRegister.h"
#include "MVNRegister.h"
#include "BICRegister.h"
#include "ADCRegister.h"
#include "BX.h"
#include "BLXRegister.h"
#include "MOVRegister.h"
#include "CMPRegister.h"
#include "MULRegister.h"
#include "TSTRegister.h"
#include "RSBImmediate.h"
#include "SBCRegister.h"
#include "UnconditionalAndConditionalBranch.h"
#include "STRRegister.h"
#include "LDRImmediate.h"
#include "SVC.h"
#include "STRImmediate.h"
#include "LDRRegister.h"
#include "ADDSPImmediate.h"
#include "REV.h"
#include "SignedAndUnsignedExtend.h"
#include "CBZandCBNZ.h"
#include "PUSH.h"
#include "POP.h"
#include "SUBSPImmediate.h"
#include "ShiftOperation.h"
#include "ANDImmediate.h"
#include "TSTImmediate.h"
#include "BICImmediate.h"
#include "ORRImmediate.h"
#include "ORNImmediate.h"
#include "MVNImmediate.h"
#include "EORImmediate.h"
#include "TEQImmediate.h"
#include "CMNImmediate.h"
#include "ADCImmediate.h"
#include "SBCImmediate.h"
#include "ADR.h"
#include "ARMSimulator.h"
#include "LDRLiteral.h"
#include "getMask.h"
#include "getAndSetBits.h"
#include "MLA.h"
#include "MLS.h"
#include "MOVT.h"
#include "SignedAndUnsignedSaturate.h"
#include "SignedAndUnsignedBitFieldExtract.h"
#include "BFIandBFC.h"
#include "RRX.h"
#include "RORImmediate.h"
#include "ORNRegister.h"
#include "TEQRegister.h"
#include "RSBRegister.h"
#include "CLZ.h"
#include "BL.h"
#include "NOP.h"
#include "SignedUnsignedLongMultiplyDivide.h"
#include "VMOV.h"
#include "VMSR.h"
#include "VMRS.h"
#include "VMLAandVMLS.h"
#include "VMUL.h"
#include "VNMLAandVNMLSandVNMUL.h"
#include "VSTM.h"
#include "VSTR.h"
#include "VPUSH.h"
#include "VLDM.h"
#include "VLDR.h"
#include "VPOP.h"
#include "VNEG.h"
#include "VCMP.h"
#include "VABS.h"
#include "VCVT.h"
#include "VSQRT.h"
#include <stdint.h>

typedef struct BitsInfo_t BitsInfo;
typedef struct TableException TableException;

struct BitsInfo_t 
{
  uint32_t noOfDontCareBits;
  uint32_t baseOpcode;
  uint32_t PositionOfbitX[32];
};

struct TableException
{
  uint32_t mask;
  uint32_t exceptionValue;
  
};

#define NO_EXCEPTION 0
#define MAXIMUM_NO_OF_TABLE_EXCEPTIONS 31

typedef enum {INSTRUCTION_OCCUPIED} tabulatingError;


void findBaseOpcode(char *string, BitsInfo *bitsInfo);
void getBitsInfo(char *string, BitsInfo *bitsInfo);
TableException *createTableException(int numberOfExceptions, ...);
void tabulateTable(char *string, void (*table[])(uint32_t), void (*function)(uint32_t) , TableException *tableException);
int determineTableException(TableException *tableException, uint32_t opcode);


void (*Thumb32DataProcessingModifiedImmediate[8192])(uint32_t instruction);
void (*Thumb32DataProcessingPlainImmediate[512])(uint32_t instruction);
void (*Thumb32DataProcessingShiftedRegister[8192])(uint32_t instruction);
void (*Thumb32MoveRegisterAndImmediateShift[128])(uint32_t instruction);
void (*Thumb32DataProcessingRegister[256])(uint32_t instruction);
void (*Thumb32BranchesAndMiscellaneousControl[1024])(uint32_t instruction);
void (*Thumb32HintInstructions[2048])(uint32_t instruction);
void (*Thumb32LoadWord[4096])(uint32_t instruction);
void (*Thumb32MultiplyAccumulate[512])(uint32_t instruction);
void (*Thumb32LongMultiplyAccumulateDivide[128])(uint32_t instruction);
void (*Thumb32LoadStoreMultiple[256])(uint32_t instruction);
void (*Thumb32StoreSingleDataItem[512])(uint32_t instruction);
void (*Thumb32LoadByteMemoryHints[65536])(uint32_t instruction);
void (*Thumb32LoadStoreDualTableBranch[256])(uint32_t instruction);
void (*Thumb32LoadHalfword[65536])(uint32_t instruction);
void (*Thumb32CoprocessorInstructions[65536])(uint32_t instruction);
void (*Thumb32CoprocessorInstructions2[65536])(uint32_t instruction);
void (*FloatingPoint32bitsTransfer[128])(uint32_t instruction);
void (*FloatingPointDataProcessing[2048])(uint32_t instruction);
void (*FloatingPointLoadStore[512])(uint32_t instruction);
void (*Thumb32Table[2048])(uint32_t instruction);


void initThumb32bitsDataProcessingModifiedImmediate();
void initThumb32bitsLoadStoreMultiple();
void initThumb32bitsDataProcessingPlainImmediate();
void initThumb32bitsDataProcessingShiftedRegister();
void initThumb32bitsMoveRegisterAndImmediateShift();
void initThumb32bitsDataProcessingRegister();
void initThumb32bitsBranchesAndMiscellaneousControl();
void initThumb32bitsHintInstructions();
void initThumb32bitsLoadWord();
void initThumb32bitsMultiplyAccumulate();
void initThumb32bitsLongMultiplyAccumulateDivide();
void initThumb32StoreSingleDataItem();
void initThumb32LoadByteMemoryHints();
void initThumb32bitsLoadStoreDualTableBranch();
void initThumb32bitsLoadHalfword();
void initThumb32bitsCoprocessorInstructions();
void initThumb32bitsCoprocessorInstructions2();
void initFloatingPoint32bitsTransfer();
void initFloatingPoint32DataProcessing();
void initFloatingPoint32FPLoadStore();
void initThumb32Table();

void determineMoveRegisterAndImmediateShifts(uint32_t instruction);


#endif // Thumb32bitsTable_H
