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


#ifndef PipeOperation_H
#define PipeOperation_H

#include <windows.h>

#define BUFFER_SIZE 1024 //1k

//Name given to the pipe
#define g_serverPipeName "\\\\.\\Pipe\\MyNamedPipe"
//Pipe name format - \\.\pipe\pipename

//Name given to the pipe
#define g_clientPipeName "\\\\.\\Pipe\\MyNamedPipe"
//Pipe name format - \\servername\pipe\pipename
//This pipe is for server on the same computer,
//however, pipes can be used to
//connect to a remote server

//Server
int createServerPipe(HANDLE *hPipe);
//Client
int createClientPipe(HANDLE *hPipe);
int waitForConnection(HANDLE *hPipe);
int readMessage(BOOL *bResult, HANDLE hPipe, DWORD *cbBytes, char *msg);
int replyMessage(BOOL *bResult, HANDLE hPipe, DWORD *cbBytes, char *msg);

#endif // PipeOperation_H
