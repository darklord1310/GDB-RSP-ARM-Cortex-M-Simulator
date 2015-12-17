/*
    GDB RSP and ARM Simulator

    Copyright (C) 2015 Wong Yan Yin, <jet_wong@hotmail.com>,
    Jackson Teh Ka Sing, <jackson_dmc69@hotmail.com>

    This file is part of GDB RSP and ARM Simulator.

    This program is free software, you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY, without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with This program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include <string.h>
#include <malloc.h>
#include <stdio.h>
#include "stateRSP.h"
#include "ServeRSP.h"
#include "Packet.h"
#include "main/gdbserver.h"

/***********************************************************************
 * State machine to handle communication between gdb client and server.
 *
 * Input:
 *      rspData     pointer to RspData data structure
 *
 * Return:
 *      packet      string of data reply to gdb
 ***********************************************************************/
void rspState(RspData *rspData, char *data)
{
    static int nack = 0;

    if(data[0] == '+')
    {
        switch(data[1])
        {
            case '\0':
                sendBuffer(&(rspData->sock), "+");
                rspData->state = ACK;
                break;
            case '$':
                data++;

                if(!verifyPacket(data))
                {
                    sendBuffer(&(rspData->sock), "-");
                    rspData->state = NACK;
                }
                else
                {
                    sendBuffer(&(rspData->sock), "+");
                    rspData->state = SERVE_RSP;
                }
                break;
            default:
                sendBuffer(&(rspData->sock), "-");
                rspData->state = NACK;
                break;
        }
    }
    else if(data[0] == '-')
    {
        sendBuffer(&(rspData->sock), "-");
        rspData->state = NACK;
    }
    else if(data != NULL && data[0] == '\0')
        rspData->state = NACK;

again:
    switch(rspData->state)
    {
        case INITIAL:
            if(data[0] == '+')
            {
                rspData->state = ACK;
            }
            else if(data[0] == '-')
            {
                rspData->state = NACK;
            }

            break;
        case ACK:
            nack = 0;
            rspData->state = SERVE_RSP;
            break;
        case NACK:
            nack++;

            if(nack == 5)
                rspData->state = KILL;
            else
                rspData->state = INITIAL;
            break;
        case SERVE_RSP:
            if(!strcmp("$k#6b", data))
            {
                rspData->state = KILL;
                break;
            }
            sendBuffer(&(rspData->sock), serveRSP(data));

            rspData->state = INITIAL;
            break;
        case KILL:
            rspData->state = INITIAL;
            break;
        default:
            rspData->state= INITIAL;
            break;
    }

    if(rspData->state == NACK)
        goto again;
}
