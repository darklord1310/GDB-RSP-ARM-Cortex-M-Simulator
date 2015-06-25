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

void (*Thumb16Opcode00XXXX[64])(uint32_t instruction);


void initThumb16bitsTable();


#endif // Thumb16bitsTable_H
