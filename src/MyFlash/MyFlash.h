#ifndef MyFlash_H
#define MyFlash_H


#if defined (TEST)
int coflash(int argc, const char * argv[]);
#else
int main(int argc, const char * argv[]);
#endif

void writeFile(char *filename, char *mode, char *str);
char *appendString(char *destStr, char *srcStr);
void destroyStr(char *newStr);
char *getDirectoryName(char *pathname);

#endif // MyFlash_H
