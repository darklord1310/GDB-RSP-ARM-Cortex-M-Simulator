#ifndef Read_File_H
#define Read_File_H

#include <stdio.h>

#include "elf.h"

typedef struct InStream InStream;

struct InStream{
  FILE *file;
  char *filename;
  uint8_t byteIndex;
  uint32_t bitIndex;
};

// Open and Close File
InStream *openFile(char *fileDirectory, char *mode);
void *closeFileInTxt(InStream *fileDirectory);

// Move File Ptr 
uint32_t inStreamMoveFilePtr(InStream *myFile, long int offset);

// Get pointer position
uint32_t posPtr(InStream *myFile);

/*
char *readFileInTxt(InStream *getByte, char *buffer);
uint32_t readBit(InStream *getBit);
uint32_t readBits(InStream *getBit, int bitSize);
uint32_t oneByte(InStream *getByte);
uint32_t twoByte(InStream *getByte);
uint32_t fourByte(InStream *getByte);
uint32_t byteSelection(InStream *getByte, int inputByte);
*/

#endif // Read_File_H
