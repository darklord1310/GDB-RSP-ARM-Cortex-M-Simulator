#ifndef gdbserver_H
#define gdbserver_H

#include <winsock2.h>
#pragma comment(lib,<ws2_32.lib>)       //Winsock Library

#define LOCAL_HOST_ADD  "127.0.0.1"
#define DEFAULT_PORT    2010
#define PACKET_SIZE     0x3fff

// void main();
void winsockInit();
void createSocket(SOCKET *sock);
void bindSocket(SOCKET *sock);
void listenSocket(SOCKET *sock);
void waitingForConnection(SOCKET *sock);
int sendBuffer(SOCKET *sock, char *sendbuf);
int receiveBuffer(SOCKET *sock, char *recvbuf);
void sendReply(SOCKET *sock, char *reply);

#endif // gdbserver_H
