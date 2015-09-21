/*  
    Program Name       : GDB RSP and ARM Simulator
    Author             : Wong Yan Yin, Jackson Teh Ka Sing 
    Copyright (C) 2015 TARUC

    This file is part of GDB RSP and ARM Simulator.

    GDB RSP and ARM Simulator is free software, you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    GDB RSP and ARM Simulator is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY, without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with GDB RSP and ARM Simulator.  If not, see <http://www.gnu.org/licenses/>.

*/

#ifndef StateRSP_H
#define StateRSP_H

#include "State.h"

#ifdef  __MINGW32__

#include <winsock2.h>
#pragma comment(lib,<ws2_32.lib>)       //Winsock Library

#elif  __linux__

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h> 
#include <unistd.h>

typedef unsigned int    u_int;
typedef u_int           SOCKET;

#endif

typedef struct RspData RspData;

struct RspData
{
    State state;
    SOCKET sock;
};

// char *rspState(RspData *rspData, char *data);
void rspState(RspData *rspData, char *data);

#endif // StateRSP_H
