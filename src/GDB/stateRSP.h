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

#ifndef stateRSP_H
#define stateRSP_H

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

void rspState(RspData *rspData, char *data);

#endif // stateRSP_H
