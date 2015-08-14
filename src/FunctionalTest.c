#include <stdio.h>
#include <malloc.h>
#include "FunctionalTest.h"
#include "ServeRSP.h"
#include "Packet.h"
#include "RemoteSerialProtocol.h"

void tarRemoteCommand()
{
    char packet[16][1024] = {
                                {"$qSupported:multiprocess+;qRelocInsn+#2a"},
                                {"$Hg0#df"},
                                {"$qXfer:features:read:target.xml:0,fff#7d"},
                                {"$qXfer:features:read:arm-m-profile.xml:0,fff#ee"},
                                {"$qXfer:features:read:arm-vfpv2.xml:0,fff#57"},
                                {"$qTStatus#49"},
                                {"$?#3f"},
                                {"$qfThreadInfo#bb"},
                                {"$qL1200000000000000000#50"},
                                {"$Hc-1#09"},
                                {"$qC#b4"},
                                {"$qAttached#8f"},
                                {"$qOffsets#4b"},
                                {"$g#67"},
                                {"$m0,4#fd"},
                                {"$qSymbol::#5b"}
                            };
    char *reply = NULL;
    int i = 0;

    for(i = 0; i < 16; i++)
    {
        reply = serveRSP(packet[i]);
    }

    free(reply);
}

void loadSimpleAssembly()
{
    char packet[4][1024] = {
                                {"$M8000000,1ac:ffff0220ad010008c1010008c1010008c1010008c1010008c101000800000000000000000000000000000000c1010008c101000800000000c1010008c1010008c1010008c1010008c1010008c1010008c1010008c1010008c1010008c1010008c1010008c1010008c1010008c1010008c1010008c1010008c1010008c1010008c1010008c1010008c1010008c1010008c1010008c1010008c1010008c1010008c1010008c1010008c1010008c1010008c1010008c1010008c1010008c1010008c1010008c1010008c1010008c1010008c1010008c1010008c1010008c1010008c1010008c1010008c1010008c1010008c1010008c1010008c1010008c1010008c1010008c1010008c1010008c1010008c1010008c1010008c1010008c1010008c1010008c1010008c1010008c1010008c1010008c1010008c1010008c1010008c1010008c1010008c1010008c1010008c1010008c1010008c1010008c1010008c1010008c1010008c1010008c1010008c1010008c1010008c101000800000000c1010008c1010008c1010008c1010008c1010008c1010008c1010008c1010008c1010008c1010008c1010008#61"},
                                {"$M80001ac,18:0348052101600168013101602022fae700000020fee70000#64"},
                                {"$M80001c4,4:04000000#fb"},
                                {"$Pf=ac010008#e0"}
                            };
    char *reply = NULL;
    int i = 0;

    for(i = 0; i < 4; i++)
    {
        reply = serveRSP(packet[i]);
    }

    free(reply);
}

void loadITBlock()
{
    char packet[3][1024] = {
                                {"$M8000000,1ac:ffff0220ad010008c1010008c1010008c1010008c1010008c101000800000000000000000000000000000000c1010008c101000800000000c1010008c1010008c1010008c1010008c1010008c1010008c1010008c1010008c1010008c1010008c1010008c1010008c1010008c1010008c1010008c1010008c1010008c1010008c1010008c1010008c1010008c1010008c1010008c1010008c1010008c1010008c1010008c1010008c1010008c1010008c1010008c1010008c1010008c1010008c1010008c1010008c1010008c1010008c1010008c1010008c1010008c1010008c1010008c1010008c1010008c1010008c1010008c1010008c1010008c1010008c1010008c1010008c1010008c1010008c1010008c1010008c1010008c1010008c1010008c1010008c1010008c1010008c1010008c1010008c1010008c1010008c1010008c1010008c1010008c1010008c1010008c1010008c1010008c1010008c1010008c1010008c1010008c1010008c1010008c1010008c101000800000000c1010008c1010008c1010008c1010008c1010008c1010008c1010008c1010008c1010008c1010008c1010008#61"},
                                {"$M80001ac,18:38bf81420cbfc141da412abfda40ec40f740fee7fee70000#98"},
                                {"$Pf=ac010008#e0"}
                            };
    char *reply = NULL;
    int i = 0;

    for(i = 0; i < 3; i++)
    {
        reply = serveRSP(packet[i]);
    }

    free(reply);
}

void singleStep()
{
    char *reply = serveRSP("$s#73");
    free(reply);
}

void storeAffectedReg(int regNum, unsigned int regValue)
{
    reg.regNum = regNum;
    reg.regValue = regValue;
}
