/*  
    GDB RSP and ARM Simulator

    Copyright (C) 2015 Wong Yan Yin, <jet_wong@hotmail.com>,
    Jackson Teh Ka Sing, <jackson_dmc69@hotmail.com>

    This file is part of GDB RSP and ARM Simulator.

    This program is free software, you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY, without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with This program.  If not, see <http://www.gnu.org/licenses/>.
*/

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

void initializeWatchpoint();
void addWatchpoint(unsigned int addr, unsigned int size, BP_Type type);
void removeWatchpoint(unsigned int addr, unsigned int size, BP_Type type);

int findBreakpoint(Breakpoint *breakpoint);

#endif // RemoteSerialProtocol_H
