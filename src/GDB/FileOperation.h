#ifndef FileOperation_H
#define FileOperation_H

#include <stdio.h>
#include <string.h>
#include "ConfigurationDetail.h"

char *readFile(FILE *file, char *filename);
void readConfigfile(FILE *file, char *filename, ConfigInfo *configInfo, char *device);
int readGdbServerConfigFile(FILE *file, char *filename);
void writeFile(FILE *file, char *filename, char *mode, char *str);

char *getDirectoryName(char *pathname);

#endif // FileOperation_H
