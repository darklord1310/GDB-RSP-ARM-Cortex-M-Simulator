#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include "gdbserver.h"
#include "Packet.h"
#include "RemoteSerialProtocol.h"

char *serveRSP(char *data)
{
    char *packet;

    switch(data[1])
    {
        case 'q':   /* General query */
            packet = handleQueryPacket(data);
            break;
        case 'v':   /*  */
            break;
        case '?':   /* Indicate the reason the target halted */
            break;
        case 'c':   /* Continue */
            break;
        case 's':   /* Step */
            break;
        case 'g':   /* Read all register */
            packet = readAllRegister(data);
            break;
        case 'p':   /* Read single register */
            packet = readSingleRegister(data);
            break;
        case 'P':   /* Write single register */
            packet = gdbCreateMsgPacket("OK");      //Write successfully
            break;
        case 'G':   /* Write all register */
            packet = gdbCreateMsgPacket("OK");      //Write successfully
            break;
        case 'm':   /* Read memory */
            break;
        case 'M':   /* Write memory */
            break;
        case 'z':   /* Remove breakpoint or watchpoint */
            break;
        case 'Z':   /* Insert breakpoint or watchpoint */
            break;
        case 'H':   /* Set thread */
            packet = gdbCreateMsgPacket("");
            break;
        case 'R':   /* Reset */
            break;
        default:
            break;
    }

    return packet;
}