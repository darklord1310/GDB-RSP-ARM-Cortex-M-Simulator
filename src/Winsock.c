/*
*   Socket programming with winsock
*/

#include "stdio.h"
#include "winsock2.h"
#include "windows.h"

#define LOCAL_HOST_ADD  "127.0.0.1"
#define DEFAULT_PORT    8080

#pragma comment(lib,"ws2_32.lib") //Winsock Library

void InitWinsock(WSADATA *wsaData)
{
    if(WSAStartup(MAKEWORD(2,2), wsaData) != 0)
        printf("Failed. Error Code : %d",WSAGetLastError());
    else
        printf("Initialised.");
}

void main(int argc , char *argv[])
{
    WSADATA wsaData;
    SOCKET s, new_socket;
    struct sockaddr_in server, client;
    int c;
    char *message;

    printf("\nInitialising Winsock...");

    InitWinsock(&wsaData);

    if((s = socket(AF_INET , SOCK_STREAM , 0 )) == INVALID_SOCKET)
        printf("\nCould not create socket : %d", WSAGetLastError());

    printf("\nSocket created.\n");

    //Prepare the sockaddr_in structure
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(DEFAULT_PORT);

    //Bind
    if( bind(s ,(struct sockaddr *)&server , sizeof(server)) == SOCKET_ERROR)
        printf("Bind failed with error code : %d" , WSAGetLastError());

    puts("Bind done");

    //Listen to incoming connections
    listen(s , 3);

    //Accept and incoming connection
    puts("Waiting for incoming connections...");

    c = sizeof(struct sockaddr_in);
    new_socket = accept(s , (struct sockaddr *)&client, &c);
    if (new_socket == INVALID_SOCKET)
        printf("accept failed with error code : %d" , WSAGetLastError());

    puts("Connection accepted");

/*    //Reply to client
    message = "Hello Client , I have received your connection. But I have to go now, bye\n";
    send(new_socket , message , strlen(message) , 0);

    getchar(); */

    closesocket(s);
    WSACleanup();
}