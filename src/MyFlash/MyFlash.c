#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <malloc.h>
#include "MyFlash.h"

void writeFile(char *filename, char *mode, char *str)
{
  FILE *file;
  file = fopen(filename, mode);

  if(file == NULL)
  {
    printf("11error: cannot open the file %s\n", filename);
    return;
  }

  fputs(str, file);
  fprintf(file, " ");

  // Close the file
  fclose(file);
}

char *getDirectoryName(char *pathname)
{
  char *tempStr = NULL, *directoryPath = NULL;
  int len;

  tempStr = strrchr (pathname, '\\');
  len = tempStr - pathname;

  if(tempStr != NULL)
  {
    directoryPath = malloc(len + 1);
    strncpy(directoryPath, pathname, len);
    directoryPath[len] = '\0';
  }

  return directoryPath;
}

char *appendString(char *destStr, char *srcStr)
{
  char *newStr;
  int destLen = 0;

  if(srcStr != NULL)
  {
    if(destStr != NULL)
      destLen = strlen(destStr);
      
    newStr = malloc(destLen + strlen(srcStr) + 1);
    newStr[0] = '\0';   // ensures the memory is an empty string
    
    if(destStr != NULL)
      strcat(newStr, destStr);
    strcat(newStr, srcStr);
  }
  else
    return NULL;

  return newStr;
}

void destroyStr(char *newStr)
{
  if(newStr)
    free(newStr);
}

#if defined (TEST)
int coflash(int argc, const char * argv[])
#else
int main(int argc, const char * argv[])
#endif
{
  int i;
  char elfPath[1024] = "", device[100]= "", *ret1, *ret2, *parentDirName = NULL, *dirName = NULL;

  for(i = 0; i < argc; i++)
  {
    ret1 = strstr(argv[i], ".elf");
    ret2 = strstr(argv[i], "--driver=");

    if(ret1 != NULL)            //locate the correct elf file
    {
      if(strcmp(ret1, ".elf") == 0 && ret2 == NULL)
        strcpy(elfPath, argv[i]);
    }

    if(strncmp(argv[i], "STM", strlen("STM")) == 0)
      strcpy(device, argv[i]);
  }

  
  parentDirName = getDirectoryName((char *)argv[0]);

#if defined (TEST)
    dirName = appendString(parentDirName, "TEST1.txt");     // different dir when test in other machine 
#else
  if(parentDirName != NULL)
    dirName = appendString(parentDirName, "/ElfLocation.txt");
  else
  {
    printf("Unable to get directoy\n");
    return 0;
  }
#endif

  writeFile(dirName, "w", elfPath);
  writeFile(dirName, "a", device);

  destroyStr(parentDirName);
  destroyStr(dirName);
  return 0;
}