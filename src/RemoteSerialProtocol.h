#ifndef RemoteSerialProtocol_H
#define RemoteSerialProtocol_H

#include <stdint.h>

#define MAX_HW_WATCHPOINT      4       //max hardware watchpoint is 4 for now

//type of breakpoint and watchpoint
typedef enum {BP_MEMORY, BP_HARDWARE, WP_WRITE, WP_READ, WP_ACCESS, NONE} BP_Type;

typedef struct Breakpoint Breakpoint;
typedef struct Watchpoint Watchpoint;

struct Breakpoint
{
    Breakpoint *next;
    unsigned int addr;
};

struct Watchpoint
{
    BP_Type type;
    unsigned int addr;
    unsigned int size;
};

Breakpoint *bp;
Watchpoint wp[MAX_HW_WATCHPOINT];

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

void addWatchpoint(unsigned int addr, unsigned int size, BP_Type type);
void removeWatchpoint(unsigned int addr, unsigned int size, BP_Type type);

int findBreakpoint(Breakpoint *breakpoint);

#endif // RemoteSerialProtocol_H
