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

void (*Thumb16Opcode00XXXX[64])(uint32_t instruction);
void (*Thumb16Opcode010000[16])(uint32_t instruction);
void (*Thumb16Opcode1011XX[128])(uint32_t instruction);


void initThumb16bitsOpcode00XXXX();
void initThumb16bitsOpcode010000();
void initThumb16bitsOpcode1011XX();


#endif // Thumb16bitsTable_H
