#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <stdint.h>
#include "MyFlash.h"
#include "LoadElf.h"
#include "ProgramElf.h"
#include "GetHeaders.h"
#include "Relocator.h"
#include "Read_File.h"
#include "elf.h"
#include "CException.h"
#include "ErrorCode.h"
#include "FileOperation.h"

#if defined (TEST)
int coflash(int argc, const char * argv[])
#else
int main(int argc, const char * argv[])
#endif
{
  int i;
  char elfPath[1024] = "", device[100]= "";
  ElfData *elfData;
  FILE file;
  ConfigInfo configInfo;
  uint32_t flashStartAddr, flashSize;

  for(i = 0; i < argc; i++)
  {
    if(strcmp("program", argv[i]) == 0)
    {
      strcpy(device, argv[i+1]);
      strcpy(elfPath, argv[i+2]);
    }
  }

  elfData = openElfFile(elfPath);
  readConfigfile(&file, &configInfo, device);
  // loadElf(elfData, &file, configInfo.flashOrigin, configInfo.flashSize);

  return 0;
}