#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include "MyFlash.h"

#define FILE_LOCATION   "C:/CooCox/CoIDE_V2Beta/bin/ElfLocation.txt"    // might cause problem to other computer as the
                                                                        // directory that coocox install is different
// #define FILE_LOCATION   "C:/ElfLocation.txt"

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
  fprintf(file, " ");

  // Close the file
  fclose(file);
}


#if defined (TEST)
int coflash(int argc, const char * argv[])
#else
int main(int argc, const char * argv[])
#endif
{
  int i;
  char elfPath[1024] = "", device[100]= "", *ret1, *ret2, *dir, buf[100];
  char *filename = FILE_LOCATION;
  FILE file;

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

  writeFile(&file, filename, "w", elfPath);
  writeFile(&file, filename, "a", device);

  return 0;
}