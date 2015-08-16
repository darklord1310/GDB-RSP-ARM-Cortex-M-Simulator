#include <string.h>
#include <malloc.h>
#include <stdio.h>
#include "stateRSP.h"
#include "ServeRSP.h"
#include "Packet.h"

/***********************************************************************
 * State machine to handle communication between gdb client and server.
 *
 * Input:
 *      state       represent the state of the State Machine
 *
 * Return:
 *      packet      string of data reply to gdb
 ***********************************************************************/
char *rsp_state(RspData *rspData, char *data)
{
    char *packet = NULL;
    static int nack = 0;
    
    if(!strcmp("+", data))
    {
        nack = 0;
        sendReply(rspData->sock, "+");
    }
    else if(!strcmp("-", data))
    {
        sendReply(rspData->sock, "-");
    }

    switch(rspData->state)
    {
        case INITIAL:
            if(!strcmp("+", data))
            {
                rspData->state = ACK;
                
            }
            else if(!strcmp("-", data))
            {
                rspData->state = NACK;
                
            }
            break;
        case ACK:
            packet = malloc(2);
            packet[0] = '+';
            packet[1] = '\0';
            nack = 0;
            rspData->state = SERVE_RSP;
            // printf("yes\n");
            break;
        case NACK:
            packet = malloc(2);
            packet[0] = '-';
            packet[1] = '\0';
            nack++;

            if(nack == 5)
                rspData->state = KILL;
            else
                rspData->state = INITIAL;
            break;
        case SERVE_RSP:
            if(!verifyChecksum(data))
            {
                // printf("yes\n");
                packet = malloc(2);
                packet[0] = '-';
                packet[1] = '\0';
            }
            else
            {
                if(!strcmp("$k#6b", data))
                {
                    rspData->state = KILL;
                    break;
                }
                packet = serveRSP(data);
                // printf("yes\n");
            }

            rspData->state = INITIAL;
            break;
        case KILL:
            packet = malloc(2);
            packet[0] = 'k';
            packet[1] = '\0';
            rspData->state = INITIAL;
            break;
        default:
            rspData->state= INITIAL;
            break;
    }

    return packet;
}
