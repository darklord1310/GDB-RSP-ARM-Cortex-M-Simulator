#ifndef RemoteSerialProtocol_H
#define RemoteSerialProtocol_H

#include <stdint.h>

typedef enum {BP_MEMORY, BP_HARDWARE, WP_WRITE, WP_READ, WP_ACCESS} BP_Type;

typedef struct Breakpoint Breakpoint;

struct Breakpoint
{
    Breakpoint *next;
    unsigned int addr;
};

Breakpoint *bp;

char *handleQueryPacket(char *data);
char *readSingleRegister(char *data);
char *readAllRegister();
char *writeSingleRegister(char *data);
char *writeAllRegister(char *data);
char *readMemory(char *data);
char *writeMemory(char *data);
char *step(char *data);
char *cont(char *data);
char *insertBreakpointOrWatchpoint(char *data);
char *removeBreakpointOrWatchpoint(char *data);

Breakpoint *createBreakpoint(unsigned addr);
void deleteBreakpoint(Breakpoint **breakpoint);
void deleteAllBreakpoint(Breakpoint **breakpoint);
void addBreakpoint(Breakpoint **breakpoint, unsigned int addr);
void removeBreakpoint(Breakpoint **breakpoint, unsigned int addr);

#endif // RemoteSerialProtocol_H
