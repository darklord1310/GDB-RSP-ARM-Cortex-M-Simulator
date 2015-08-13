#include <malloc.h>
#include <string.h>
#include "unity.h"
#include "FunctionalTest.h"
#include "ServeRSP.h"
#include "Packet.h"
#include "RemoteSerialProtocol.h"
#include "ARMRegisters.h"
#include "MemoryBlock.h"
#include "getAndSetBits.h"
#include "getMask.h"
#include "CException.h"
#include "ErrorSignal.h"
#include "ARMSimulator.h"
#include "ConditionalExecution.h"
#include "StatusRegisters.h"
#include "Thumb16bitsTable.h"
#include "LSLImmediate.h"
#include "LSRImmediate.h"
#include "MOVRegister.h"
#include "ASRImmediate.h"
#include "MOVImmediate.h"
#include "ModifiedImmediateConstant.h"
#include "CMPImmediate.h"
#include "ADDImmediate.h"
#include "SUBImmediate.h"
#include "ADDRegister.h"
#include "SUBRegister.h"
#include "ADDSPRegister.h"
#include "ITandHints.h"
#include "ANDRegister.h"
#include "LSLRegister.h"
#include "LSRRegister.h"
#include "ASRRegister.h"
#include "CMPRegister.h"
#include "CMNRegister.h"
#include "EORRegister.h"
#include "ORRRegister.h"
#include "RORRegister.h"
#include "MVNRegister.h"
#include "BICRegister.h"
#include "ADCRegister.h"
#include "BX.h"
#include "BLXRegister.h"
#include "MULRegister.h"
#include "TSTRegister.h"
#include "RSBImmediate.h"
#include "SBCRegister.h"
#include "UnconditionalAndConditionalBranch.h"
#include "STRRegister.h"
#include "LDRImmediate.h"
#include "LDRLiteral.h"
#include "SVC.h"
#include "ADR.h"
#include "ADDSPImmediate.h"
#include "STRImmediate.h"
#include "LDRRegister.h"
#include "REV.h"
#include "SignedAndUnsignedExtend.h"
#include "CBZandCBNZ.h"
#include "PUSH.h"
#include "POP.h"
#include "SUBSPImmediate.h"
#include "LoadAndWriteMemory.h"
#include "Thumb32bitsTable.h"
#include "ShiftOperation.h"
#include "CustomTypeAssertion.h"

/* extern char *targetCortexM4_XML;
extern char *arm_m_profile;
extern char *arm_vfpv2;
extern int watchpointIndex; */

void setUp(void)
{
    initializeSimulator();
    initializeWatchpoint();
}

void tearDown(void)
{
}

void test_gdb_tar_remote_command(void)
{
    /* char *packet = NULL;

    reply = serveRSP(qSupported);
    packet = gdbCreateMsgPacket("PacketSize=3fff;qXfer:memory-map:read-;qXfer:features:read+;qRelocInsn-");
    TEST_ASSERT_EQUAL_STRING(packet, reply);
    free(packet);
    free(reply); */

    tarRemoteCommand();
    loadMemory();
    singleStep();
    storeAffectedReg(R0, 0x20000000);
    TEST_ASSERT_EQUAL_Register(&reg);
    storeAffectedReg(PC_REG, 0x080001ae);
    TEST_ASSERT_EQUAL_Register(&reg);
}
