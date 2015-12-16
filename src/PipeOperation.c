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


#include <stdio.h>
#include <string.h>
#include "PipeOperation.h"

int createServerPipe(HANDLE *hPipe)
{
  *hPipe = CreateNamedPipe(
          g_szPipeName,             // pipe name
          PIPE_ACCESS_DUPLEX,       // read/write access
          PIPE_TYPE_MESSAGE |       // message type pipe
          PIPE_READMODE_MESSAGE |   // message-read mode
          PIPE_WAIT,                // blocking mode
          PIPE_UNLIMITED_INSTANCES, // max. instances
          BUFFER_SIZE,              // output buffer size
          BUFFER_SIZE,              // input buffer size
          NMPWAIT_USE_DEFAULT_WAIT, // client time-out
          NULL);                    // default security attribute

  if (INVALID_HANDLE_VALUE == *hPipe)
  {
    printf("\nError occurred while creating the pipe: %d", GetLastError());
    return 1;  //Error
  }
  else
  {
    printf("\nCreateNamedPipe() was successful.");
  }

  return 0;
}

int createClientPipe(HANDLE *hPipe)
{
  *hPipe = CreateFile(
          g_szPipeName,     // pipe name
          GENERIC_READ |    // read and write access
          GENERIC_WRITE,
          0,                // no sharing
          NULL,             // default security attributes
          OPEN_EXISTING,    // opens existing pipe
          0,                // default attributes
          NULL);            // no template file

  if (INVALID_HANDLE_VALUE == *hPipe)
  {
    printf("\nError occurred while connecting to the server: %d", GetLastError());
    //One might want to check whether the server pipe is busy
    //This sample will error out if the server pipe is busy
    //Read on ERROR_PIPE_BUSY and WaitNamedPipe() for that
    return 1;  //Error
  }
  else
  {
    printf("\nCreateFile() was successful.");
  }

  return 0;
}

int waitForConnection(HANDLE *hPipe)
{
  if(createServerPipe(hPipe))
      return 1;

  printf("\nWaiting for client connection...");

  BOOL bClientConnected = ConnectNamedPipe(*hPipe, NULL);

  if (FALSE == bClientConnected)
  {
    printf("\nError occurred while connecting to the client: %d", GetLastError());
    CloseHandle(*hPipe);
    return 1;  //Error
  }
  else
  {
    printf("\nConnectNamedPipe() was successful.");
  }

  return 0;
}

int readMessage(BOOL *bResult, HANDLE hPipe, DWORD *cbBytes, char *msg)
{
  char szBuffer[BUFFER_SIZE];

  *bResult = ReadFile(
          hPipe,                  // handle to pipe
          szBuffer,               // buffer to receive data
          sizeof(szBuffer),       // size of buffer
          cbBytes,                // number of bytes read
          NULL);                  // not overlapped I/O

  if ( (!*bResult) || (0 == *cbBytes))
  {
    printf("\nError occurred while reading from the client: %d", GetLastError());
    CloseHandle(hPipe);
    return 1;  //Error
  }
  else
  {
    strcpy(msg, szBuffer);
    printf("\nReadFile() was successful.");
  }

  return 0;
}

int replyMessage(BOOL *bResult, HANDLE hPipe, DWORD *cbBytes, char *msg)
{
  *bResult = WriteFile(
          hPipe,                // handle to pipe
          msg,                  // buffer to write from
          strlen(msg)+1,        // number of bytes to write, include the NULL
          cbBytes,             // number of bytes written
          NULL);                // not overlapped I/O

  if ( (!*bResult) || (strlen(msg)+1 != *cbBytes))
  {
    printf("\nError occurred while writing to the client: %d", GetLastError());
    CloseHandle(hPipe);
    return 1;  //Error
  }
  else
  {
    printf("\nWriteFile() was successful.");
  }

  return 0;
}