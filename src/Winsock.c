#include <stdio.h>
#include <winsock2.h>
// #include "ChkSumCal.h"

#pragma comment(lib,<ws2_32.lib>)       //Winsock Library

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
    char sendbuf[100] = "";
    char recvbuf[100] = "";

    /*
     *  Recv packet
     *      ==>  + (ACK)
     */
    bytesRecv = recv( sock, recvbuf, 100, 0 );
    printf( "\nBytes Recv: %ld\n", bytesRecv );
    recvbuf[bytesRecv] = '\0';
    printf( "recvbuf: %s\n", recvbuf );

    /*
     *  Response packet
     *      ==>  + (ACK)
     */
    strcpy( sendbuf, "+" );
    bytesSent = send( sock, sendbuf, strlen(sendbuf), 0 );
    printf( "\nBytes Sent: %ld\n", bytesSent );
    printf( "sendbuf: %s\n", sendbuf );

    /*
     *  Recv packet
     *      ==>  $qSupported:multiprocess+;qRelocInsn+#2a
     */
    bytesRecv = recv( sock, recvbuf, 100, 0 );
    printf( "\nBytes Recv: %ld\n", bytesRecv );
    recvbuf[bytesRecv] = '\0';
    printf( "recvbuf: %s\n", recvbuf );

    /*
     *  Response packet
     *      ==>  $PacketSize=3fff;qXfer:memory-map:read+;qXfer:features:read+#f0
     */
    // strcpy( sendbuf, "+$PacketSize=3fff;qXfer:memory-map:read+;qXfer:features:read-;QStartNoAckMode+#08" );
    strcpy( sendbuf, "+$PacketSize=171;qXfer:memory-map:read+;qXfer:features:read+#24" );
    // strcpy( sendbuf, "+$PacketSize=4000;multiprocess+#84" );
    bytesSent = send( sock, sendbuf, strlen(sendbuf), 0 );
    printf( "\nBytes Sent: %ld\n", bytesSent );
    printf( "sendbuf: %s\n", sendbuf );

    /*
     *  Recv packet
     *      ==>  + (ACK)
     */
    bytesRecv = recv( sock, recvbuf, 100, 0 );
    // printf( "\nBytes Recv: %ld\n", bytesRecv );
    // recvbuf[bytesRecv] = '\0';
    // printf( "recvbuf: %s\n", recvbuf );

    /*
     *  Response packet
     *      ==>  + (ACK)
     */
    strcpy( sendbuf, "+" );
    bytesSent = send( sock, sendbuf, strlen(sendbuf), 0 );
    // printf( "\nBytes Sent: %ld\n", bytesSent );
    // printf( "sendbuf: %s\n", sendbuf );

    /*
     *  Recv packet
     *      ==>  $qTStatus#49
     */
    bytesRecv = recv( sock, recvbuf, 100, 0 );
    printf( "\nBytes Recv: %ld\n", bytesRecv );
    recvbuf[bytesRecv] = '\0';
    printf( "recvbuf: %s\n", recvbuf );

    /*
     *  Response packet
     *      ==>  $T0#84
     */
    strcpy( sendbuf, "+$T0#84" );
    bytesSent = send( sock, sendbuf, strlen(sendbuf), 0 );
    printf( "\nBytes Sent: %ld\n", bytesSent );
    printf( "sendbuf: %s\n", sendbuf );

    /*
     *  Recv packet
     *      ==>  + (ACK)
     */
    bytesRecv = recv( sock, recvbuf, 100, 0 );
    // printf( "\nBytes Recv: %ld\n", bytesRecv );
    // recvbuf[bytesRecv] = '\0';
    // printf( "recvbuf: %s\n", recvbuf );

    /*
     *  Response packet
     *      ==>  + (ACK)
     */
    strcpy( sendbuf, "+" );
    bytesSent = send( sock, sendbuf, strlen(sendbuf), 0 );
    // printf( "\nBytes Sent: %ld\n", bytesSent );
    // printf( "sendbuf: %s\n", sendbuf );

    /*
     *  Recv packet
     *      ==>  $qTfV#81
     */
    bytesRecv = recv( sock, recvbuf, 100, 0 );
    printf( "\nBytes Recv: %ld\n", bytesRecv );
    recvbuf[bytesRecv] = '\0';
    printf( "recvbuf: %s\n", recvbuf );

    /*
     *  Response packet
     *      ==>  $#00
     */
    strcpy( sendbuf, "+$#00" );
    bytesSent = send( sock, sendbuf, strlen(sendbuf), 0 );
    printf( "\nBytes Sent: %ld\n", bytesSent );
    printf( "sendbuf: %s\n", sendbuf );

    /*
     *  Recv packet
     *      ==>  + (ACK)
     */
    bytesRecv = recv( sock, recvbuf, 100, 0 );
    // printf( "\nBytes Recv: %ld\n", bytesRecv );
    // recvbuf[bytesRecv] = '\0';
    // printf( "recvbuf: %s\n", recvbuf );

    /*
     *  Response packet
     *      ==>  + (ACK)
     */
    strcpy( sendbuf, "+" );
    bytesSent = send( sock, sendbuf, strlen(sendbuf), 0 );
    // printf( "\nBytes Sent: %ld\n", bytesSent );
    // printf( "sendbuf: %s\n", sendbuf );

    /*
     *  Recv packet
     *      ==>  $?#3f
     */
    bytesRecv = recv( sock, recvbuf, 100, 0 );
    printf( "\nBytes Recv: %ld\n", bytesRecv );
    recvbuf[bytesRecv] = '\0';
    printf( "recvbuf: %s\n", recvbuf );
    
    /*
     *  Response packet
     *      ==>  $S05#b8
     */
    strcpy( sendbuf, "+$S05#b8" );
    bytesSent = send( sock, sendbuf, strlen(sendbuf), 0 );
    printf( "\nBytes Sent: %ld\n", bytesSent );
    printf( "sendbuf: %s\n", sendbuf );
    
    /*
     *  Recv packet
     *      ==>  + (ACK)
     */
    bytesRecv = recv( sock, recvbuf, 100, 0 );
    // printf( "\nBytes Recv: %ld\n", bytesRecv );
    // recvbuf[bytesRecv] = '\0';
    // printf( "recvbuf: %s\n", recvbuf );

    /*
     *  Response packet
     *      ==>  + (ACK)
     */
    strcpy( sendbuf, "+" );
    bytesSent = send( sock, sendbuf, strlen(sendbuf), 0 );
    // printf( "\nBytes Sent: %ld\n", bytesSent );
    // printf( "sendbuf: %s\n", sendbuf );
    
    /*
     *  Recv packet
     *      ==>  $qfThreadInfo#bb
     */
    bytesRecv = recv( sock, recvbuf, 100, 0 );
    printf( "\nBytes Recv: %ld\n", bytesRecv );
    recvbuf[bytesRecv] = '\0';
    printf( "recvbuf: %s\n", recvbuf );
    
    /*
     *  Response packet
     *      ==>  $m01,02#5c
     */
    strcpy( sendbuf, "+$m01,02#5c" );
    bytesSent = send( sock, sendbuf, strlen(sendbuf), 0 );
    printf( "\nBytes Sent: %ld\n", bytesSent );
    printf( "sendbuf: %s\n", sendbuf );
    
    /*
     *  Recv packet
     *      ==>  + (ACK)
     */
    bytesRecv = recv( sock, recvbuf, 100, 0 );
    // printf( "\nBytes Recv: %ld\n", bytesRecv );
    // recvbuf[bytesRecv] = '\0';
    // printf( "recvbuf: %s\n", recvbuf );

    /*
     *  Response packet
     *      ==>  + (ACK)
     */
    strcpy( sendbuf, "+" );
    bytesSent = send( sock, sendbuf, strlen(sendbuf), 0 );
    // printf( "\nBytes Sent: %ld\n", bytesSent );
    // printf( "sendbuf: %s\n", sendbuf );
    
    /*
     *  Recv packet
     *      ==>  $qAttached#8f
     */
    bytesRecv = recv( sock, recvbuf, 100, 0 );
    printf( "\nBytes Recv: %ld\n", bytesRecv );
    recvbuf[bytesRecv] = '\0';
    printf( "recvbuf: %s\n", recvbuf );
    
    /*
     *  Response packet
     *      ==>  $1#31
     */
    strcpy( sendbuf, "+$l#31" );
    bytesSent = send( sock, sendbuf, strlen(sendbuf), 0 );
    printf( "\nBytes Sent: %ld\n", bytesSent );
    printf( "sendbuf: %s\n", sendbuf );
    
    /*
     *  Recv packet
     *      ==>  + (ACK)
     */
    bytesRecv = recv( sock, recvbuf, 100, 0 );
    // printf( "\nBytes Recv: %ld\n", bytesRecv );
    // recvbuf[bytesRecv] = '\0';
    // printf( "recvbuf: %s\n", recvbuf );

    /*
     *  Response packet
     *      ==>  + (ACK)
     */
    strcpy( sendbuf, "+" );
    bytesSent = send( sock, sendbuf, strlen(sendbuf), 0 );
    // printf( "\nBytes Sent: %ld\n", bytesSent );
    // printf( "sendbuf: %s\n", sendbuf );
    
    /*
     *  Recv packet
     *      ==>  $qsThreadInfo#c8
     */
    bytesRecv = recv( sock, recvbuf, 100, 0 );
    printf( "\nBytes Recv: %ld\n", bytesRecv );
    recvbuf[bytesRecv] = '\0';
    printf( "recvbuf: %s\n", recvbuf );
    
    /*
     *  Response packet
     *      ==>  $1#31
     */
    strcpy( sendbuf, "+$1#31" );
    bytesSent = send( sock, sendbuf, strlen(sendbuf), 0 );
    printf( "\nBytes Sent: %ld\n", bytesSent );
    printf( "sendbuf: %s\n", sendbuf );
    
    /*
     *  Recv packet
     *      ==>  + (ACK)
     */
    bytesRecv = recv( sock, recvbuf, 100, 0 );
    // printf( "\nBytes Recv: %ld\n", bytesRecv );
    // recvbuf[bytesRecv] = '\0';
    // printf( "recvbuf: %s\n", recvbuf );

    /*
     *  Response packet
     *      ==>  + (ACK)
     */
    strcpy( sendbuf, "+" );
    bytesSent = send( sock, sendbuf, strlen(sendbuf), 0 );
    // printf( "\nBytes Sent: %ld\n", bytesSent );
    // printf( "sendbuf: %s\n", sendbuf );
    
    /*
     *  Recv packet
     *      ==>  $Hc-1#09
     */
    bytesRecv = recv( sock, recvbuf, 100, 0 );
    printf( "\nBytes Recv: %ld\n", bytesRecv );
    recvbuf[bytesRecv] = '\0';
    printf( "recvbuf: %s\n", recvbuf );
    
    /*
     *  Response packet
     *      ==>  $OK#9a
     */
    strcpy( sendbuf, "+$OK#9a" );
    bytesSent = send( sock, sendbuf, strlen(sendbuf), 0 );
    printf( "\nBytes Sent: %ld\n", bytesSent );
    printf( "sendbuf: %s\n", sendbuf );
    
    /*
     *  Recv packet
     *      ==>  + (ACK)
     */
    bytesRecv = recv( sock, recvbuf, 100, 0 );
    // printf( "\nBytes Recv: %ld\n", bytesRecv );
    // recvbuf[bytesRecv] = '\0';
    // printf( "recvbuf: %s\n", recvbuf );

    /*
     *  Response packet
     *      ==>  + (ACK)
     */
    strcpy( sendbuf, "+" );
    bytesSent = send( sock, sendbuf, strlen(sendbuf), 0 );
    // printf( "\nBytes Sent: %ld\n", bytesSent );
    // printf( "sendbuf: %s\n", sendbuf );
    
    /*
     *  Recv packet
     *      ==>  $qC#b4
     */
    bytesRecv = recv( sock, recvbuf, 100, 0 );
    printf( "\nBytes Recv: %ld\n", bytesRecv );
    recvbuf[bytesRecv] = '\0';
    printf( "recvbuf: %s\n", recvbuf );
    
    /*
     *  Response packet
     *      ==>  $#00
     */
    strcpy( sendbuf, "+$#00" );
    bytesSent = send( sock, sendbuf, strlen(sendbuf), 0 );
    printf( "\nBytes Sent: %ld\n", bytesSent );
    printf( "sendbuf: %s\n", sendbuf );
    
    /*
     *  Recv packet
     *      ==>  + (ACK)
     */
    bytesRecv = recv( sock, recvbuf, 100, 0 );
    // printf( "\nBytes Recv: %ld\n", bytesRecv );
    // recvbuf[bytesRecv] = '\0';
    // printf( "recvbuf: %s\n", recvbuf );

    /*
     *  Response packet
     *      ==>  + (ACK)
     */
    strcpy( sendbuf, "+" );
    bytesSent = send( sock, sendbuf, strlen(sendbuf), 0 );
    // printf( "\nBytes Sent: %ld\n", bytesSent );
    // printf( "sendbuf: %s\n", sendbuf );
    
    /*
     *  Recv packet
     *      ==>  $g#67
     */
    bytesRecv = recv( sock, recvbuf, 100, 0 );
    printf( "\nBytes Recv: %ld\n", bytesRecv );
    recvbuf[bytesRecv] = '\0';
    printf( "recvbuf: %s\n", recvbuf );
    
    /*
     *  Response packet
     *      ==>  $00000000000000000000000000000000000#90
     */
    strcpy( sendbuf, "+$00000000000000000000000000000000000#90" );
    bytesSent = send( sock, sendbuf, strlen(sendbuf), 0 );
    printf( "\nBytes Sent: %ld\n", bytesSent );
    printf( "sendbuf: %s\n", sendbuf );
    
    /*
     *  Recv packet
     *      ==>  + (ACK)
     */
    // bytesRecv = recv( sock, recvbuf, 100, 0 );
    // printf( "\nBytes Recv: %ld\n", bytesRecv );
    // recvbuf[bytesRecv] = '\0';
    // printf( "recvbuf: %s\n", recvbuf );

    /*
     *  Response packet
     *      ==>  + (ACK)
     */
    // strcpy( sendbuf, "+" );
    // bytesSent = send( sock, sendbuf, strlen(sendbuf), 0 );
    // printf( "\nBytes Sent: %ld\n", bytesSent );
    // printf( "sendbuf: %s\n", sendbuf );
    
    /*
     *  Recv packet
     *      ==>  $pf#d6
     */
    // bytesRecv = recv( sock, recvbuf, 100, 0 );
    // printf( "\nBytes Recv: %ld\n", bytesRecv );
    // recvbuf[bytesRecv] = '\0';
    // printf( "recvbuf: %s\n", recvbuf );
    
    /*
     *  Response packet
     *      ==>  $00000000000000000000000000000000000#90
     */
    // strcpy( sendbuf, "+$00#c0" );
    // bytesSent = send( sock, sendbuf, strlen(sendbuf), 0 );
    // printf( "\nBytes Sent: %ld\n", bytesSent );
    // printf( "sendbuf: %s\n", sendbuf );
    
    /****************Close our socket entirely****************/
	closesocket(sock);

	/****************Cleanup Winsock****************/
	WSACleanup();
}