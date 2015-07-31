#include <stdio.h>
#include <malloc.h>
#include <stdint.h>
#include <string.h>
#include "ServeRSP.h"
#include "ARMRegisters.h"
#include "MemoryBlock.h"
#include "gdbserver.h"
#include "getAndSetBits.h"
#include "getMask.h"
// #include "ConditionalExecution.h"
// #include "StatusRegisters.h"
// #include "Thumb16bitsTable.h"
// #include "LSLImmediate.h"
// #include "LSRImmediate.h"
// #include "MOVRegister.h"
// #include "ASRImmediate.h"
// #include "MOVImmediate.h"
// #include "ModifiedImmediateConstant.h"
// #include "CMPImmediate.h"
// #include "ADDImmediate.h"
// #include "SUBImmediate.h"
// #include "ADDRegister.h"
// #include "SUBRegister.h"
// #include "ADDSPRegister.h"
// #include "ITandHints.h"
// #include "ANDRegister.h"
// #include "LSLRegister.h"
// #include "LSRRegister.h"
// #include "ASRRegister.h"
// #include "CMPRegister.h"
// #include "CMNRegister.h"
// #include "EORRegister.h"
// #include "ORRRegister.h"
// #include "RORRegister.h"
// #include "MVNRegister.h"
// #include "BICRegister.h"
// #include "ADCRegister.h"
// #include "BX.h"
// #include "BLXRegister.h"
// #include "MULRegister.h"
// #include "TSTRegister.h"
// #include "RSBImmediate.h"
// #include "SBCRegister.h"
// #include "UnconditionalAndConditionalBranch.h"
// #include "STRRegister.h"
#include "State.h"
#include "stateRSP.h"

/****************Initialize Winsock.****************/
void winsockInit()
{
    printf( "\n1. Initialising Winsock..............." );
    WSADATA wsaData;
    int iResult = WSAStartup( MAKEWORD(2,2), &wsaData );
    if ( iResult != NO_ERROR )
    {
        printf( "\n>>>Error at WSAStartup()\n" );
        WSACleanup();
        return;
    }
    else
        printf( "Initialised\n" );
}

/****************Create a socket.****************/
void createSocket(SOCKET *sock)
{
    printf( "2. Creating socket...................." );
    *sock = socket( AF_INET, SOCK_STREAM, IPPROTO_TCP );
    if ( *sock == INVALID_SOCKET )
    {
        printf( ">>>Error at socket(): %ld\n", WSAGetLastError() );
        WSACleanup();
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
        printf( ">>>Error at bind(): %ld\n", WSAGetLastError() );
        closesocket(*sock);
        return;
    }
    else
        printf( "Bind done\n" );
}

/****************Listen on the socket.****************/
void listenSocket(SOCKET sock)
{
    printf( "4. Listening to socket................" );
    if ( listen( sock, 1 ) == SOCKET_ERROR )
        printf( ">>>Error listening on socket\n");
    else
        printf( "Listening...\n" );
}

/****************Accept connections.****************/
void waitingForConnection(SOCKET *sock)
{
    printf( "5. Waiting for incoming connections..." );
    SOCKET acceptSocket;
    while (1)
    {
        acceptSocket = SOCKET_ERROR;
        while ( acceptSocket == SOCKET_ERROR )
            acceptSocket = accept( *sock, NULL, NULL );

        if ( acceptSocket == INVALID_SOCKET )
            printf( ">>>Error at accept(): %ld\n" , WSAGetLastError() );
        else
            printf( "Connection accepted\n" );
        *sock = acceptSocket;
        break;
    }
}

void main()
{
    SOCKET sock;

    initializeSimulator();

    winsockInit();
    createSocket(&sock);
    bindSocket(&sock);
    listenSocket(sock);
    waitingForConnection(&sock);

    /****************Send and receive data.****************/
    int bytesSent;
    int bytesRecv = SOCKET_ERROR;
    char *reply = NULL;
    char recvbuf[0x3fff] = "";
    State state = INITIAL;

    // while(recvbuf[1] != 'k')
    // {
        /*
         *  Recv ACK
         */
        // bytesRecv = recv( sock, recvbuf, 0x3fff, 0 );

        /*
         *  Response ACK
         */
        // bytesSent = send( sock, "+", strlen("+"), 0 );

        /*
         *  Recv packet
         */
        /* bytesRecv = recv( sock, recvbuf, 0x3fff, 0 );
        printf( "\nBytes Recv: %ld\n", bytesRecv );
        recvbuf[bytesRecv] = '\0';
        printf( "recvbuf: %s\n", recvbuf );

        reply = serveRSP(recvbuf); */

        /*
         *  Response packet
         */
        /* bytesSent = send( sock, reply, strlen(reply), 0 );
        printf( "\nBytes Sent: %ld\n", bytesSent );
        printf( "sendbuf: %s\n", reply );

        free(reply);
    } */

    while(1)
    {
        bytesRecv = recv( sock, recvbuf, 0x3fff, 0 );
        printf( "\nBytes Recv: %ld\n", bytesRecv );
        recvbuf[bytesRecv] = '\0';
        printf( "recvbuf: %s\n", recvbuf );

        // while(state == ACK || state == NACK)
        do {
            reply = rsp_state(&state, recvbuf);
        }while(state == ACK || state == NACK || state == KILL);

        printf("reply: %s\n", reply);
        bytesSent = send( sock, reply, strlen(reply), 0 );

        if(!strcmp("k", reply))
        {
            free(reply);
            break;
        }

        free(reply);
    }
    
    // deleteAllBreakpoint(&bp);

    /****************Close our socket entirely****************/
	closesocket(sock);

	/****************Cleanup Winsock****************/
	WSACleanup();
}