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
char *rsp_state(State *state, char *data)
{
    char *packet = NULL;
    static int nack = 0;

    switch(*state)
    {
        case INITIAL:
            if(!strcmp("+", data))
                *state = ACK;
            else if(!strcmp("-", data))
                *state = NACK;
            break;
        case ACK:
            packet = malloc(2);
            packet[0] = '+';
            packet[1] = '\0';
            nack = 0;
            *state = SERVE_RSP;
            // printf("yes\n");
            break;
        case NACK:
            packet = malloc(2);
            packet[0] = '-';
            packet[1] = '\0';
            nack++;

            if(nack == 5)
                *state = KILL;
            else
                *state = INITIAL;
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
                    *state = KILL;
                    break;
                }
                packet = serveRSP(data);
                // printf("yes\n");
            }

            *state = INITIAL;
            break;
        case KILL:
            packet = malloc(2);
            packet[0] = 'k';
            packet[1] = '\0';
            *state = INITIAL;
            break;
        default:
            *state= INITIAL;
            break;
    }

    return packet;
}