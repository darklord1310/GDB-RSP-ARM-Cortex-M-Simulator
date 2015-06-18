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
        case 'q':
            packet = handleQueryPacket(data);
            break;
        default:
            break;
    }

    return packet;
}