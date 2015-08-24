#ifndef stateRSP_H
#define stateRSP_H

#include "State.h"
#include <winsock2.h>
#pragma comment(lib,<ws2_32.lib>)       //Winsock Library

typedef struct RspData RspData;

struct RspData
{
  State state;
  SOCKET sock;
};

// char *rspState(RspData *rspData, char *data);
void rspState(RspData *rspData, char *data);

#endif // stateRSP_H
