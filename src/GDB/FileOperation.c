#include <assert.h>
#include "FileOperation.h"


char *readElfText(FILE *file, char *filename)
{
  int i = 0;
  char buffer[100] = "", *str, *elfPath;

  file = fopen(filename, "r");

  if(file == NULL)
  {
    printf("error: cannot open the file %s\n", filename);
    exit;
  }

  elfPath = fgets(buffer, 100, file);

  // Close the file
  fclose(file);

  return elfPath;
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
      {
        // configInfo->device = device;
        break;
      }
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

void writeFile(FILE *file, char *filename, char *mode, char *str)
{
  int i = 0;

  file = fopen(filename, mode);

  if(file == NULL)
  {
    printf("error: cannot open the file %s\n", filename);
    return;
  }

  fputs(str, file);
  fprintf(file, "\n");

  // Close the file
  fclose(file);
}
