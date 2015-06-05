#include <stdio.h>
#include "winsock2.h"

#pragma comment(lib,"ws2_32.lib")       //Winsock Library

#define LOCAL_HOST_ADD  "127.0.0.1"
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

    /****************Connect to a server.****************/
    printf( "3. Connecting to server..............." );
    struct sockaddr_in clientService;
    clientService.sin_family = AF_INET;
    clientService.sin_addr.s_addr = inet_addr( LOCAL_HOST_ADD );
    clientService.sin_port = htons( DEFAULT_PORT );
    if ( connect( sock, (SOCKADDR*) &clientService, sizeof(clientService) ) == SOCKET_ERROR )
    {
        printf( ">>>Failed to connect.\n" );
        WSACleanup();
        return;
    }
    else
        printf( "Server connected\n" );

    /****************Send and receive data.****************/
    int bytesSent;
    int bytesRecv = SOCKET_ERROR;
    char sendbuf[100] = "Client: Sending data.";
    char recvbuf[100] = "";

    bytesSent = send( sock, sendbuf, strlen(sendbuf), 0 );
    printf( "\nBytes Sent: %ld\n", bytesSent );
    printf( "sendbuf: %s\n", sendbuf );

    while( bytesRecv == SOCKET_ERROR )
    {
        bytesRecv = recv( sock, recvbuf, 100, 0 );

        if ( bytesRecv == 0 || bytesRecv == WSAECONNRESET )
        {
            printf( "\nConnection Closed.\n");
            break;
        }

        if (bytesRecv < 0)
            return;

        printf( "\nBytes Recv: %ld\n", bytesRecv );
        printf( "recvbuf: %s\n", recvbuf );
    }
    /*
    // recv
    bytesRecv = recv( sock, recvbuf, 100, 0 );
    printf( "\nBytes Recv: %ld\n", bytesRecv );
    recvbuf[bytesRecv] = '\0';
    printf( "recvbuf: %s\n", recvbuf );

    // recv
    bytesRecv = recv( sock, recvbuf, 100, 0 );
    printf( "\nBytes Recv: %ld\n", bytesRecv );
    recvbuf[bytesRecv] = '\0';
    printf( "recvbuf: %s\n", recvbuf );

    // send
    strcpy( sendbuf, "+$PacketSize=4000;qXfer:auxv:read-;qXfer:features:read-;multiprocess-#a5" );
    // strcpy( sendbuf, "+$PacketSize=119#cb" );
    // strcpy( sendbuf, "+$qSupported#37" );
    bytesSent = send( sock, sendbuf, strlen(sendbuf), 0 );
    printf( "\nBytes Sent: %ld\n", bytesSent );
    printf( "sendbuf: %s\n", sendbuf );

    // recv
    bytesRecv = recv( sock, recvbuf, 100, 0 );
    printf( "\nBytes Recv: %ld\n", bytesRecv );
    recvbuf[bytesRecv] = '\0';
    printf( "recvbuf: %s\n", recvbuf );

    // send
    // strcpy( sendbuf, "+$S00#b3" );
    strcpy( sendbuf, "+$OK#9a" );
    bytesSent = send( sock, sendbuf, strlen(sendbuf), 0 );
    printf( "\nBytes Sent: %ld\n", bytesSent );
    printf( "sendbuf: %s\n", sendbuf );

    // recv
    bytesRecv = recv( sock, recvbuf, 100, 0 );
    printf( "\nBytes Recv: %ld\n", bytesRecv );
    recvbuf[bytesRecv] = '\0';
    printf( "recvbuf: %s\n", recvbuf );

    // send
    strcpy( sendbuf, "+$OK#9a" );
    // strcpy( sendbuf, "+$tnotrun:0#84" );
    bytesSent = send( sock, sendbuf, strlen(sendbuf), 0 );
    printf( "\nBytes Sent: %ld\n", bytesSent );
    printf( "sendbuf: %s\n", sendbuf );

    // recv
    bytesRecv = recv( sock, recvbuf, 100, 0 );
    printf( "\nBytes Recv: %ld\n", bytesRecv );
    recvbuf[bytesRecv] = '\0';
    printf( "recvbuf: %s\n", recvbuf ); */

	/****************Close our socket entirely****************/
	closesocket(sock);

	/****************Cleanup Winsock****************/
	WSACleanup();
}