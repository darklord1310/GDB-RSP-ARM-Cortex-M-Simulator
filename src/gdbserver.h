#ifndef gdbserver_H
#define gdbserver_H

#include <winsock2.h>
#pragma comment(lib,<ws2_32.lib>)       //Winsock Library

#define LOCAL_HOST_ADD  "127.0.0.1"
#define DEFAULT_PORT    2010

void winsockInit();
void createSocket(SOCKET *sock);
void bindSocket(SOCKET *sock);
void listenSocket(SOCKET sock);
void waitingForConnection(SOCKET *sock);

#endif // gdbserver_H
