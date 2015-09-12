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
#include "ANDImmediate.h"
#include "TSTImmediate.h"
#include "BICImmediate.h"
#include "ORRImmediate.h"
#include "ORNImmediate.h"
#include "MVNImmediate.h"
#include "EORImmediate.h"
#include "TEQImmediate.h"
#include "CMNImmediate.h"
#include "ADCImmediate.h"
#include "SBCImmediate.h"
#include "MOVT.h"
#include "SignedAndUnsignedSaturate.h"
#include "SignedAndUnsignedBitFieldExtract.h"
#include "BFIandBFC.h"
#include "RRX.h"
#include "RORImmediate.h"
#include "ORNRegister.h"
#include "TEQRegister.h"
#include "RSBRegister.h"
#include "CLZ.h"
#include "NOP.h"
#include "MLA.h"
#include "MLS.h"
#include "SignedUnsignedLongMultiplyDivide.h"


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

/*
Simple assembly
080001ac <Reset_Handler>:
 80001ac:       4803            ldr     r0, [pc, #12]   ; (80001bc <again+0xa>)
 80001ae:       2105            movs    r1, #5
 80001b0:       6001            str     r1, [r0, #0]

080001b2 <again>:
 80001b2:       6801            ldr     r1, [r0, #0]
 80001b4:       3101            adds    r1, #1
 80001b6:       6001            str     r1, [r0, #0]
 80001b8:       2220            movs    r2, #32
 80001ba:       e7fa            b.n     80001b2 <again>
 80001bc:       20000000        .word   0x20000000

080001c0 <ADC_IRQHandler>:
 80001c0:       e7fe            b.n     80001c0 <ADC_IRQHandler>
*/
void test_simple_assembly_code(void)
{
    /* char *packet = NULL;

    reply = serveRSP(qSupported);
    packet = gdbCreateMsgPacket("PacketSize=3fff;qXfer:memory-map:read-;qXfer:features:read+;qRelocInsn-");
    TEST_ASSERT_EQUAL_STRING(packet, reply);
    free(packet);
    free(reply); */

    // tarRemoteCommand();
    loadSimpleAssembly();

    singleStep();                           //ldr     r0, [pc, #12]
    storeAffectedReg(R0, 0x20000000);
    TEST_ASSERT_EQUAL_Register(&reg);
    storeAffectedReg(PC_REG, 0x080001ae);
    TEST_ASSERT_EQUAL_Register(&reg);

    singleStep();                           //movs    r1, #5
    storeAffectedReg(R1, 0x5);
    TEST_ASSERT_EQUAL_Register(&reg);
    storeAffectedReg(PC_REG, 0x080001b0);
    TEST_ASSERT_EQUAL_Register(&reg);

    singleStep();                           //str     r1, [r0, #0]
    TEST_ASSERT_EQUAL(0x5, memoryBlock[virtualMemToPhysicalMem(0x20000000)]);
    storeAffectedReg(PC_REG, 0x080001b2);
    TEST_ASSERT_EQUAL_Register(&reg);

    singleStep();                           //ldr     r1, [r0, #0]
    storeAffectedReg(R1, 0x5);
    TEST_ASSERT_EQUAL_Register(&reg);
    storeAffectedReg(PC_REG, 0x080001b4);
    TEST_ASSERT_EQUAL_Register(&reg);

    singleStep();                           //adds    r1, #1
    storeAffectedReg(R1, 0x6);
    TEST_ASSERT_EQUAL_Register(&reg);
    storeAffectedReg(PC_REG, 0x080001b6);
    TEST_ASSERT_EQUAL_Register(&reg);

    singleStep();                           //str     r1, [r0, #0]
    TEST_ASSERT_EQUAL(0x6, memoryBlock[virtualMemToPhysicalMem(0x20000000)]);
    storeAffectedReg(PC_REG, 0x080001b8);
    TEST_ASSERT_EQUAL_Register(&reg);

    singleStep();                           //movs    r2, #32
    storeAffectedReg(R2, 0x20);
    TEST_ASSERT_EQUAL_Register(&reg);
    storeAffectedReg(PC_REG, 0x080001ba);
    TEST_ASSERT_EQUAL_Register(&reg);

    singleStep();                           //b.n     80001b2 <again>
    storeAffectedReg(PC_REG, 0x080001b2);
    TEST_ASSERT_EQUAL_Register(&reg);

    coreReg[PC] = 0x80001c0;
    singleStep();                           //b.n     80001c0
    storeAffectedReg(PC_REG, 0x80001c0);
    TEST_ASSERT_EQUAL_Register(&reg);
}

/*
IT block
080001ac <Reset_Handler>:
 80001ac:       bf38            it      cc
 80001ae:       4281            cmpcc   r1, r0
 80001b0:       bf0c            ite     eq
 80001b2:       41c1            roreq   r1, r0
 80001b4:       41da            rorne   r2, r3
 80001b6:       bf2a            itet    cs
 80001b8:       40da            lsrcs   r2, r3
 80001ba:       40ec            lsrcc   r4, r5
 80001bc:       40f7            lsrcs   r7, r6
 80001be:       e7fe            b.n     80001be <Reset_Handler+0x12>

080001c0 <ADC_IRQHandler>:
 80001c0:       e7fe            b.n     80001c0 <ADC_IRQHandler>
*/
void test_IT_block_assmbly_code()
{
    loadITBlock();

    singleStep();                           //it      cc
    storeAffectedReg(XPSR, 0x01003800);
    TEST_ASSERT_EQUAL_Register(&reg);
    storeAffectedReg(PC_REG, 0x080001ae);
    TEST_ASSERT_EQUAL_Register(&reg);
    
    singleStep();                           //cmpcc   r1, r0
    storeAffectedReg(XPSR, 0x61000000);
    TEST_ASSERT_EQUAL_Register(&reg);
    storeAffectedReg(PC_REG, 0x080001b0);
    TEST_ASSERT_EQUAL_Register(&reg);
    
    singleStep();                           //ite     eq
    storeAffectedReg(XPSR, 0x61000C00);
    TEST_ASSERT_EQUAL_Register(&reg);
    storeAffectedReg(PC_REG, 0x080001b2);
    TEST_ASSERT_EQUAL_Register(&reg);
    
    singleStep();                           //roreq   r1, r0
    storeAffectedReg(XPSR, 0x61001800);
    TEST_ASSERT_EQUAL_Register(&reg);
    storeAffectedReg(PC_REG, 0x080001b4);
    TEST_ASSERT_EQUAL_Register(&reg);
    
    singleStep();                           //rorne   r2, r3
    storeAffectedReg(XPSR, 0x61000000);
    TEST_ASSERT_EQUAL_Register(&reg);
    storeAffectedReg(PC_REG, 0x080001b6);
    TEST_ASSERT_EQUAL_Register(&reg);
    
    singleStep();                           //itet    cs
    storeAffectedReg(XPSR, 0x65002800);
    TEST_ASSERT_EQUAL_Register(&reg);
    storeAffectedReg(PC_REG, 0x080001b8);
    TEST_ASSERT_EQUAL_Register(&reg);
    
    singleStep();                           //lsrcs   r2, r3
    storeAffectedReg(XPSR, 0x61003400);
    TEST_ASSERT_EQUAL_Register(&reg);
    storeAffectedReg(PC_REG, 0x080001ba);
    TEST_ASSERT_EQUAL_Register(&reg);
    
    singleStep();                           //lsrcc   r4, r5
    storeAffectedReg(XPSR, 0x61002800);
    TEST_ASSERT_EQUAL_Register(&reg);
    storeAffectedReg(PC_REG, 0x080001bc);
    TEST_ASSERT_EQUAL_Register(&reg);
    
    singleStep();                           //lsrcs   r7, r6
    storeAffectedReg(XPSR, 0x61000000);
    TEST_ASSERT_EQUAL_Register(&reg);
    storeAffectedReg(PC_REG, 0x080001be);
    TEST_ASSERT_EQUAL_Register(&reg);
}


