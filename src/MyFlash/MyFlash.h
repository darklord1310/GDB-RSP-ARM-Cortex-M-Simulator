#ifndef MyFlash_H
#define MyFlash_H


#if defined (TEST)
int coflash(int argc, const char * argv[]);
#else
int main(int argc, const char * argv[]);
#endif

void writeFile(FILE *file, char *filename, char *mode, char *str);
char *getDirectoryName(char *pathname);

#endif // MyFlash_H
