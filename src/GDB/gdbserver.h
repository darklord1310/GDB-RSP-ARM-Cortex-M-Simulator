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

#ifndef gdbserver_H
#define gdbserver_H

#ifdef _WIN32

#ifdef GDBSERVER_MAIN_EXPORTS
  #define GDBSERVER_MAIN __declspec(dllexport)
#else
  #define GDBSERVER_MAIN __declspec(dllimport)
#endif

/* Define calling convention in one place, for convenience. */
#define GDBSERVER_CALL __cdecl

#else /* _WIN32 not defined. */

  /* Define with no value on non-Windows OSes. */
  #define GDBSERVER_MAIN
  #define GDBSERVER_CALL

#endif

/* Make sure functions are exported with C linkage under C++ compilers. */
#ifdef __cplusplus
extern "C"
{
#endif


#define LOCAL_HOST_ADD  "127.0.0.1"
#define DEFAULT_PORT    2010
#define PACKET_SIZE     0x3fff

#include "FileOperation.h"

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

#define INVALID_SOCKET  (SOCKET)(~0)
#define SOCKET_ERROR            (-1)

#endif

typedef enum {GDB_SERVER_INFO, ELF_PATH, ELF_DATA} TypeOfDataToRetrieve;

/* Declare our Add function using the above definitions. */
GDBSERVER_MAIN int GDBSERVER_CALL main(int argc, const char * argv[]);

// void gdbserverMain(int argc, const char * argv[]);
void winsockInit();
void createSocket(SOCKET *sock);
void bindSocket(SOCKET *sock, int port);
void listenSocket(SOCKET *sock);
void waitingForConnection(SOCKET *sock, int port);
int sendBuffer(SOCKET *sock, char *sendbuf);
int receiveBuffer(SOCKET *sock, char *recvbuf);
void displayErrorMsg(char *errorMsg);

void initSimulator();
void *retrieveData(char *dir, TypeOfDataToRetrieve dataToRetrieve);

#ifdef __cplusplus
} // __cplusplus defined.
#endif

#endif // gdbserver_H
