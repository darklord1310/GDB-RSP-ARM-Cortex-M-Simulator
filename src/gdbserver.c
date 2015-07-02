#include <stdio.h>
#include <winsock2.h>
#include <malloc.h>
#include "ServeRSP.h"

#pragma comment(lib,<ws2_32.lib>)       //Winsock Library

#define LOCAL_HOST_ADD  "127.0.0.1"
#define DEFAULT_PORT    2010

void main()
{
    /****************Initialize Winsock.****************/
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

    /****************Create a socket.****************/
    printf( "2. Creating socket...................." );
    SOCKET sock;
    sock = socket( AF_INET, SOCK_STREAM, IPPROTO_TCP );
    if ( sock == INVALID_SOCKET )
    {
        printf( ">>>Error at socket(): %ld\n", WSAGetLastError() );
        WSACleanup();
        return;
    }
    else
        printf( "Socket created\n" );

    /****************Bind the socket.****************/
    printf( "3. Binding socket....................." );
    struct sockaddr_in service;
    service.sin_family = AF_INET;
    service.sin_addr.s_addr = inet_addr( LOCAL_HOST_ADD );
    service.sin_port = htons( DEFAULT_PORT );
    if ( bind( sock, (SOCKADDR*) &service, sizeof(service) ) == SOCKET_ERROR )
    {
        printf( ">>>Error at bind(): %ld\n", WSAGetLastError() );
        closesocket(sock);
        return;
    }
    else
        printf( "Bind done\n" );

    /****************Listen on the socket.****************/
    printf( "4. Listening to socket................" );
    if ( listen( sock, 1 ) == SOCKET_ERROR )
        printf( ">>>Error listening on socket\n");
    else
        printf( "Listening...\n" );

    /****************Accept connections.****************/
    printf( "5. Waiting for incoming connections..." );
    SOCKET acceptSocket;
    while (1)
    {
        acceptSocket = SOCKET_ERROR;
        while ( acceptSocket == SOCKET_ERROR )
            acceptSocket = accept( sock, NULL, NULL );

        if ( acceptSocket == INVALID_SOCKET )
            printf( ">>>Error at accept(): %ld\n" , WSAGetLastError() );
        else
            printf( "Connection accepted\n" );
        sock = acceptSocket;
        break;
    }

    /****************Send and receive data.****************/
    int bytesSent;
    int bytesRecv = SOCKET_ERROR;
    char *reply = NULL;
    char recvbuf[200] = "";

    while(1)
    {
    /*
     *  Recv packet
     *      ==>  + (ACK)
     */
    bytesRecv = recv( sock, recvbuf, 100, 0 );

    /*
     *  Response packet
     *      ==>  + (ACK)
     */
    bytesSent = send( sock, "+", strlen("+"), 0 );

    /*
     *  Recv packet
     */
    bytesRecv = recv( sock, recvbuf, 100, 0 );
    printf( "\nBytes Recv: %ld\n", bytesRecv );
    recvbuf[bytesRecv] = '\0';
    printf( "recvbuf: %s\n", recvbuf );

    reply = serveRSP(recvbuf);

    /*
     *  Response packet
     */
    bytesSent = send( sock, reply, strlen(reply), 0 );
    printf( "\nBytes Sent: %ld\n", bytesSent );
    printf( "sendbuf: %s\n", reply );

    free(reply);
    }

    /****************Close our socket entirely****************/
	closesocket(sock);

	/****************Cleanup Winsock****************/
	WSACleanup();
}