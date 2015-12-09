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

#if defined (TEST)
int coflash(int argc, const char * argv[])
#else
int main(int argc, const char * argv[])
#endif
{
  int i;
  char elfPath[1024] = "", device[100]= "", *ret1, *ret2, *dir = NULL, dir2[1024];

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

  dir = getDirectoryName((char *)argv[0]);

  if(dir != NULL)
  {
     strcpy(dir2, dir);
#if defined (TEST)
    strcat(dir2, "/TEST1.txt");
#else
    strcat(dir2, "/ElfLocation.txt");
#endif

    writeFile(dir2, "w", elfPath);
    writeFile(dir2, "a", device);
  }
  else
    printf("Unable to get directoy\n");

  free(dir);
  return 0;
}