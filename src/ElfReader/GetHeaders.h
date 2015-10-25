#ifndef Get_File_Header_H
#define Get_File_Header_H

#include <stdio.h>
#include <string.h>
#include <malloc.h>

#include "Read_File.h"
#include "elf.h"
#include "ProgramElf.h"

typedef struct {
  InStream *myFile;
  Elf32_Ehdr *eh;
  Elf32_Shdr *sh;
  Elf32_Phdr *ph;
  _Elf32_Shdr *programElf;
  Elf32_Sym *st;
  Elf32_Rel *rel;
  uint32_t *sectionAddress;
  uint32_t *targetAddr;
} ElfData;

typedef struct {
  int index;
  int size;
  uint8_t *dataAddress;
  uint32_t destAddress;
} ElfSection;

typedef enum {
  FILE_CLOSED = 0,
  FILE_OPENED
} File_Status;

extern ElfData *elfData;
extern ElfSection *isr, *text, *initArray, *rodata, *data, *finiArray;
extern uint32_t entryAddress;
extern int fileStatus;

// File Header
Elf32_Ehdr *getElfHeader(ElfData *elfData);

// Program Header
Elf32_Phdr *getProgramHeaders(ElfData *elfData);

// Section Header
Elf32_Shdr *getSectionHeaders(ElfData *elfData);

// Symbol Table
Elf32_Sym *getSymbolTables(ElfData *elfData);

// Section info and Name
char *getSectionInfoNameUsingIndex(ElfData *elfData, int index);
uint32_t *getSectionInfoUsingIndex(ElfData *elfData, int index);
_Elf32_Shdr *getAllSectionInfo(ElfData *elfData);

// ElfData initialization with file directory
ElfData *openElfFile(char *fileName);

//  Section Header Addr
uint32_t getSectionHeaderAddrUsingIndex(ElfData *elfData, int index);

//  Index, Address and Size of section
int getIndexOfSectionByName(ElfData *elfData, char *name);
uint32_t getSectionAddress(ElfData *elfData, int index);
int getSectionSize(ElfData *elfData, int index);

//  Physical and Virtual Address of Program Headers
uint32_t getSectionPhysicalAddress(ElfData *elfData, int index);
uint32_t getSectionVirtualAddress(ElfData *elfData, int index);

//  Status check for Executable, Writeable and Readable
int isSectionExecutable(ElfData *elfData, int index);
int isSectionWriteable(ElfData *elfData, int index);
int isSectionReadable(ElfData *elfData, int index);

//  Entries of Symbol Table
int getSymbolTableEntries(ElfData *elfData);

//  Symbol Table Size and Address from Name
uint32_t getSymbolTableSizeUsingName(ElfData *elfData, char *name);
uint32_t getSymbolTableAddressUsingName(ElfData *elfData, char *name);

//  Name of Symbol Table
char *getSymbolTableNameUsingIndex(ElfData *elfData, int index);

ElfSection *getElfSectionInfo(ElfData *elfData, char *section);
void getElfSection(char *elfFile);
int getProgramSize(char *elfFile);

void closeElfData(ElfData *elfData);
void closeElfSection(ElfSection *elfSection);
void closeElfFile(void);
#endif // Get_File_Header_H

