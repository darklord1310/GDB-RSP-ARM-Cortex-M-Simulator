#include <stdio.h>
#include "winsock2.h"

#pragma comment(lib,"ws2_32.lib")       //Winsock Library

#define LOCAL_HOST_ADD  "127.0.0.1"
#define SERVER_PORT     2009
#define DEFAULT_PORT    8080

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

    /****************Create a listen socket.****************/
    printf( "2. Creating listen socket............." );
    SOCKET listenSock;
    listenSock = socket( AF_INET, SOCK_STREAM, IPPROTO_TCP );
    if ( listenSock == INVALID_SOCKET )
    {
        printf( ">>>Error at socket(): %ld\n", WSAGetLastError() );
        WSACleanup();
        return;
    }
    else
        printf( "Listen socket created\n" );

    /****************Create a client socket.****************/
    printf( "3. Creating client socket............." );
    SOCKET clientSock;
    clientSock = socket( AF_INET, SOCK_STREAM, IPPROTO_TCP );
    if ( clientSock == INVALID_SOCKET )
    {
        printf( ">>>Error at socket(): %ld\n", WSAGetLastError() );
        WSACleanup();
        return;
    }
    else
        printf( "Client socket created\n" );

    /****************Connect to a server.****************/
    printf( "5. Connecting to server..............." );
    struct sockaddr_in clientService;
    clientService.sin_family = AF_INET;
    clientService.sin_addr.s_addr = inet_addr( LOCAL_HOST_ADD );
    clientService.sin_port = htons( SERVER_PORT );
    if ( connect( clientSock, (SOCKADDR*) &clientService, sizeof(clientService) ) == SOCKET_ERROR )
    {
        printf( ">>>Failed to connect.\n" );
        WSACleanup();
        return;
    }
    else
        printf( "Server connected\n" );
    
    int clientSent;
    int clientRecv = SOCKET_ERROR;
    char clientRecvBuf[100];
    
    strcpy( clientRecvBuf, '+' );
    clientSent = send( clientSock, clientRecvBuf, strlen(clientRecvBuf), 0 );
    
    /****************Socket "keep-alive".****************/
/*    int iOption = 1; // Turn on keep-alive, 0 = disables, 1 = enables
    if (setsockopt(clientSock, SOL_SOCKET, SO_KEEPALIVE, (const char *) &iOption,  sizeof(int)) == SOCKET_ERROR)
       printf( "Set keepalive: Keepalive option failed" );
    else
        printf( "Socket keep alive\n" ); */

    /****************Bind the socket.****************/
    printf( "4. Binding socket....................." );
    struct sockaddr_in service;
    service.sin_family = AF_INET;
    service.sin_addr.s_addr = inet_addr( LOCAL_HOST_ADD );
    service.sin_port = htons( DEFAULT_PORT );
    if ( bind( listenSock, (SOCKADDR*) &service, sizeof(service) ) == SOCKET_ERROR )
    {
        printf( ">>>Error at bind(): %ld\n", WSAGetLastError() );
        closesocket(listenSock);
        return;
    }
    else
        printf( "Bind done\n" );

    /****************Listen on the socket.****************/
    printf( "6. Listening to socket................" );
    if ( listen( listenSock, 1 ) == SOCKET_ERROR )
        printf( ">>>Error listening on socket\n");
    else
        printf( "Listening...\n" );

    /****************Accept connections.****************/
    printf( "7. Waiting for incoming connections..." );
    SOCKET acceptSocket;
    while (1)
    {
        acceptSocket = SOCKET_ERROR;
        while ( acceptSocket == SOCKET_ERROR )
            acceptSocket = accept( listenSock, NULL, NULL );

        if ( acceptSocket == INVALID_SOCKET )
            printf( ">>>Error at accept(): %ld\n" , WSAGetLastError() );
        else
            printf( "Connection accepted\n" );
        listenSock = acceptSocket;
        break;
    }

    /****************Send and receive data.****************/
    int serverSent;
    int serverRecv = SOCKET_ERROR;
    char serverRecvBuf[100];

    // recv
    serverRecv = recv( listenSock, serverRecvBuf, 100, 0 );
    printf( "\nBytes Recv: %ld\n", serverRecv );
    serverRecvBuf[serverRecv] = '\0';
    printf( "recvbuf: %s\n", serverRecvBuf );

    while ( serverRecvBuf[0] != '+' );

    // recv
    serverRecv = recv( listenSock, serverRecvBuf, 100, 0 );
    printf( "\nBytes Recv: %ld\n", serverRecv );
    serverRecvBuf[serverRecv] = '\0';
    printf( "recvbuf: %s\n", serverRecvBuf );

    // send
    serverSent = send( clientSock, serverRecvBuf, strlen(serverRecvBuf), 0 );
    printf( "\nBytes Sent: %ld\n", serverSent );

    ///////////////////////////////////////////////////////
    // recv
/*    clientRecv = recv( clientSock, clientRecvBuf, 100, 0 );
    printf( "\nBytes Recv: %ld\n", clientRecv );
    clientRecvBuf[clientRecv] = '\0';
    printf( "recvbuf: %s\n", clientRecvBuf );

    while ( serverRecvBuf[0] != '+' );

    // recv
    clientRecv = recv( clientSock, clientRecvBuf, 100, 0 );
    printf( "\nBytes Recv: %ld\n", clientRecv );
    clientRecvBuf[clientRecv] = '\0';
    printf( "recvbuf: %s\n", clientRecvBuf );

    clientSent = send( listenSock, clientRecvBuf, strlen(clientRecvBuf), 0 );
    printf( "\nBytes Sent: %ld\n", clientSent ); */

	/****************Close our socket entirely****************/
	closesocket(listenSock);
	closesocket(clientSock);

	/****************Cleanup Winsock****************/
	WSACleanup();
}