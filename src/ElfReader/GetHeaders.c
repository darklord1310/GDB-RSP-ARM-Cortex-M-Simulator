#include "ProgramElf.h"
#include "GetHeaders.h"
#include "Relocator.h"
#include "Read_File.h"
#include "elf.h"
#include "CException.h"
#include "ErrorCode.h"

ElfData *elfData;
ElfSection *isr, *text, *initArray, *rodata, *data, *finiArray;
uint32_t entryAddress = 0;
int fileStatus = FILE_CLOSED;

/******************************************************************************
 * ELF Header
 *
 *  Operation:
 *          To read the information in the ELF Header
 *
 *  Input:
 *          elfData(ElfData structure)
 *
 *  Data:
 *          Information of the ELF Header allocate in the structure
 *          of Elf32_Ehdr
 *
 *  Return:
 *          elfData->eh
 *          (The structure of Elf32_Ehdr with information of the ELF Header)
 *
 ******************************************************************************/
Elf32_Ehdr *getElfHeader(ElfData *elfData){
  elfData->eh = malloc(sizeof(Elf32_Ehdr));

  fread(elfData->eh, sizeof(Elf32_Ehdr), 1, elfData->myFile->file);

  return elfData->eh;
}

/******************************************************************************
 * Program Header
 *
 *  Operation:
 *          To read the information in the Program Header by moving the file
 *          pointer to the e_phoff(Program_Header_Offset) in the Elf32_Ehdr
 *
 *  Input:
 *          elfData(ElfData structure)
 *
 *  Data:
 *          Information of the Program Header allocate in the structure
 *          of Elf32_Phdr
 *
 *  Return:
 *          elfData->ph
 *          (The structure of Elf32_Phdr with information of the Program Header)
 *
 ******************************************************************************/
Elf32_Phdr *getProgramHeaders(ElfData *elfData){
  int phSizeToMalloc = sizeof(Elf32_Phdr) * (elfData->eh->e_phnum);
  elfData->ph = malloc(phSizeToMalloc);

  inStreamMoveFilePtr(elfData->myFile, elfData->eh->e_phoff);
  fread(elfData->ph, phSizeToMalloc, 1, elfData->myFile->file);

  /* int i;

  printf("\nProgram Headers\n");
  for(i = 0; i < elfData->eh->e_phnum; i++)
  {
    printf("%10x%10x%8x\n", elfData->ph[i].p_vaddr,  \
                            elfData->ph[i].p_paddr,  \
                            elfData->ph[i].p_filesz);
  } */

  return elfData->ph;
}

/******************************************************************************
 * Section Header
 *
 *  Operation:
 *          To read the information in the Section Header by moving the file
 *          pointer to the e_shoff(Section_Header_Offset) in the Elf32_Ehdr
 *
 *  Input:
 *          elfData(ElfData structure)
 *  Data:
 *          Information of the Section Header allocate in the structure
 *          of Elf32_Shdr
 *
 *  Return:
 *          elfData->sh
 *          (The structure of Elf32_Shdr with information of the Section Header)
 *
 ******************************************************************************/
Elf32_Shdr *getSectionHeaders(ElfData *elfData){
  int shSizeToMalloc = sizeof(Elf32_Shdr) * (elfData->eh->e_shnum);
  elfData->sh = malloc(shSizeToMalloc);

  inStreamMoveFilePtr(elfData->myFile, elfData->eh->e_shoff);
  fread(elfData->sh, shSizeToMalloc, 1, elfData->myFile->file);

  /* int i;

  printf("Section Headers\n");
  for(i = 0; i < elfData->eh->e_shnum; i++)
  {
    printf("%10x%10x%10x%15d%10x%10x\n", elfData->sh[i].sh_addr,  \
                                         elfData->sh[i].sh_size,  \
                                         elfData->sh[i].sh_offset,\
                                         elfData->sh[i].sh_type,  \
                                         elfData->sh[i].sh_link,  \
                                         elfData->sh[i].sh_info,  \
                                         elfData->sh[i].sh_info,  \
                                         elfData->sh[i].sh_info,  \
                                         elfData->sh[i].sh_info   \
                                         );
  } */

  return elfData->sh;
}

/******************************************************************************
 * Symbol Tables
 *
 *  Operation:
 *          To read the information in the Symbol Table by moving the file
 *          pointer to the sh_offset(Symbol_Table_Offset) in the Elf32_Shdr
 *
 *  Input:
 *          elfData(ElfData structure)
 *
 *  Data:
 *          Information of the Symbol Table allocate in the structure
 *          of Elf32_Sym
 *
 *  Return:
 *          elfData->st
 *          (The structure of Elf32_Sym with information of the Symbol Table)
 *
 ******************************************************************************/
Elf32_Sym *getSymbolTables(ElfData *elfData){
  int i, totalSymTab, entriesOfSymTab;

  for(i = 0; elfData->sh[i].sh_type != SHT_SYMTAB; i++);
  totalSymTab = elfData->sh[i+1].sh_offset - elfData->sh[i].sh_offset;
  elfData->st = malloc(totalSymTab);

  inStreamMoveFilePtr(elfData->myFile, elfData->sh[i].sh_offset);
  fread(elfData->st, totalSymTab, 1, elfData->myFile->file);

  return elfData->st;
}

/******************************************************************************
 * Get Section Info Name Using Index
 *
 *  Operation:
 *          To read the information of name in the section header by moving
 *          the file pointer to the sh_offset(Symbol_Table_Offset) of String
 *          Table add with sh[index].sh_name in the Elf32_Shdr. Index is the
 *          index for Section Header
 *
 *  Input:
 *          elfData(ElfData structure)
 *          index(Section index)
 *
 *  Data:
 *          Information of the Section Name allocate with the size of String
 *          Table type in the Section Header
 *
 *  Return:
 *          names
 *
 ******************************************************************************/
char *getSectionInfoNameUsingIndex(ElfData *elfData, int index){
  char *names;
  int i;

  for(i = 0; elfData->sh[i].sh_type != SHT_STRTAB; i++);
  names= malloc(elfData->sh[i].sh_size);

  inStreamMoveFilePtr(elfData->myFile, elfData->sh[i].sh_offset + elfData->sh[index].sh_name);
  fread(names, elfData->sh[i].sh_size, 1, elfData->myFile->file);

  return names;
}

/******************************************************************************
 * Get Section Info Using Index
 *
 *  Operation:
 *          To read the information of section in the section header by moving
 *          the file pointer to the sh[index].sh_offset(Symbol_Table_Offset)
 *          in the Elf32_Shdr. Index is the index for Section Header
 *
 *  Input:
 *          elfData(ElfData structure)
 *          index(Section index)
 *
 *  Data:
 *          Information of the Section allocate with the size of String
 *          Table type in the Section Header
 *
 *  Return:
 *          sectInfo
 *
 ******************************************************************************/
uint32_t *getSectionInfoUsingIndex(ElfData *elfData, int index){
  uint32_t *sectInfo = malloc(elfData->sh[index].sh_size);

  inStreamMoveFilePtr(elfData->myFile, elfData->sh[index].sh_offset);
  fread(sectInfo, elfData->sh[index].sh_size, 1, elfData->myFile->file);

  return sectInfo;
}

/******************************************************************************
 * Get All Section Info
 *
 *  Operation:
 *          To read the information of section and name in the section header
 *          with the two function created which are getSectionInfoUsingIndex
 *          and getSectionInfoNameUsingIndex.
 *
 *  Input:
 *          elfData(ElfData structure)
 *
 *  Data:
 *          Information of the Section allocate with the size of _Elf32_Shdr
 *          multiply with e_shnum in the ELF Header
 *
 *  Return:
 *          elfData->programElf
 *          (The structure of _Elf32_Shdr)
 *
 ******************************************************************************/
_Elf32_Shdr *getAllSectionInfo(ElfData *elfData){
  elfData->programElf = malloc(elfData->eh->e_shnum * sizeof(_Elf32_Shdr));
  int i;

  for(i = 0; i < elfData->eh->e_shnum; i++){
    elfData->programElf[i].section = (char *)getSectionInfoUsingIndex(elfData, i);
    elfData->programElf[i].name = (char *)getSectionInfoNameUsingIndex(elfData, i);
  }

  return elfData->programElf;
}

/******************************************************************************
 * Elf Data initialization with open the file
 *
 *  Operation:
 *          To open the file and gather all the elfData structure information
 *
 *  Input:
 *          fileName
 *          (Directory of the file)
 *
 *  Data:
 *          myFile, eh, sh, ph, programElf, st
 *
 *  Return:
 *          elfData
 *          (The structure of elfData)
 *
 ******************************************************************************/
ElfData *openElfFile(char *fileName){
  ElfData *elfData = malloc(sizeof(ElfData));

  elfData->myFile = openFile(fileName, "rb+");
  elfData->eh = getElfHeader(elfData);
  elfData->sh = getSectionHeaders(elfData);
  elfData->ph = getProgramHeaders(elfData);
  elfData->programElf = getAllSectionInfo(elfData);
  elfData->st = getSymbolTables(elfData);

  return elfData;
}

/******************************************************************************
 * Get Section Header Address From Index
 *
 *  Operation:
 *          To get the address of section header
 *
 *  Input:
 *          elfData(ElfData structure)
 *          index(index of section in section header)
 *
 *  Data:
 *          section header address
 *
 *  Return:
 *          shAddr
 *
 ******************************************************************************/
uint32_t getSectionHeaderAddrUsingIndex(ElfData *elfData, int index){
  uint32_t shAddr;

  shAddr = elfData->sh[index].sh_addr;

  return shAddr;
}

/******************************************************************************
 * Get Section Index From Section Name
 *
 *  Operation:
 *          To get the index of section in section header from the section name
 *
 *  Input:
 *          elfData(ElfData structure)
 *
 *  Data:
 *          The index of section
 *
 *  Return:
 *          index(Name Matched)
 *          -1 (Not Matched)
 *
 ******************************************************************************/
int getIndexOfSectionByName(ElfData *elfData, char *name){
  int i;

  for(i = 0; i < elfData->eh->e_shnum; i++){
    if(strcmp(elfData->programElf[i].name , name) == 0){
      return i;
    }
  }

  return -1;
}

/******************************************************************************
 * Get Section Address From Section Index
 *
 *  Operation:
 *          To get the address of section in function getAllSectionInfo from
 *          the section index
 *
 *  Input:
 *          elfData(ElfData structure)
 *          index(Section index)
 *
 *  Data:
 *          The address of section
 *
 *  Return:
 *          secAddress
 *
 ******************************************************************************/
uint32_t getSectionAddress(ElfData *elfData, int index){
  uint32_t secAddress;
  secAddress = (uint32_t)elfData->programElf[index].section;

  return secAddress;
}

/******************************************************************************
 * Get Section Size From Section Index
 *
 *  Operation:
 *          To get the size of section in section header from the section
 *          index
 *
 *  Input:
 *          elfData(ElfData structure)
 *          index(Section index)
 *
 *  Data:
 *          The size of section
 *
 *  Return:
 *          sectionSize
 *
 ******************************************************************************/
int getSectionSize(ElfData *elfData, int index){
  int sectionSize;
  sectionSize = elfData->sh[index].sh_size;

  return sectionSize;
}

/******************************************************************************
 * Get Physical Address From Program Header Index
 *
 *  Operation:
 *          To get the physical address in program header from the program
 *          header index
 *
 *  Input:
 *          elfData(ElfData structure)
 *          index(Section index)
 *
 *  Data:
 *          The physical address
 *
 *  Return:
 *          phyAddr
 *
 ******************************************************************************/
uint32_t getSectionPhysicalAddress(ElfData *elfData, int index){
  uint32_t phyAddr;
  phyAddr = elfData->ph[index].p_paddr;

  return phyAddr;
}

/******************************************************************************
 * Get Virtual Address From Program Header Index
 *
 *  Operation:
 *          To get the virtual address in program header from the program
 *          header index
 *
 *  Input:
 *          elfData(ElfData structure)
 *          index(Section index)
 *
 *  Data:
 *          The virtual address
 *
 *  Return:
 *          virAddr
 *
 ******************************************************************************/
uint32_t getSectionVirtualAddress(ElfData *elfData, int index){
  uint32_t virAddr;
  virAddr = elfData->ph[index].p_vaddr;

  return virAddr;
}

/******************************************************************************
 * Section Executable Check
 *
 *  Operation:
 *          To check the program header available for executable from flag
 *
 *  Input:
 *          elfData(ElfData structure)
 *          index(Program Header index)
 *
 *  Return:
 *          1(Available)
 *          0(Not Available)
 *
 ******************************************************************************/
int isSectionExecutable(ElfData *elfData, int index){
  int flag;
  flag = elfData->ph[index].p_flags;

  if((flag & PF_X) == 1){
    return 1;
  }else{
    return 0;
  }
}

/******************************************************************************
 * Section Writeable Check
 *
 *  Operation:
 *          To check the program header available for writeable from flag
 *
 *  Input:
 *          elfData(ElfData structure)
 *          index(Program Header index)
 *
 *  Return:
 *          1(Available)
 *          0(Not Available)
 *
 ******************************************************************************/
int isSectionWriteable(ElfData *elfData, int index){
  int flag;
  flag = elfData->ph[index].p_flags;

  if((flag & PF_W) == 2){
    return 1;
  }else{
    return 0;
  }
}

/******************************************************************************
 * Section Readable Check
 *
 *  Operation:
 *          To check the program header available for readable from flag
 *
 *  Input:
 *          elfData(ElfData structure)
 *          index(Program Header index)
 *
 *  Return:
 *          1(Available)
 *          0(Not Available)
 *
 ******************************************************************************/
int isSectionReadable(ElfData *elfData, int index){
  int flag;
  flag = elfData->ph[index].p_flags;

  if((flag & PF_R) == 4){
    return 1;
  }else{
    return 0;
  }
}

/******************************************************************************
 * Get Symbol Table Entries
 *
 *  Operation:
 *          To get symbol table entries
 *
 *  Input:
 *          elfData(ElfData structure)
 *
 *  Data:
 *          The entries of symbol table
 *
 *  Return:
 *          symTabEntries
 *
 ******************************************************************************/
int getSymbolTableEntries(ElfData *elfData){
  int i, symTabEntries;

  for(i = 0; elfData->sh[i].sh_type != SHT_SYMTAB; i++);
  symTabEntries = elfData->sh[i].sh_size / 4;

  return symTabEntries;
}

/******************************************************************************
 * Get Symbol Table Size From Name
 *
 *  Operation:
 *          To get symbol table size by moving the pointer to sh[i].sh_offset
 *          plus st[j].st_name
 *
 *  Input:
 *          elfData(ElfData structure)
 *          name(Symbol Table name)
 *
 *  Data:
 *          The size of symbol table
 *
 *  Return:
 *          st[j].st_size(Matched)
 *          -1(Not matched)
 *
 ******************************************************************************/
uint32_t getSymbolTableSizeUsingName(ElfData *elfData, char *name){
  char *SectNames;
  int i, j, symTabEntries;

  for(i = 0; i < elfData->eh->e_shnum - 1; i++);
  SectNames = malloc(elfData->sh[i].sh_size);

  symTabEntries = getSymbolTableEntries(elfData);

  for(j = 0; j < symTabEntries; j++){
    inStreamMoveFilePtr(elfData->myFile, elfData->sh[i].sh_offset + elfData->st[j].st_name);
    fread(SectNames, elfData->sh[i].sh_size, 1, elfData->myFile->file);
    if(strcmp(SectNames , name) == 0){
      return elfData->st[j].st_size;
    }
  }

  return -1;
}

/******************************************************************************
 * Get Symbol Table Address From Name
 *
 *  Operation:
 *          To get symbol table address by moving the pointer to sh[i].sh_offset
 *          plus st[j].st_name
 *
 *  Input:
 *          elfData(ElfData structure)
 *          name(Symbol Table name)
 *
 *  Data:
 *          The address of symbol table
 *
 *  Return:
 *          st[j].st_value(Matched)
 *          -1(Not matched)
 *
 ******************************************************************************/
uint32_t getSymbolTableAddressUsingName(ElfData *elfData, char *name){
  char *SectNames;
  int i, j, symTabEntries;

  for(i = 0; i < elfData->eh->e_shnum - 1; i++);
  SectNames = malloc(elfData->sh[i].sh_size);

  symTabEntries = getSymbolTableEntries(elfData);

  for(j = 0; j < symTabEntries; j++){
    inStreamMoveFilePtr(elfData->myFile, elfData->sh[i].sh_offset + elfData->st[j].st_name);
    fread(SectNames, elfData->sh[i].sh_size, 1, elfData->myFile->file);
    if(strcmp(SectNames , name) == 0){
        return elfData->st[j].st_value;
    }
  }

  return -1;
}

/******************************************************************************
 * Get Symbol Table Name From Index
 *
 *  Operation:
 *          To get symbol table name by moving the pointer to sh[i].sh_offset
 *          plus st[index].st_name
 *
 *  Input:
 *          elfData(ElfData structure)
 *          index(Symbol Table index)
 *
 *  Data:
 *          The names of symbol table
 *
 *  Return:
 *          symbolName
 *
 ******************************************************************************/
char *getSymbolTableNameUsingIndex(ElfData *elfData, int index){
  char *symbolName;
  int i, j;

  for(i = 0; i < elfData->eh->e_shnum - 1; i++);
  symbolName = malloc(elfData->sh[i].sh_size);

  inStreamMoveFilePtr(elfData->myFile, elfData->sh[i].sh_offset + elfData->st[index].st_name);
  fread(symbolName, elfData->sh[i].sh_size, 1, elfData->myFile->file);

  return symbolName;
}

ElfSection *getElfSectionInfo(ElfData *elfData, char *section) {
  ElfSection *elfSection = malloc(sizeof(ElfSection));

  elfSection->index = getIndexOfSectionByName(elfData, section);
  elfSection->dataAddress = (uint8_t *)getSectionAddress(elfData, elfSection->index);
  elfSection->destAddress = getSectionHeaderAddrUsingIndex(elfData, elfSection->index);
  elfSection->size = (int)getSectionSize(elfData, elfSection->index);

  return elfSection;
}

void getElfSection(char *elfFile) {

  fileStatus = FILE_OPENED;

  elfData = openElfFile(elfFile);
  isr     = getElfSectionInfo(elfData, ".isr_vector");
  text    = getElfSectionInfo(elfData, ".text");
  rodata  = getElfSectionInfo(elfData, ".rodata");
  initArray = getElfSectionInfo(elfData, ".init_array");
  finiArray = getElfSectionInfo(elfData, ".fini_array");
  data = getElfSectionInfo(elfData, ".data");

  entryAddress = (*(uint32_t *)(&isr->dataAddress[4]));
  // programSize = isr->size + text->size;
}

int getProgramSize(char *elfFile) {
  int programSize = 0;

  getElfSection(elfFile);

  programSize = isr->size + text->size;

  closeElfFile();

  return programSize;
}

void closeElfData(ElfData *elfData) {
  if(elfData != NULL) {
    if(elfData->myFile)     free(elfData->myFile);
    if(elfData->eh)         free(elfData->eh);
    if(elfData->sh)         free(elfData->sh);
    if(elfData->ph)         free(elfData->ph);
    if(elfData->programElf) free(elfData->programElf);
    if(elfData->st)         free(elfData->st);
    /* Free elf data */
    free(elfData);
    elfData = NULL;
  }
}

void closeElfSection(ElfSection *elfSection) {
  if(elfSection != NULL) {
    free(elfSection);
  }
}

void closeElfFile(void) {
  closeElfSection(isr);
  closeElfSection(text);
  closeElfSection(rodata);
  closeElfSection(initArray);
  closeElfSection(finiArray);
  closeElfSection(data);
  closeElfData(elfData);

  fileStatus = FILE_CLOSED;
}
