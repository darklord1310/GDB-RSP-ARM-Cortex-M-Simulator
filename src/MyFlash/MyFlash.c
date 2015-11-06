#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include "MyFlash.h"

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

void backwardToForwardSlash(char *path)
{
  int i;

  for(i = 0; path[i] != '\0'; i++)
  {
    if(path[i] == '\\')
      path[i] = '/';
  }
}

#if defined (TEST)
int coflash(int argc, const char * argv[])
#else
int main(int argc, const char * argv[])
#endif
{
  int i;
  char elfPath[1024] = "", device[100]= "", *ret1, *ret2, *dir, buf[1024];
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

  dir = getcwd(buf, 1024);
  backwardToForwardSlash(buf);

#if defined (TEST)
  strcat(buf, "/TEST1.txt");
#else
  strcat(buf, "/bin/ElfLocation.txt");
#endif

  writeFile(&file, buf, "w", elfPath);
  writeFile(&file, buf, "a", device);

  return 0;
}