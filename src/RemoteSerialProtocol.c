#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include "RemoteSerialProtocol.h"
#include "Packet.h"

/*
 * This function handle all the query packet receive from
 * gdb client and return the appropriate message back to it
 *
 * Input:
 *      data    packet receive from gdb client
 *
 * Return:
 *      packet  complete packet to reply to gdb client
 */
char *handleQueryPacket(char *data)
{
    char *packet = NULL;

    if(data[2] == 'P' || data[2] == 'C' || data[2] == 'L')
        packet = completePacket("");

    if(strcmp(strstr(data, "Supported"), "Supported"))
        packet = completePacket("qRelocInsn-");
    // else if()

    printf("packet: %p\n", packet);
    return packet;
}
