#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include "ServeRSP.h"
#include "Packet.h"
#include "RemoteSerialProtocol.h"
#include "CException.h"
#include "ErrorSignal.h"

char *serveRSP(char *data)
{
    CEXCEPTION_T errorSignal;
    char *packet;

    Try
    {
        switch(data[1])
        {
            case 'q':   /* General query */
                packet = handleQueryPacket(data);
                break;
            case 'v':   /*  */
                packet = gdbCreateMsgPacket("");
                break;
            case '?':   /* Indicate the reason the target halted */
                packet = gdbCreateMsgPacket("S05");
                break;
            case 'c':   /* Continue */
                break;
            case 's':   /* Step */
                packet = step(data);
                break;
            case 'g':   /* Read all register */
                packet = readAllRegister(data);
                break;
            case 'p':   /* Read single register */
                packet = readSingleRegister(data);
                break;
            case 'P':   /* Write single register */
                packet = writeSingleRegister(data);
                break;
            case 'G':   /* Write all register */
                packet = writeAllRegister(data);
                break;
            case 'm':   /* Read memory */
                packet = readMemory(data);
                break;
            case 'M':   /* Write memory */
                packet = writeMemory(data);
                break;
            // case 'X':   /* Write data to memory */
                // writeMemory(data);
                // packet = gdbCreateMsgPacket("OK");
                // break;
            case 'z':   /* Remove breakpoint or watchpoint */
                break;
            case 'Z':   /* Insert breakpoint or watchpoint */
                break;
            case 'H':   /* Set thread */
                packet = gdbCreateMsgPacket("");
                break;
            case 'R':   /* Reset */
                break;
            case 'k':   /* Kill request */
                packet = gdbCreateMsgPacket("");
                break;
            default:
                packet = gdbCreateMsgPacket("");
                break;
        }
    }
    Catch(errorSignal)
    {
        char *asciiString = NULL, errorString[4] = "E";

        printf("Error signal: %d\n", errorSignal);
        asciiString = createdHexToString(errorSignal, 1);
        strcat(errorString, asciiString);
        destroyHexToString(asciiString);
        packet = gdbCreateMsgPacket(errorString);
    }

    return packet;
}