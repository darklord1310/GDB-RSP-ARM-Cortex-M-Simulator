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

/****************Send data.****************/
int sendBuffer(SOCKET *sock, char *sendbuf)
{
    int bytesSent;

    bytesSent = send( *sock, sendbuf, strlen(sendbuf), 0 );
    printf( "\nBytes Sent: %ld\n", bytesSent );

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

void main()
{
    SOCKET sock;

    initializeSimulator();

    winsockInit();
    createSocket(&sock);
    bindSocket(&sock);
    listenSocket(sock);
    waitingForConnection(&sock);

    int bytesSent;
    int bytesRecv = SOCKET_ERROR;
    char *reply = NULL;
    char recvbuf[PACKET_SIZE] = "";
    State state = INITIAL;

    while(1)
    {
        bytesRecv = receiveBuffer(&sock, recvbuf);
        if(bytesRecv != -1)
        {
            recvbuf[bytesRecv] = '\0';
            printf( "recvbuf: %s\n", recvbuf );
        }
        else
            state = NACK;

        do {
            reply = rsp_state(&state, recvbuf);
        }while(state == ACK || state == NACK || state == KILL);

        if(!strcmp("k", reply))
        {
            free(reply);
            break;
        }
        else
        {
            bytesSent = sendBuffer(&sock, reply);
            printf("reply: %s\n", reply);
        }

        free(reply);
    }

    // deleteAllBreakpoint(&bp);

    /****************Close our socket entirely****************/
	closesocket(sock);

	/****************Cleanup Winsock****************/
	WSACleanup();
}

    /* while(recvbuf[1] != 'k')
    { */
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
