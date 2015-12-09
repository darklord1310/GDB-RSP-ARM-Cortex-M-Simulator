#ifndef FileOperation_H
#define FileOperation_H

#include <stdio.h>
#include "ConfigurationDetail.h"

typedef struct GdbServerInfo GdbServerInfo;

struct GdbServerInfo
{
  char *host;
  int port;
};

char *readFile(char *filename, char *mode);
void readConfigfile(char *filename, char *mode, ConfigInfo *configInfo, char *device);
GdbServerInfo *readGdbServerConfigFile(char *filename, char *mode);
void writeFile(char *filename, char *mode, char *str);

GdbServerInfo *createGdbServerInfo(char *host, int port);
void *destroyGdbServerInfo(GdbServerInfo *gdbServerInfo);

char *getDirectoryName(char *pathname);
char *appendString(char *destStr, char *srcStr);
void destroyStr(char *newStr);

#endif // FileOperation_H
