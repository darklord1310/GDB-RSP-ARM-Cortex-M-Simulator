/*  
    Program Name       : GDB RSP and ARM Simulator
    Author             : Wong Yan Yin, Jackson Teh Ka Sing 
    Copyright (C) 2015 TARUC

    This file is part of GDB RSP and ARM Simulator.

    GDB RSP and ARM Simulator is free software, you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    GDB RSP and ARM Simulator is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY, without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with GDB RSP and ARM Simulator.  If not, see <http://www.gnu.org/licenses/>.

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
#include "ADDSPRegister.h"
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
#include "SUBSPRegister.h"
#include "SignedUnsignedLongMultiplyDivide.h"
#include <stdint.h>


void (*Thumb32DataProcessingModifiedImmediate[8192])(uint32_t instruction);
void (*Thumb32DataProcessingPlainImmediate[512])(uint32_t instruction);
void (*Thumb32DataProcessingShiftedRegister[8192])(uint32_t instruction);
void (*Thumb32MoveRegisterAndImmediateShift[128])(uint32_t instruction);
void (*Thumb32DataProcessingRegister[256])(uint32_t instruction);
void (*Thumb32LoadWord[4096])(uint32_t instruction);
void (*Thumb32MultiplyAccumulate[512])(uint32_t instruction);
void (*Thumb32LongMultiplyAccumulateDivide[128])(uint32_t instruction);
void (*Thumb32LoadStoreMultiple[256])(uint32_t instruction);
void (*Thumb32Table[1024])(uint32_t instruction);


void initThumb32bitsDataProcessingModifiedImmediate();
void initThumb32bitsLoadStoreMultiple();
void initThumb32bitsDataProcessingPlainImmediate();
void initThumb32bitsDataProcessingShiftedRegister();
void initThumb32bitsMoveRegisterAndImmediateShift();
void initThumb32bitsDataProcessingRegister();
void initThumb32bitsLoadWord();
void initThumb32bitsMultiplyAccumulate();
void initThumb32bitsLongMultiplyAccumulateDivide();
void initThumb32Table();

void determineMoveRegisterAndImmediateShifts(uint32_t instruction);


#endif // Thumb32bitsTable_H
