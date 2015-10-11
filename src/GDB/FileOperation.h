#ifndef FileOperation_H
#define FileOperation_H

#include <stdio.h>
#include <string.h>
#include "ConfigurationDetail.h"

char *readElfText(FILE *file, char *filename);
void readConfigfile(FILE *file, char *filename, ConfigInfo *configInfo, char *device);
void writeFile(FILE *file, char *filename, char *mode, char *str);

#endif // FileOperation_H
