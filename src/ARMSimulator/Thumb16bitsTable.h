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

#ifndef Thumb16bitsTable_H
#define Thumb16bitsTable_H

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
#include "BKPT.h"


void (*Thumb16Opcode00XXXX[64])(uint32_t instruction);
void (*Thumb16Opcode010000[16])(uint32_t instruction);
void (*Thumb16Opcode1011XX[128])(uint32_t instruction);
void (*Thumb16Opcode010001[16])(uint32_t instruction);
void (*Thumb16LoadStoreSingleData[128])(uint32_t instruction);
void (*Thumb16Opcode1101XX[16])(uint32_t instruction);


void initThumb16bitsOpcode00XXXX();
void initThumb16bitsOpcode010000();
void initThumb16bitsOpcode010001();
void initThumb16bitsOpcode1011XX();
void initThumb16LoadStoreSingleData();
void initThumb16bitsOpcode1101XX();


#endif // Thumb16bitsTable_H
