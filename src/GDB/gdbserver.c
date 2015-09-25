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
#include <malloc.h>
#include <string.h>
#include "ServeRSP.h"
#include "ARMRegisters.h"
#include "MemoryBlock.h"
#include "gdbserver.h"
#include "RemoteSerialProtocol.h"
#include "ARMSimulator.h"
#include "State.h"
#include "StateRSP.h"

#ifdef  __MINGW32__
/****************Initialize Winsock.****************/
void winsockInit()
{
    printf( "\n1. Initialising Winsock..............." );
    WSADATA wsaData;
    int iResult = WSAStartup( MAKEWORD(2,2), &wsaData );
    if ( iResult != NO_ERROR )
    {
        displayErrorMsg("WSAStartup()");
        WSACleanup();
        return;
    }
    else
        printf( "Initialised\n" );
}

#endif

/****************Create a socket.****************/
void createSocket(SOCKET *sock)
{
    printf( "2. Creating socket...................." );
    *sock = socket( AF_INET, SOCK_STREAM, IPPROTO_TCP );
    if ( *sock == INVALID_SOCKET )
    {
        displayErrorMsg("socket()");
#ifdef  __MINGW32__
        WSACleanup();
#endif
        return;
    }
    else
        printf( "Socket created\n" );
}

/****************Bind the socket.****************/
void bindSocket(SOCKET *sock)
{
    printf( "3. Binding socket....................." );
    struct sockaddr_in service;
    service.sin_family = AF_INET;
    service.sin_addr.s_addr = inet_addr( LOCAL_HOST_ADD );
    service.sin_port = htons( DEFAULT_PORT );
    if ( bind( *sock, (SOCKADDR*) &service, sizeof(service) ) == SOCKET_ERROR )
    {
        displayErrorMsg("bind()");
#ifdef  __MINGW32__
        closesocket(*sock);
#elif  __linux__
        close(*sock);
#endif
        return;
    }
    else
        printf( "Bind done\n" );
}

/****************Listen on the socket.****************/
void listenSocket(SOCKET *sock)
{
    printf( "4. Listening to socket................" );
    if ( listen( *sock, 1 ) == SOCKET_ERROR )
        printf( ">>>Error listening on socket\n");
    else
        printf( "Listening...\n" );
}

/****************Accept connections.****************/
void waitingForConnection(SOCKET *sock)
{
    printf( "5. Waiting on %s:%d...", LOCAL_HOST_ADD, DEFAULT_PORT );
    SOCKET acceptSocket;
    while (1)
    {
        acceptSocket = SOCKET_ERROR;
        while ( acceptSocket == SOCKET_ERROR )
            acceptSocket = accept( *sock, NULL, NULL );

        if ( acceptSocket == INVALID_SOCKET )
            displayErrorMsg("accept()");
        else
            printf( "Connection accepted\n" );
        *sock = acceptSocket;
        break;
    }
}

/****************Send data.****************/
int sendBuffer(SOCKET *sock, char *sendbuf)
{
    int bytesSent;

    bytesSent = send( *sock, sendbuf, strlen(sendbuf), 0 );
    printf( "\nBytes Sent: %ld\n", bytesSent );
    printf( "Reply: %s\n", sendbuf );

    return bytesSent;
}

/****************Receive data.****************/
int receiveBuffer(SOCKET *sock, char *recvbuf)
{
    int bytesRecv = SOCKET_ERROR;

    bytesRecv = recv( *sock, recvbuf, PACKET_SIZE, 0 );
    printf( "\nBytes Recv: %ld\n", bytesRecv );

    return bytesRecv;
}

void displayErrorMsg(char *errorMsg)
{
#ifdef  __MINGW32__
    printf( ">>>Error at %s: %ld\n" , errorMsg, WSAGetLastError() );
#elif  __linux__
    printf( ">>>%s\n" , errorMsg );
#endif
}

void main()
{
    SOCKET sock;
    RspData rspData = {INITIAL, sock};

    initializeSimulator();
    initializeWatchpoint();

#ifdef  __MINGW32__
    winsockInit();
#endif
    createSocket(&rspData.sock);
    bindSocket(&rspData.sock);
    listenSocket(&rspData.sock);
    waitingForConnection(&rspData.sock);

    int bytesSent;
    int bytesRecv;
    char *reply = NULL;
    char recvbuf[PACKET_SIZE] = "";
    rspData.state = INITIAL;

    while(1)
    {
        bytesRecv = receiveBuffer(&rspData.sock, recvbuf);
        if(bytesRecv != -1)
        {
            recvbuf[bytesRecv] = '\0';
            printf( "recvbuf: %s\n", recvbuf );
        }
        else
            rspData.state = NACK;

        // do {
            // reply = rspState(&rspData, recvbuf);
            rspState(&rspData, recvbuf);
        // }while(state == ACK || state == NACK || state == KILL);

        if(rspData.state == KILL)
        {
            break;
        }
        /* else
        {
            bytesSent = sendBuffer(&rspData.sock, reply);
            printf("reply: %s\n", reply);
        } */

        /* if(reply != NULL)
            free(reply); */
    }

    // deleteAllBreakpoint(&bp);

#ifdef  __MINGW32__
    /****************Close our socket entirely****************/
    closesocket(rspData.sock);

    /****************Cleanup Winsock****************/
    WSACleanup();
#elif  __linux__
    close(rspData.sock);
#endif
}
