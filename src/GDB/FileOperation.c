#include <assert.h>
#include <string.h>
#include <malloc.h>
#include "FileOperation.h"


char *readFile(FILE *file, char *filename)
{
  char buffer[1024] = "", *str;

  file = fopen(filename, "r");

  if(file == NULL)
  {
    printf("error: cannot open the file %s\n", filename);
    return "";
  }

  str = fgets(buffer, 1024, file);

  // Close the file
  fclose(file);

  return str;
}

void readConfigfile(FILE *file, char *filename, ConfigInfo *configInfo, char *device)
{
  assert(device != NULL);
  char *str = NULL, buffer[1024], prefix;
  file = fopen(filename, "r");
  uint32_t flashOrigin, flashSize, ramOrigin, ramSize;

  if(file == NULL)
  {
    printf("error: cannot open the file %s\n", filename);
    return;
  }

  do {
    str = fgets(buffer, 100, file);

    if(str == NULL)       // reach end of file
      break;
    else
    {
      if(strncmp(str, device, strlen(device)) == 0)
        break;
    }
  } while(1);

  if(str != NULL)
  {
    str = fgets(buffer, 100, file);
    sscanf(str, "FLASH ORIGIN = 0x%8x LENGTH = %d%c", &flashOrigin, &flashSize, &prefix);
    configInfo->flashOrigin = flashOrigin;
    configInfo->flashSize = flashSize;
    if(prefix == 'K')
      configInfo->flashSize *= 1024;

    str = fgets(buffer, 100, file);
    sscanf(str, "RAM ORIGIN = 0x%8x LENGTH = %d%c", &ramOrigin, &ramSize, &prefix);
    configInfo->ramOrigin = ramOrigin;
    configInfo->ramSize = ramSize;
    if(prefix == 'K')
      configInfo->ramSize *= 1024;
  }

  // Close the file
  fclose(file);
}

int readGdbServerConfigFile(FILE *file, char *filename)
{
  char *str = NULL, buffer[1024], prefix;
  int portNumber = -1;
  file = fopen(filename, "r");

  if(file == NULL)
  {
    printf("error: cannot open the file %s\n", filename);
    return -1;
  }

  str = fgets(buffer, 100, file);

  if(str != NULL)       // reach end of file
  {
    if(strncmp(str, "[GDBServer]", strlen("[GDBServer]")) == 0)
    {
      str = fgets(buffer, 100, file);     // get IP
      str = fgets(buffer, 100, file);     // get Port number
      sscanf(str, "Port=%d", &portNumber);
    }
  }

  // Close the file
  fclose(file);

  return portNumber;
}

void writeFile(FILE *file, char *filename, char *mode, char *str)
{
  file = fopen(filename, mode);

  if(file == NULL)
  {
    printf("error: cannot open the file %s\n", filename);
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

void backwardToForwardSlash(char *path)
{
  int i;

  for(i = 0; path[i] != '\0'; i++)
  {
    if(path[i] == '\\')
      path[i] = '/';
  }
}
