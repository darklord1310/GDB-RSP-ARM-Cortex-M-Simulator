#ifndef Relocator_H
#define Relocator_H

#include <stdio.h>

#include "Read_File.h"
#include "elf.h"
#include "ProgramElf.h"
#include "GetHeaders.h"

typedef struct {
  int S;
  int J1;
  int J2;
  int imm10;
  int imm11;
} BlArguments;

//  Relocation infomation
Elf32_Rel *getRelocation(ElfData *dataFromElf);
char *getRelSymbolName(ElfData *dataFromElf, int index);
uint32_t getRelType(ElfData *dataFromElf, int index);

//  Generate and extract the bl arguements from the relocate instruction
uint32_t *generateBLInstruction(ElfData *dataFromElf, char *secNameToRel);
uint32_t extractBlArguments(ElfData *dataFromElf, BlArguments *blArgs);

//  Extract the relocate address and function address
uint32_t extractRelocateAddress(ElfData *elfData);
uint32_t extractFunctionAddress(ElfData *elfData, ElfData *elfData2);

//  Generate the address to link
uint32_t generateAddressToLink(ElfData *elfData, ElfData *elfData2);

// Generate the new instruction from arguments 
uint32_t generateNewInstrFromArgs(ElfData *elfData, ElfData *elfData2, BlArguments *blArgs);

//  To relocate the new instruction in the memory
uint32_t *relocateNewInstruction(ElfData *elfData, ElfData *elfData2, BlArguments *blArgs);

//  To return the new .text section
_Elf32_Shdr *newTextSection(ElfData *elfData, ElfData *elfData2, BlArguments *blArgs);

#endif // Relocator_H
