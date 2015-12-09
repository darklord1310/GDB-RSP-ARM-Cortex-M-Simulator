#include <assert.h>
#include <string.h>
#include <malloc.h>
#include "FileOperation.h"

/*
  r   open for reading (file must exist)
  w   open for writing (overwrite file, file created if not exist)
  a   open for appending (file created if not exist)
  r+  open for reading and writing, start at beginning (file must exist)
  w+  open for reading and writing (overwrite file, file created if not exist)
  a+  open for appending and reading (file created if not exist)
*/

char *readFile(char *filename, char *mode)
{
  FILE *file;
  char buffer[1024] = "", *str;

  file = fopen(filename, mode);

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

void readConfigfile(char *filename, char *mode, ConfigInfo *configInfo, char *device)
{
  assert(device != NULL);
  FILE *file;
  char *str = NULL, buffer[1024], prefix;
  file = fopen(filename, mode);
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

GdbServerInfo *createGdbServerInfo(char *host, int port)
{
  GdbServerInfo *gdbServerInfo;

  gdbServerInfo = malloc(sizeof(GdbServerInfo));
  gdbServerInfo->host = host;
  gdbServerInfo->port = port;

  return gdbServerInfo;
}

void *destroyGdbServerInfo(GdbServerInfo *gdbServerInfo)
{
  if(gdbServerInfo)
    free(gdbServerInfo);
}

GdbServerInfo *readGdbServerConfigFile(char *filename, char *mode)
{
  FILE *file;
  GdbServerInfo *gdbServerInfo;
  char host[15] = "", *str = NULL, buffer[1024];
  int portNumber = -1;

  file = fopen(filename, "r");

  if(file == NULL)
  {
    printf("error: cannot open the file %s\n", filename);
    return NULL;
  }

  str = fgets(buffer, 100, file);

  if(str != NULL)       // reach end of file
  {
    if(strncmp(str, "[GDBServer]", strlen("[GDBServer]")) == 0)
    {
      str = fgets(buffer, 100, file);     // get IP
      if(strncmp(str, "IP", strlen("IP")) == 0)
        sscanf(str, "IP=%s", &host);
      str = fgets(buffer, 100, file);     // get Port number
      if(strncmp(str, "Port", strlen("Port")) == 0)
        sscanf(str, "Port=%d", &portNumber);
    }
  }

  gdbServerInfo = createGdbServerInfo(host, portNumber);

  // Close the file
  fclose(file);

  return gdbServerInfo;
}

void writeFile(char *filename, char *mode, char *str)
{
  FILE *file;
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
