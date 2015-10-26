#include "Read_File.h"
#include <stdio.h>
#include <malloc.h>
#include "CException.h"
#include "ErrorCode.h"

/******************************************************************************
 * File Open
 *
 *  Operation:
 *          To open the file
 *
 *  Input:
 *          fileDirectory(directory of the file)
 *          mode(mode to open the file)
 *
 *  Return:
 *          myFile
 *
 ******************************************************************************/
InStream *openFile(char *fileDirectory, char *mode){
  InStream *myFile = (InStream *)malloc(sizeof(InStream));
  
  myFile->file = fopen(fileDirectory, mode);
  
  if(myFile->file == NULL){
    // Throw(ERR_FILE_NOT_EXIST);
    printf("File not exist");
  }
  
  myFile->filename = fileDirectory;
  myFile->byteIndex = 0;
  myFile->bitIndex = 8;

  return myFile;
}

/******************************************************************************
 * File Close
 *
 *  Operation:
 *          To close the file
 *
 *  Input:
 *          fileDirectory(directory of the file)
 *
 *  Return:
 *          none
 *
 ******************************************************************************/
void *closeFileInTxt(InStream *myFile){
  fclose(myFile->file);
  free(myFile);
}

/******************************************************************************
 * InStream Move File Pointer
 *
 *  Operation:
 *          To move the file pointer
 *
 *  Input:
 *          myFile(directory of the file)
 *          offset(offset to pointing at)
 *
 *  Return:
 *          startPos(0 is valid)
 *          Throw(ERR_RANGE_OFFSET)(1 is not valid)
 *
 ******************************************************************************/
uint32_t inStreamMoveFilePtr(InStream *myFile, long int offset){
  int startPos;
  
  startPos = fseek(myFile->file, offset, SEEK_SET);
  
  if(startPos == 1){
    Throw(ERR_RANGE_OFFSET);
  }else{
    return startPos;
  }
}

/******************************************************************************
 * Position File Pointer
 *
 *  Operation:
 *          To display the current position file pointer
 *
 *  Input:
 *          myFile(directory of the file)
 *
 *  Return:
 *          ptrPosition
 *
 ******************************************************************************/
uint32_t posPtr(InStream *myFile){
  long int ptrPosition;
  
  ptrPosition = ftell(myFile->file);
  return ptrPosition;
}

/******************************************************************************
 *
 *                  Here is the code for exploring the fread
 *
 ******************************************************************************/
/*
uint32_t readBit(InStream *getBit){
  int returnBit = 0;
  int mask = 1;
  
  returnBit = (getBit->byteIndex >> getBit->bitIndex) & mask;
  
  return returnBit;
}

uint32_t readBits(InStream *getBit, int bitSize){
  uint32_t readChar = 0;
  uint32_t returnBits = 0;
  int i;
  
  for(i = 0; i < bitSize; i++){
    while(getBit->bitIndex == 8){
      if(feof(getBit->file) != 1){
        fread(&(getBit->byteIndex), sizeof(getBit->byteIndex), 1, getBit->file);
      getBit->bitIndex = 0;
      }
    }
    readChar = readBit(getBit);
    returnBits = returnBits | (readChar << i);
    getBit->bitIndex++;
  }
  
  return returnBits;
}

uint32_t oneByte(InStream *getByte){
  uint32_t returnBits;

  returnBits = readBits(getByte, 8);
  return returnBits;
}

uint32_t twoByte(InStream *getByte){
  uint32_t returnBits;

  returnBits = readBits(getByte, 16);
  return returnBits;
}

uint32_t fourByte(InStream *getByte){
  uint32_t returnBits;

  returnBits = readBits(getByte, 32);
  return returnBits;
}

uint32_t byteSelection(InStream *getByte, int inputByte){
  uint32_t returnBits;
  
  if(inputByte == 1){
    returnBits = oneByte(getByte);
  }else if(inputByte == 2){
    returnBits = twoByte(getByte);
  }else if(inputByte == 4){
    returnBits = fourByte(getByte);
  }else{
    Throw(ERR_BYTE_SELECTION);
  }
  
  return returnBits;
}*/



