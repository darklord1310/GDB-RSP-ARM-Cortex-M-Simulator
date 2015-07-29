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
