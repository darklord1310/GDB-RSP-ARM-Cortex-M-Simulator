#ifndef ConfigurationDetail_H
#define ConfigurationDetail_H

#include <stdint.h>

typedef struct ConfigInfo ConfigInfo;

struct ConfigInfo
{
  // char *device;
  uint32_t flashOrigin;
  uint32_t flashSize;
  uint32_t ramOrigin;
  uint32_t ramSize;
};

#endif // ConfigurationDetail_H