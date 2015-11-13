#include "unity.h"
#include "SBCImmediate.h"
#include "ExceptionObject.h"
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
#include "BL.h"
#include "BKPT.h"
#include "ModifiedImmediateConstant.h"
#include "ConditionalExecution.h"
#include "Thumb16bitsTable.h"
#include "StatusRegisters.h"
#include "ARMRegisters.h"
#include "getAndSetBits.h"
#include "getMask.h"
#include "ARMSimulator.h"
#include "ITandHints.h"
#include "ADDImmediate.h"
#include "LSLImmediate.h"
#include "LSRImmediate.h"
#include "MOVRegister.h"
#include "ASRImmediate.h"
#include "MOVImmediate.h"
#include "CMPImmediate.h"
#include "ADDImmediate.h"
#include "SUBImmediate.h"
#include "ADDRegister.h"
#include "SUBRegister.h"
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
#include "MemoryBlock.h"
#include "LDRLiteral.h"
#include "ErrorSignal.h"
#include "CException.h"
#include "SVC.h"
#include "ADDSPImmediate.h"
#include "ADR.h"
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
#include "NOP.h"
#include "MLA.h"
#include "MLS.h"
#include "SignedUnsignedLongMultiplyDivide.h"
#include "VMOV.h"
#include "VMSR.h"
#include "VMRS.h"
#include "VMLAandVMLS.h"
#include "VMUL.h"
#include "VNMLAandVNMLSandVNMUL.h"
#include "VSTM.h"
#include "VSTR.h"
#include "VPUSH.h"
#include "VLDM.h"
#include "VLDR.h"
#include "VPOP.h"
#include "VNEG.h"


void setUp(void)
{
  initializeSimulator();
}


void tearDown(void)
{
}


/*---------------------------------------------------------------------------------------------------------------------------------------------------*/
  //STM Register T2

//test STM.W  r0, {r0-r12, r14}
/*  r0 = 0x20000000
 *  r1 = 0xffffffff
 *  r2 = 0x33333333
 *  r3 = 0x44444444
 *  r4 = 0x00000000
 *  r5 = 0x66666666
 *  r6 = 0x77777777
 *  r7 = 0x80000000   
 *  r8 = 0x99999999
 *  r9 = 0xaaaaaaaa
 *  r10 = 0xbbbbbbbb
 *  r11 = 0xcccccccc
 *  r12 = 0xdddddddd
 *  r14 = 0xeeeeeeee
 * 
 * Expected:
 *  Memory address 0x20000000 = 0x00
 *  Memory address 0x20000001 = 0x00
 *  Memory address 0x20000002 = 0x00
 *  Memory address 0x20000003 = 0x20
 *  Memory address 0x20000004 = 0xff
 *  Memory address 0x20000005 = 0xff
 *  Memory address 0x20000006 = 0xff
 *  Memory address 0x20000007 = 0xff
 *  Memory address 0x20000008 = 0x33
 *  Memory address 0x20000009 = 0x33
 *  Memory address 0x2000000a = 0x33
 *  Memory address 0x2000000b = 0x33
 *  Memory address 0x2000000c = 0x44
 *  Memory address 0x2000000d = 0x44
 *  Memory address 0x2000000e = 0x44
 *  Memory address 0x2000000f = 0x44
 *  Memory address 0x20000010 = 0x00
 *  Memory address 0x20000011 = 0x00
 *  Memory address 0x20000012 = 0x00
 *  Memory address 0x20000013 = 0x00
 *  Memory address 0x20000014 = 0x66
 *  Memory address 0x20000015 = 0x66
 *  Memory address 0x20000016 = 0x66
 *  Memory address 0x20000017 = 0x66
 *  Memory address 0x20000018 = 0x77
 *  Memory address 0x20000019 = 0x77
 *  Memory address 0x2000001a = 0x77
 *  Memory address 0x2000001b = 0x77
 *  Memory address 0x2000001c = 0x00
 *  Memory address 0x2000001d = 0x00
 *  Memory address 0x2000001e = 0x00
 *  Memory address 0x2000001f = 0x80
 *  Memory address 0x20000020 = 0x99
 *  Memory address 0x20000021 = 0x99
 *  Memory address 0x20000022 = 0x99
 *  Memory address 0x20000023 = 0x99
 *  Memory address 0x20000024 = 0xaa
 *  Memory address 0x20000025 = 0xaa
 *  Memory address 0x20000026 = 0xaa
 *  Memory address 0x20000027 = 0xaa
 *  Memory address 0x20000028 = 0xbb
 *  Memory address 0x20000029 = 0xbb
 *  Memory address 0x2000002a = 0xbb
 *  Memory address 0x2000002b = 0xbb
 *  Memory address 0x2000002c = 0xcc
 *  Memory address 0x2000002d = 0xcc
 *  Memory address 0x2000002e = 0xcc
 *  Memory address 0x2000002f = 0xcc
 *  Memory address 0x20000030 = 0xdd
 *  Memory address 0x20000031 = 0xdd
 *  Memory address 0x20000032 = 0xdd
 *  Memory address 0x20000033 = 0xdd
 *  Memory address 0x20000034 = 0xee
 *  Memory address 0x20000035 = 0xee
 *  Memory address 0x20000036 = 0xee
 *  Memory address 0x20000037 = 0xee
 
 */
void test_STMRegisterT2_given_writeback_is_0_should_get_the_expected_result(void)
{
  CEXCEPTION_T err;
  coreReg[0] = 0x20000000;
  coreReg[1] = 0xffffffff;
  coreReg[2] = 0x33333333;
  coreReg[3] = 0x44444444;
  coreReg[4] = 0x00000000;
  coreReg[5] = 0x66666666;
  coreReg[6] = 0x77777777;
  coreReg[7] = 0x80000000;
  coreReg[8] = 0x99999999;
  coreReg[9] = 0xaaaaaaaa;
  coreReg[10] = 0xbbbbbbbb;
  coreReg[11] = 0xcccccccc;
  coreReg[12] = 0xdddddddd;
  coreReg[14] = 0xeeeeeeee;

  Try
  {
    writeInstructionToMemoryGivenByAddress(0xe8805fff, 0x08000046);  // STM.W  r0, {r0-r12, r14}
    coreReg[PC] = 0x08000046;
    armStep();
    TEST_ASSERT_EQUAL( 0x0800004a, coreReg[PC]);
    TEST_ASSERT_EQUAL( 0x00, memoryBlock[ virtualMemToPhysicalMem(0x20000000) ]);
    TEST_ASSERT_EQUAL( 0x00, memoryBlock[ virtualMemToPhysicalMem(0x20000001) ]);
    TEST_ASSERT_EQUAL( 0x00, memoryBlock[ virtualMemToPhysicalMem(0x20000002) ]);
    TEST_ASSERT_EQUAL( 0x20, memoryBlock[ virtualMemToPhysicalMem(0x20000003) ]);
    TEST_ASSERT_EQUAL( 0xff, memoryBlock[ virtualMemToPhysicalMem(0x20000004) ]);
    TEST_ASSERT_EQUAL( 0xff, memoryBlock[ virtualMemToPhysicalMem(0x20000005) ]);
    TEST_ASSERT_EQUAL( 0xff, memoryBlock[ virtualMemToPhysicalMem(0x20000006) ]);
    TEST_ASSERT_EQUAL( 0xff, memoryBlock[ virtualMemToPhysicalMem(0x20000007) ]);
    TEST_ASSERT_EQUAL( 0x33, memoryBlock[ virtualMemToPhysicalMem(0x20000008) ]);
    TEST_ASSERT_EQUAL( 0x33, memoryBlock[ virtualMemToPhysicalMem(0x20000009) ]);
    TEST_ASSERT_EQUAL( 0x33, memoryBlock[ virtualMemToPhysicalMem(0x2000000a) ]);
    TEST_ASSERT_EQUAL( 0x33, memoryBlock[ virtualMemToPhysicalMem(0x2000000b) ]);
    TEST_ASSERT_EQUAL( 0x44, memoryBlock[ virtualMemToPhysicalMem(0x2000000c) ]);
    TEST_ASSERT_EQUAL( 0x44, memoryBlock[ virtualMemToPhysicalMem(0x2000000d) ]);
    TEST_ASSERT_EQUAL( 0x44, memoryBlock[ virtualMemToPhysicalMem(0x2000000e) ]);
    TEST_ASSERT_EQUAL( 0x44, memoryBlock[ virtualMemToPhysicalMem(0x2000000f) ]);
    TEST_ASSERT_EQUAL( 0x00, memoryBlock[ virtualMemToPhysicalMem(0x20000010) ]);
    TEST_ASSERT_EQUAL( 0x00, memoryBlock[ virtualMemToPhysicalMem(0x20000011) ]);
    TEST_ASSERT_EQUAL( 0x00, memoryBlock[ virtualMemToPhysicalMem(0x20000012) ]);
    TEST_ASSERT_EQUAL( 0x00, memoryBlock[ virtualMemToPhysicalMem(0x20000013) ]);
    TEST_ASSERT_EQUAL( 0x66, memoryBlock[ virtualMemToPhysicalMem(0x20000014) ]);
    TEST_ASSERT_EQUAL( 0x66, memoryBlock[ virtualMemToPhysicalMem(0x20000015) ]);
    TEST_ASSERT_EQUAL( 0x66, memoryBlock[ virtualMemToPhysicalMem(0x20000016) ]);
    TEST_ASSERT_EQUAL( 0x66, memoryBlock[ virtualMemToPhysicalMem(0x20000017) ]);
    TEST_ASSERT_EQUAL( 0x77, memoryBlock[ virtualMemToPhysicalMem(0x20000018) ]);
    TEST_ASSERT_EQUAL( 0x77, memoryBlock[ virtualMemToPhysicalMem(0x20000019) ]);
    TEST_ASSERT_EQUAL( 0x77, memoryBlock[ virtualMemToPhysicalMem(0x2000001a) ]);
    TEST_ASSERT_EQUAL( 0x77, memoryBlock[ virtualMemToPhysicalMem(0x2000001b) ]);
    TEST_ASSERT_EQUAL( 0x00, memoryBlock[ virtualMemToPhysicalMem(0x2000001c) ]);
    TEST_ASSERT_EQUAL( 0x00, memoryBlock[ virtualMemToPhysicalMem(0x2000001d) ]);
    TEST_ASSERT_EQUAL( 0x00, memoryBlock[ virtualMemToPhysicalMem(0x2000001e) ]);
    TEST_ASSERT_EQUAL( 0x80, memoryBlock[ virtualMemToPhysicalMem(0x2000001f) ]);
    TEST_ASSERT_EQUAL( 0x99, memoryBlock[ virtualMemToPhysicalMem(0x20000020) ]);
    TEST_ASSERT_EQUAL( 0x99, memoryBlock[ virtualMemToPhysicalMem(0x20000021) ]);
    TEST_ASSERT_EQUAL( 0x99, memoryBlock[ virtualMemToPhysicalMem(0x20000022) ]);
    TEST_ASSERT_EQUAL( 0x99, memoryBlock[ virtualMemToPhysicalMem(0x20000023) ]);
    TEST_ASSERT_EQUAL( 0xaa, memoryBlock[ virtualMemToPhysicalMem(0x20000024) ]);
    TEST_ASSERT_EQUAL( 0xaa, memoryBlock[ virtualMemToPhysicalMem(0x20000025) ]);
    TEST_ASSERT_EQUAL( 0xaa, memoryBlock[ virtualMemToPhysicalMem(0x20000026) ]);
    TEST_ASSERT_EQUAL( 0xaa, memoryBlock[ virtualMemToPhysicalMem(0x20000027) ]);
    TEST_ASSERT_EQUAL( 0xbb, memoryBlock[ virtualMemToPhysicalMem(0x20000028) ]);
    TEST_ASSERT_EQUAL( 0xbb, memoryBlock[ virtualMemToPhysicalMem(0x20000029) ]);
    TEST_ASSERT_EQUAL( 0xbb, memoryBlock[ virtualMemToPhysicalMem(0x2000002a) ]);
    TEST_ASSERT_EQUAL( 0xbb, memoryBlock[ virtualMemToPhysicalMem(0x2000002b) ]);
    TEST_ASSERT_EQUAL( 0xcc, memoryBlock[ virtualMemToPhysicalMem(0x2000002c) ]);
    TEST_ASSERT_EQUAL( 0xcc, memoryBlock[ virtualMemToPhysicalMem(0x2000002d) ]);
    TEST_ASSERT_EQUAL( 0xcc, memoryBlock[ virtualMemToPhysicalMem(0x2000002e) ]);
    TEST_ASSERT_EQUAL( 0xcc, memoryBlock[ virtualMemToPhysicalMem(0x2000002f) ]);
    TEST_ASSERT_EQUAL( 0xdd, memoryBlock[ virtualMemToPhysicalMem(0x20000030) ]);
    TEST_ASSERT_EQUAL( 0xdd, memoryBlock[ virtualMemToPhysicalMem(0x20000031) ]);
    TEST_ASSERT_EQUAL( 0xdd, memoryBlock[ virtualMemToPhysicalMem(0x20000032) ]);
    TEST_ASSERT_EQUAL( 0xdd, memoryBlock[ virtualMemToPhysicalMem(0x20000033) ]);
    TEST_ASSERT_EQUAL( 0xee, memoryBlock[ virtualMemToPhysicalMem(0x20000034) ]);
    TEST_ASSERT_EQUAL( 0xee, memoryBlock[ virtualMemToPhysicalMem(0x20000035) ]);
    TEST_ASSERT_EQUAL( 0xee, memoryBlock[ virtualMemToPhysicalMem(0x20000036) ]);
    TEST_ASSERT_EQUAL( 0xee, memoryBlock[ virtualMemToPhysicalMem(0x20000037) ]);
  }
  Catch(err)
  {
    TEST_FAIL_MESSAGE("Not expect error to be throw\n");
  }
}


//test STM.W  r0!, {r1-r12, r14}
/*  r0 = 0x20000000
 *  r1 = 0xffffffff
 *  r2 = 0x33333333
 *  r3 = 0x44444444
 *  r4 = 0x00000000
 *  r5 = 0x66666666
 *  r6 = 0x77777777
 *  r7 = 0x80000000   
 *  r8 = 0x99999999
 *  r9 = 0xaaaaaaaa
 *  r10 = 0xbbbbbbbb
 *  r11 = 0xcccccccc
 *  r12 = 0xdddddddd
 *  r14 = 0xeeeeeeee
 * 
 * Expected:
 *  Memory address 0x20000000 = 0x00
 *  Memory address 0x20000001 = 0x00
 *  Memory address 0x20000002 = 0x00
 *  Memory address 0x20000003 = 0x20
 *  Memory address 0x20000004 = 0xff
 *  Memory address 0x20000005 = 0xff
 *  Memory address 0x20000006 = 0xff
 *  Memory address 0x20000007 = 0xff
 *  Memory address 0x20000008 = 0x33
 *  Memory address 0x20000009 = 0x33
 *  Memory address 0x2000000a = 0x33
 *  Memory address 0x2000000b = 0x33
 *  Memory address 0x2000000c = 0x44
 *  Memory address 0x2000000d = 0x44
 *  Memory address 0x2000000e = 0x44
 *  Memory address 0x2000000f = 0x44
 *  Memory address 0x20000010 = 0x00
 *  Memory address 0x20000011 = 0x00
 *  Memory address 0x20000012 = 0x00
 *  Memory address 0x20000013 = 0x00
 *  Memory address 0x20000014 = 0x66
 *  Memory address 0x20000015 = 0x66
 *  Memory address 0x20000016 = 0x66
 *  Memory address 0x20000017 = 0x66
 *  Memory address 0x20000018 = 0x77
 *  Memory address 0x20000019 = 0x77
 *  Memory address 0x2000001a = 0x77
 *  Memory address 0x2000001b = 0x77
 *  Memory address 0x2000001c = 0x00
 *  Memory address 0x2000001d = 0x00
 *  Memory address 0x2000001e = 0x00
 *  Memory address 0x2000001f = 0x80
 *  Memory address 0x20000020 = 0x99
 *  Memory address 0x20000021 = 0x99
 *  Memory address 0x20000022 = 0x99
 *  Memory address 0x20000023 = 0x99
 *  Memory address 0x20000024 = 0xaa
 *  Memory address 0x20000025 = 0xaa
 *  Memory address 0x20000026 = 0xaa
 *  Memory address 0x20000027 = 0xaa
 *  Memory address 0x20000028 = 0xbb
 *  Memory address 0x20000029 = 0xbb
 *  Memory address 0x2000002a = 0xbb
 *  Memory address 0x2000002b = 0xbb
 *  Memory address 0x2000002c = 0xcc
 *  Memory address 0x2000002d = 0xcc
 *  Memory address 0x2000002e = 0xcc
 *  Memory address 0x2000002f = 0xcc
 *  Memory address 0x20000030 = 0xdd
 *  Memory address 0x20000031 = 0xdd
 *  Memory address 0x20000032 = 0xdd
 *  Memory address 0x20000033 = 0xdd
 *  Memory address 0x20000034 = 0xee
 *  Memory address 0x20000035 = 0xee
 *  Memory address 0x20000036 = 0xee
 *  Memory address 0x20000037 = 0xee
 
 */
void test_STMRegisterT2_given_writeback_is_1_should_get_the_expected_result(void)
{
  CEXCEPTION_T err;
  coreReg[0] = 0x20000004;
  coreReg[1] = 0xffffffff;
  coreReg[2] = 0x33333333;
  coreReg[3] = 0x44444444;
  coreReg[4] = 0x00000000;
  coreReg[5] = 0x66666666;
  coreReg[6] = 0x77777777;
  coreReg[7] = 0x80000000;
  coreReg[8] = 0x99999999;
  coreReg[9] = 0xaaaaaaaa;
  coreReg[10] = 0xbbbbbbbb;
  coreReg[11] = 0xcccccccc;
  coreReg[12] = 0xdddddddd;
  coreReg[14] = 0xeeeeeeee;

  Try
  {
    writeInstructionToMemoryGivenByAddress(0xe8a05ffe, 0x08000044);  //  STM.W  r0!, {r1-r12, r14}
    coreReg[PC] = 0x08000044;
    armStep();
    TEST_ASSERT_EQUAL( 0x08000048, coreReg[PC]);
    TEST_ASSERT_EQUAL( 0x20000038, coreReg[0]);
    TEST_ASSERT_EQUAL( 0xff, memoryBlock[ virtualMemToPhysicalMem(0x20000004) ]);
    TEST_ASSERT_EQUAL( 0xff, memoryBlock[ virtualMemToPhysicalMem(0x20000005) ]);
    TEST_ASSERT_EQUAL( 0xff, memoryBlock[ virtualMemToPhysicalMem(0x20000006) ]);
    TEST_ASSERT_EQUAL( 0xff, memoryBlock[ virtualMemToPhysicalMem(0x20000007) ]);
    TEST_ASSERT_EQUAL( 0x33, memoryBlock[ virtualMemToPhysicalMem(0x20000008) ]);
    TEST_ASSERT_EQUAL( 0x33, memoryBlock[ virtualMemToPhysicalMem(0x20000009) ]);
    TEST_ASSERT_EQUAL( 0x33, memoryBlock[ virtualMemToPhysicalMem(0x2000000a) ]);
    TEST_ASSERT_EQUAL( 0x33, memoryBlock[ virtualMemToPhysicalMem(0x2000000b) ]);
    TEST_ASSERT_EQUAL( 0x44, memoryBlock[ virtualMemToPhysicalMem(0x2000000c) ]);
    TEST_ASSERT_EQUAL( 0x44, memoryBlock[ virtualMemToPhysicalMem(0x2000000d) ]);
    TEST_ASSERT_EQUAL( 0x44, memoryBlock[ virtualMemToPhysicalMem(0x2000000e) ]);
    TEST_ASSERT_EQUAL( 0x44, memoryBlock[ virtualMemToPhysicalMem(0x2000000f) ]);
    TEST_ASSERT_EQUAL( 0x00, memoryBlock[ virtualMemToPhysicalMem(0x20000010) ]);
    TEST_ASSERT_EQUAL( 0x00, memoryBlock[ virtualMemToPhysicalMem(0x20000011) ]);
    TEST_ASSERT_EQUAL( 0x00, memoryBlock[ virtualMemToPhysicalMem(0x20000012) ]);
    TEST_ASSERT_EQUAL( 0x00, memoryBlock[ virtualMemToPhysicalMem(0x20000013) ]);
    TEST_ASSERT_EQUAL( 0x66, memoryBlock[ virtualMemToPhysicalMem(0x20000014) ]);
    TEST_ASSERT_EQUAL( 0x66, memoryBlock[ virtualMemToPhysicalMem(0x20000015) ]);
    TEST_ASSERT_EQUAL( 0x66, memoryBlock[ virtualMemToPhysicalMem(0x20000016) ]);
    TEST_ASSERT_EQUAL( 0x66, memoryBlock[ virtualMemToPhysicalMem(0x20000017) ]);
    TEST_ASSERT_EQUAL( 0x77, memoryBlock[ virtualMemToPhysicalMem(0x20000018) ]);
    TEST_ASSERT_EQUAL( 0x77, memoryBlock[ virtualMemToPhysicalMem(0x20000019) ]);
    TEST_ASSERT_EQUAL( 0x77, memoryBlock[ virtualMemToPhysicalMem(0x2000001a) ]);
    TEST_ASSERT_EQUAL( 0x77, memoryBlock[ virtualMemToPhysicalMem(0x2000001b) ]);
    TEST_ASSERT_EQUAL( 0x00, memoryBlock[ virtualMemToPhysicalMem(0x2000001c) ]);
    TEST_ASSERT_EQUAL( 0x00, memoryBlock[ virtualMemToPhysicalMem(0x2000001d) ]);
    TEST_ASSERT_EQUAL( 0x00, memoryBlock[ virtualMemToPhysicalMem(0x2000001e) ]);
    TEST_ASSERT_EQUAL( 0x80, memoryBlock[ virtualMemToPhysicalMem(0x2000001f) ]);
    TEST_ASSERT_EQUAL( 0x99, memoryBlock[ virtualMemToPhysicalMem(0x20000020) ]);
    TEST_ASSERT_EQUAL( 0x99, memoryBlock[ virtualMemToPhysicalMem(0x20000021) ]);
    TEST_ASSERT_EQUAL( 0x99, memoryBlock[ virtualMemToPhysicalMem(0x20000022) ]);
    TEST_ASSERT_EQUAL( 0x99, memoryBlock[ virtualMemToPhysicalMem(0x20000023) ]);
    TEST_ASSERT_EQUAL( 0xaa, memoryBlock[ virtualMemToPhysicalMem(0x20000024) ]);
    TEST_ASSERT_EQUAL( 0xaa, memoryBlock[ virtualMemToPhysicalMem(0x20000025) ]);
    TEST_ASSERT_EQUAL( 0xaa, memoryBlock[ virtualMemToPhysicalMem(0x20000026) ]);
    TEST_ASSERT_EQUAL( 0xaa, memoryBlock[ virtualMemToPhysicalMem(0x20000027) ]);
    TEST_ASSERT_EQUAL( 0xbb, memoryBlock[ virtualMemToPhysicalMem(0x20000028) ]);
    TEST_ASSERT_EQUAL( 0xbb, memoryBlock[ virtualMemToPhysicalMem(0x20000029) ]);
    TEST_ASSERT_EQUAL( 0xbb, memoryBlock[ virtualMemToPhysicalMem(0x2000002a) ]);
    TEST_ASSERT_EQUAL( 0xbb, memoryBlock[ virtualMemToPhysicalMem(0x2000002b) ]);
    TEST_ASSERT_EQUAL( 0xcc, memoryBlock[ virtualMemToPhysicalMem(0x2000002c) ]);
    TEST_ASSERT_EQUAL( 0xcc, memoryBlock[ virtualMemToPhysicalMem(0x2000002d) ]);
    TEST_ASSERT_EQUAL( 0xcc, memoryBlock[ virtualMemToPhysicalMem(0x2000002e) ]);
    TEST_ASSERT_EQUAL( 0xcc, memoryBlock[ virtualMemToPhysicalMem(0x2000002f) ]);
    TEST_ASSERT_EQUAL( 0xdd, memoryBlock[ virtualMemToPhysicalMem(0x20000030) ]);
    TEST_ASSERT_EQUAL( 0xdd, memoryBlock[ virtualMemToPhysicalMem(0x20000031) ]);
    TEST_ASSERT_EQUAL( 0xdd, memoryBlock[ virtualMemToPhysicalMem(0x20000032) ]);
    TEST_ASSERT_EQUAL( 0xdd, memoryBlock[ virtualMemToPhysicalMem(0x20000033) ]);
    TEST_ASSERT_EQUAL( 0xee, memoryBlock[ virtualMemToPhysicalMem(0x20000034) ]);
    TEST_ASSERT_EQUAL( 0xee, memoryBlock[ virtualMemToPhysicalMem(0x20000035) ]);
    TEST_ASSERT_EQUAL( 0xee, memoryBlock[ virtualMemToPhysicalMem(0x20000036) ]);
    TEST_ASSERT_EQUAL( 0xee, memoryBlock[ virtualMemToPhysicalMem(0x20000037) ]);
  }
  Catch(err)
  {
    TEST_FAIL_MESSAGE("Not expect error to be throw\n");
  }
}


/*---------------------------------------------------------------------------------------------------------------------------------------------------*/
  //STMDB

//test STMDB  r0!, {r1-r12, r14}
/*  r0 = 0x20000000
 *  r1 = 0xffffffff
 *  r2 = 0x33333333
 *  r3 = 0x44444444
 *  r4 = 0x00000000
 *  r5 = 0x66666666
 *  r6 = 0x77777777
 *  r7 = 0x80000000   
 *  r8 = 0x99999999
 *  r9 = 0xaaaaaaaa
 *  r10 = 0xbbbbbbbb
 *  r11 = 0xcccccccc
 *  r12 = 0xdddddddd
 *  r14 = 0xeeeeeeee
 * 
 * Expected:
 *  Memory address 0x20000000 = 0x00
 *  Memory address 0x20000001 = 0x00
 *  Memory address 0x20000002 = 0x00
 *  Memory address 0x20000003 = 0x20
 *  Memory address 0x20000004 = 0xff
 *  Memory address 0x20000005 = 0xff
 *  Memory address 0x20000006 = 0xff
 *  Memory address 0x20000007 = 0xff
 *  Memory address 0x20000008 = 0x33
 *  Memory address 0x20000009 = 0x33
 *  Memory address 0x2000000a = 0x33
 *  Memory address 0x2000000b = 0x33
 *  Memory address 0x2000000c = 0x44
 *  Memory address 0x2000000d = 0x44
 *  Memory address 0x2000000e = 0x44
 *  Memory address 0x2000000f = 0x44
 *  Memory address 0x20000010 = 0x00
 *  Memory address 0x20000011 = 0x00
 *  Memory address 0x20000012 = 0x00
 *  Memory address 0x20000013 = 0x00
 *  Memory address 0x20000014 = 0x66
 *  Memory address 0x20000015 = 0x66
 *  Memory address 0x20000016 = 0x66
 *  Memory address 0x20000017 = 0x66
 *  Memory address 0x20000018 = 0x77
 *  Memory address 0x20000019 = 0x77
 *  Memory address 0x2000001a = 0x77
 *  Memory address 0x2000001b = 0x77
 *  Memory address 0x2000001c = 0x00
 *  Memory address 0x2000001d = 0x00
 *  Memory address 0x2000001e = 0x00
 *  Memory address 0x2000001f = 0x80
 *  Memory address 0x20000020 = 0x99
 *  Memory address 0x20000021 = 0x99
 *  Memory address 0x20000022 = 0x99
 *  Memory address 0x20000023 = 0x99
 *  Memory address 0x20000024 = 0xaa
 *  Memory address 0x20000025 = 0xaa
 *  Memory address 0x20000026 = 0xaa
 *  Memory address 0x20000027 = 0xaa
 *  Memory address 0x20000028 = 0xbb
 *  Memory address 0x20000029 = 0xbb
 *  Memory address 0x2000002a = 0xbb
 *  Memory address 0x2000002b = 0xbb
 *  Memory address 0x2000002c = 0xcc
 *  Memory address 0x2000002d = 0xcc
 *  Memory address 0x2000002e = 0xcc
 *  Memory address 0x2000002f = 0xcc
 *  Memory address 0x20000030 = 0xdd
 *  Memory address 0x20000031 = 0xdd
 *  Memory address 0x20000032 = 0xdd
 *  Memory address 0x20000033 = 0xdd
 *  Memory address 0x20000034 = 0xee
 *  Memory address 0x20000035 = 0xee
 *  Memory address 0x20000036 = 0xee
 *  Memory address 0x20000037 = 0xee
 
 */
void test_STMDB_given_writeback_is_1_should_get_the_expected_result(void)
{
  CEXCEPTION_T err;
  coreReg[0] = 0x20000038;
  coreReg[1] = 0xffffffff;
  coreReg[2] = 0x33333333;
  coreReg[3] = 0x44444444;
  coreReg[4] = 0x00000000;
  coreReg[5] = 0x66666666;
  coreReg[6] = 0x77777777;
  coreReg[7] = 0x80000000;
  coreReg[8] = 0x99999999;
  coreReg[9] = 0xaaaaaaaa;
  coreReg[10] = 0xbbbbbbbb;
  coreReg[11] = 0xcccccccc;
  coreReg[12] = 0xdddddddd;
  coreReg[14] = 0xeeeeeeee;

  Try
  {
    writeInstructionToMemoryGivenByAddress(0xe9205ffe, 0x08000044);  //  STMDB.W  r0!, {r1-r12, r14}
    coreReg[PC] = 0x08000044;
    armStep();
    TEST_ASSERT_EQUAL( 0x08000048, coreReg[PC]);
    TEST_ASSERT_EQUAL( 0x20000004, coreReg[0]);
    TEST_ASSERT_EQUAL( 0xff, memoryBlock[ virtualMemToPhysicalMem(0x20000004) ]);
    TEST_ASSERT_EQUAL( 0xff, memoryBlock[ virtualMemToPhysicalMem(0x20000005) ]);
    TEST_ASSERT_EQUAL( 0xff, memoryBlock[ virtualMemToPhysicalMem(0x20000006) ]);
    TEST_ASSERT_EQUAL( 0xff, memoryBlock[ virtualMemToPhysicalMem(0x20000007) ]);
    TEST_ASSERT_EQUAL( 0x33, memoryBlock[ virtualMemToPhysicalMem(0x20000008) ]);
    TEST_ASSERT_EQUAL( 0x33, memoryBlock[ virtualMemToPhysicalMem(0x20000009) ]);
    TEST_ASSERT_EQUAL( 0x33, memoryBlock[ virtualMemToPhysicalMem(0x2000000a) ]);
    TEST_ASSERT_EQUAL( 0x33, memoryBlock[ virtualMemToPhysicalMem(0x2000000b) ]);
    TEST_ASSERT_EQUAL( 0x44, memoryBlock[ virtualMemToPhysicalMem(0x2000000c) ]);
    TEST_ASSERT_EQUAL( 0x44, memoryBlock[ virtualMemToPhysicalMem(0x2000000d) ]);
    TEST_ASSERT_EQUAL( 0x44, memoryBlock[ virtualMemToPhysicalMem(0x2000000e) ]);
    TEST_ASSERT_EQUAL( 0x44, memoryBlock[ virtualMemToPhysicalMem(0x2000000f) ]);
    TEST_ASSERT_EQUAL( 0x00, memoryBlock[ virtualMemToPhysicalMem(0x20000010) ]);
    TEST_ASSERT_EQUAL( 0x00, memoryBlock[ virtualMemToPhysicalMem(0x20000011) ]);
    TEST_ASSERT_EQUAL( 0x00, memoryBlock[ virtualMemToPhysicalMem(0x20000012) ]);
    TEST_ASSERT_EQUAL( 0x00, memoryBlock[ virtualMemToPhysicalMem(0x20000013) ]);
    TEST_ASSERT_EQUAL( 0x66, memoryBlock[ virtualMemToPhysicalMem(0x20000014) ]);
    TEST_ASSERT_EQUAL( 0x66, memoryBlock[ virtualMemToPhysicalMem(0x20000015) ]);
    TEST_ASSERT_EQUAL( 0x66, memoryBlock[ virtualMemToPhysicalMem(0x20000016) ]);
    TEST_ASSERT_EQUAL( 0x66, memoryBlock[ virtualMemToPhysicalMem(0x20000017) ]);
    TEST_ASSERT_EQUAL( 0x77, memoryBlock[ virtualMemToPhysicalMem(0x20000018) ]);
    TEST_ASSERT_EQUAL( 0x77, memoryBlock[ virtualMemToPhysicalMem(0x20000019) ]);
    TEST_ASSERT_EQUAL( 0x77, memoryBlock[ virtualMemToPhysicalMem(0x2000001a) ]);
    TEST_ASSERT_EQUAL( 0x77, memoryBlock[ virtualMemToPhysicalMem(0x2000001b) ]);
    TEST_ASSERT_EQUAL( 0x00, memoryBlock[ virtualMemToPhysicalMem(0x2000001c) ]);
    TEST_ASSERT_EQUAL( 0x00, memoryBlock[ virtualMemToPhysicalMem(0x2000001d) ]);
    TEST_ASSERT_EQUAL( 0x00, memoryBlock[ virtualMemToPhysicalMem(0x2000001e) ]);
    TEST_ASSERT_EQUAL( 0x80, memoryBlock[ virtualMemToPhysicalMem(0x2000001f) ]);
    TEST_ASSERT_EQUAL( 0x99, memoryBlock[ virtualMemToPhysicalMem(0x20000020) ]);
    TEST_ASSERT_EQUAL( 0x99, memoryBlock[ virtualMemToPhysicalMem(0x20000021) ]);
    TEST_ASSERT_EQUAL( 0x99, memoryBlock[ virtualMemToPhysicalMem(0x20000022) ]);
    TEST_ASSERT_EQUAL( 0x99, memoryBlock[ virtualMemToPhysicalMem(0x20000023) ]);
    TEST_ASSERT_EQUAL( 0xaa, memoryBlock[ virtualMemToPhysicalMem(0x20000024) ]);
    TEST_ASSERT_EQUAL( 0xaa, memoryBlock[ virtualMemToPhysicalMem(0x20000025) ]);
    TEST_ASSERT_EQUAL( 0xaa, memoryBlock[ virtualMemToPhysicalMem(0x20000026) ]);
    TEST_ASSERT_EQUAL( 0xaa, memoryBlock[ virtualMemToPhysicalMem(0x20000027) ]);
    TEST_ASSERT_EQUAL( 0xbb, memoryBlock[ virtualMemToPhysicalMem(0x20000028) ]);
    TEST_ASSERT_EQUAL( 0xbb, memoryBlock[ virtualMemToPhysicalMem(0x20000029) ]);
    TEST_ASSERT_EQUAL( 0xbb, memoryBlock[ virtualMemToPhysicalMem(0x2000002a) ]);
    TEST_ASSERT_EQUAL( 0xbb, memoryBlock[ virtualMemToPhysicalMem(0x2000002b) ]);
    TEST_ASSERT_EQUAL( 0xcc, memoryBlock[ virtualMemToPhysicalMem(0x2000002c) ]);
    TEST_ASSERT_EQUAL( 0xcc, memoryBlock[ virtualMemToPhysicalMem(0x2000002d) ]);
    TEST_ASSERT_EQUAL( 0xcc, memoryBlock[ virtualMemToPhysicalMem(0x2000002e) ]);
    TEST_ASSERT_EQUAL( 0xcc, memoryBlock[ virtualMemToPhysicalMem(0x2000002f) ]);
    TEST_ASSERT_EQUAL( 0xdd, memoryBlock[ virtualMemToPhysicalMem(0x20000030) ]);
    TEST_ASSERT_EQUAL( 0xdd, memoryBlock[ virtualMemToPhysicalMem(0x20000031) ]);
    TEST_ASSERT_EQUAL( 0xdd, memoryBlock[ virtualMemToPhysicalMem(0x20000032) ]);
    TEST_ASSERT_EQUAL( 0xdd, memoryBlock[ virtualMemToPhysicalMem(0x20000033) ]);
    TEST_ASSERT_EQUAL( 0xee, memoryBlock[ virtualMemToPhysicalMem(0x20000034) ]);
    TEST_ASSERT_EQUAL( 0xee, memoryBlock[ virtualMemToPhysicalMem(0x20000035) ]);
    TEST_ASSERT_EQUAL( 0xee, memoryBlock[ virtualMemToPhysicalMem(0x20000036) ]);
    TEST_ASSERT_EQUAL( 0xee, memoryBlock[ virtualMemToPhysicalMem(0x20000037) ]);
  }
  Catch(err)
  {
    TEST_FAIL_MESSAGE("Not expect error to be throw\n");
  }
}








//test STMDB.W  r0, {r1-r12, r14}
/*  r0 = 0x20000000
 *  r1 = 0xffffffff
 *  r2 = 0x33333333
 *  r3 = 0x44444444
 *  r4 = 0x00000000
 *  r5 = 0x66666666
 *  r6 = 0x77777777
 *  r7 = 0x80000000   
 *  r8 = 0x99999999
 *  r9 = 0xaaaaaaaa
 *  r10 = 0xbbbbbbbb
 *  r11 = 0xcccccccc
 *  r12 = 0xdddddddd
 *  r14 = 0xeeeeeeee
 * 
 * Expected:
 *  Memory address 0x20000000 = 0x00
 *  Memory address 0x20000001 = 0x00
 *  Memory address 0x20000002 = 0x00
 *  Memory address 0x20000003 = 0x20
 *  Memory address 0x20000004 = 0xff
 *  Memory address 0x20000005 = 0xff
 *  Memory address 0x20000006 = 0xff
 *  Memory address 0x20000007 = 0xff
 *  Memory address 0x20000008 = 0x33
 *  Memory address 0x20000009 = 0x33
 *  Memory address 0x2000000a = 0x33
 *  Memory address 0x2000000b = 0x33
 *  Memory address 0x2000000c = 0x44
 *  Memory address 0x2000000d = 0x44
 *  Memory address 0x2000000e = 0x44
 *  Memory address 0x2000000f = 0x44
 *  Memory address 0x20000010 = 0x00
 *  Memory address 0x20000011 = 0x00
 *  Memory address 0x20000012 = 0x00
 *  Memory address 0x20000013 = 0x00
 *  Memory address 0x20000014 = 0x66
 *  Memory address 0x20000015 = 0x66
 *  Memory address 0x20000016 = 0x66
 *  Memory address 0x20000017 = 0x66
 *  Memory address 0x20000018 = 0x77
 *  Memory address 0x20000019 = 0x77
 *  Memory address 0x2000001a = 0x77
 *  Memory address 0x2000001b = 0x77
 *  Memory address 0x2000001c = 0x00
 *  Memory address 0x2000001d = 0x00
 *  Memory address 0x2000001e = 0x00
 *  Memory address 0x2000001f = 0x80
 *  Memory address 0x20000020 = 0x99
 *  Memory address 0x20000021 = 0x99
 *  Memory address 0x20000022 = 0x99
 *  Memory address 0x20000023 = 0x99
 *  Memory address 0x20000024 = 0xaa
 *  Memory address 0x20000025 = 0xaa
 *  Memory address 0x20000026 = 0xaa
 *  Memory address 0x20000027 = 0xaa
 *  Memory address 0x20000028 = 0xbb
 *  Memory address 0x20000029 = 0xbb
 *  Memory address 0x2000002a = 0xbb
 *  Memory address 0x2000002b = 0xbb
 *  Memory address 0x2000002c = 0xcc
 *  Memory address 0x2000002d = 0xcc
 *  Memory address 0x2000002e = 0xcc
 *  Memory address 0x2000002f = 0xcc
 *  Memory address 0x20000030 = 0xdd
 *  Memory address 0x20000031 = 0xdd
 *  Memory address 0x20000032 = 0xdd
 *  Memory address 0x20000033 = 0xdd
 *  Memory address 0x20000034 = 0xee
 *  Memory address 0x20000035 = 0xee
 *  Memory address 0x20000036 = 0xee
 *  Memory address 0x20000037 = 0xee
 
 */
void test_STMDB_given_writeback_is_0_should_get_the_expected_result(void)
{
  CEXCEPTION_T err;
  coreReg[0] = 0x20000038;
  coreReg[1] = 0xffffffff;
  coreReg[2] = 0x33333333;
  coreReg[3] = 0x44444444;
  coreReg[4] = 0x00000000;
  coreReg[5] = 0x66666666;
  coreReg[6] = 0x77777777;
  coreReg[7] = 0x80000000;
  coreReg[8] = 0x99999999;
  coreReg[9] = 0xaaaaaaaa;
  coreReg[10] = 0xbbbbbbbb;
  coreReg[11] = 0xcccccccc;
  coreReg[12] = 0xdddddddd;
  coreReg[14] = 0xeeeeeeee;

  Try
  {
    writeInstructionToMemoryGivenByAddress(0xe9005ffe, 0x08000046);  // STMDB.W  r0, {r1-r12, r14}
    coreReg[PC] = 0x08000046;
    armStep();
    TEST_ASSERT_EQUAL( 0x0800004a, coreReg[PC]);
    TEST_ASSERT_EQUAL( 0x20000038, coreReg[0]);
    TEST_ASSERT_EQUAL( 0xff, memoryBlock[ virtualMemToPhysicalMem(0x20000004) ]);
    TEST_ASSERT_EQUAL( 0xff, memoryBlock[ virtualMemToPhysicalMem(0x20000005) ]);
    TEST_ASSERT_EQUAL( 0xff, memoryBlock[ virtualMemToPhysicalMem(0x20000006) ]);
    TEST_ASSERT_EQUAL( 0xff, memoryBlock[ virtualMemToPhysicalMem(0x20000007) ]);
    TEST_ASSERT_EQUAL( 0x33, memoryBlock[ virtualMemToPhysicalMem(0x20000008) ]);
    TEST_ASSERT_EQUAL( 0x33, memoryBlock[ virtualMemToPhysicalMem(0x20000009) ]);
    TEST_ASSERT_EQUAL( 0x33, memoryBlock[ virtualMemToPhysicalMem(0x2000000a) ]);
    TEST_ASSERT_EQUAL( 0x33, memoryBlock[ virtualMemToPhysicalMem(0x2000000b) ]);
    TEST_ASSERT_EQUAL( 0x44, memoryBlock[ virtualMemToPhysicalMem(0x2000000c) ]);
    TEST_ASSERT_EQUAL( 0x44, memoryBlock[ virtualMemToPhysicalMem(0x2000000d) ]);
    TEST_ASSERT_EQUAL( 0x44, memoryBlock[ virtualMemToPhysicalMem(0x2000000e) ]);
    TEST_ASSERT_EQUAL( 0x44, memoryBlock[ virtualMemToPhysicalMem(0x2000000f) ]);
    TEST_ASSERT_EQUAL( 0x00, memoryBlock[ virtualMemToPhysicalMem(0x20000010) ]);
    TEST_ASSERT_EQUAL( 0x00, memoryBlock[ virtualMemToPhysicalMem(0x20000011) ]);
    TEST_ASSERT_EQUAL( 0x00, memoryBlock[ virtualMemToPhysicalMem(0x20000012) ]);
    TEST_ASSERT_EQUAL( 0x00, memoryBlock[ virtualMemToPhysicalMem(0x20000013) ]);
    TEST_ASSERT_EQUAL( 0x66, memoryBlock[ virtualMemToPhysicalMem(0x20000014) ]);
    TEST_ASSERT_EQUAL( 0x66, memoryBlock[ virtualMemToPhysicalMem(0x20000015) ]);
    TEST_ASSERT_EQUAL( 0x66, memoryBlock[ virtualMemToPhysicalMem(0x20000016) ]);
    TEST_ASSERT_EQUAL( 0x66, memoryBlock[ virtualMemToPhysicalMem(0x20000017) ]);
    TEST_ASSERT_EQUAL( 0x77, memoryBlock[ virtualMemToPhysicalMem(0x20000018) ]);
    TEST_ASSERT_EQUAL( 0x77, memoryBlock[ virtualMemToPhysicalMem(0x20000019) ]);
    TEST_ASSERT_EQUAL( 0x77, memoryBlock[ virtualMemToPhysicalMem(0x2000001a) ]);
    TEST_ASSERT_EQUAL( 0x77, memoryBlock[ virtualMemToPhysicalMem(0x2000001b) ]);
    TEST_ASSERT_EQUAL( 0x00, memoryBlock[ virtualMemToPhysicalMem(0x2000001c) ]);
    TEST_ASSERT_EQUAL( 0x00, memoryBlock[ virtualMemToPhysicalMem(0x2000001d) ]);
    TEST_ASSERT_EQUAL( 0x00, memoryBlock[ virtualMemToPhysicalMem(0x2000001e) ]);
    TEST_ASSERT_EQUAL( 0x80, memoryBlock[ virtualMemToPhysicalMem(0x2000001f) ]);
    TEST_ASSERT_EQUAL( 0x99, memoryBlock[ virtualMemToPhysicalMem(0x20000020) ]);
    TEST_ASSERT_EQUAL( 0x99, memoryBlock[ virtualMemToPhysicalMem(0x20000021) ]);
    TEST_ASSERT_EQUAL( 0x99, memoryBlock[ virtualMemToPhysicalMem(0x20000022) ]);
    TEST_ASSERT_EQUAL( 0x99, memoryBlock[ virtualMemToPhysicalMem(0x20000023) ]);
    TEST_ASSERT_EQUAL( 0xaa, memoryBlock[ virtualMemToPhysicalMem(0x20000024) ]);
    TEST_ASSERT_EQUAL( 0xaa, memoryBlock[ virtualMemToPhysicalMem(0x20000025) ]);
    TEST_ASSERT_EQUAL( 0xaa, memoryBlock[ virtualMemToPhysicalMem(0x20000026) ]);
    TEST_ASSERT_EQUAL( 0xaa, memoryBlock[ virtualMemToPhysicalMem(0x20000027) ]);
    TEST_ASSERT_EQUAL( 0xbb, memoryBlock[ virtualMemToPhysicalMem(0x20000028) ]);
    TEST_ASSERT_EQUAL( 0xbb, memoryBlock[ virtualMemToPhysicalMem(0x20000029) ]);
    TEST_ASSERT_EQUAL( 0xbb, memoryBlock[ virtualMemToPhysicalMem(0x2000002a) ]);
    TEST_ASSERT_EQUAL( 0xbb, memoryBlock[ virtualMemToPhysicalMem(0x2000002b) ]);
    TEST_ASSERT_EQUAL( 0xcc, memoryBlock[ virtualMemToPhysicalMem(0x2000002c) ]);
    TEST_ASSERT_EQUAL( 0xcc, memoryBlock[ virtualMemToPhysicalMem(0x2000002d) ]);
    TEST_ASSERT_EQUAL( 0xcc, memoryBlock[ virtualMemToPhysicalMem(0x2000002e) ]);
    TEST_ASSERT_EQUAL( 0xcc, memoryBlock[ virtualMemToPhysicalMem(0x2000002f) ]);
    TEST_ASSERT_EQUAL( 0xdd, memoryBlock[ virtualMemToPhysicalMem(0x20000030) ]);
    TEST_ASSERT_EQUAL( 0xdd, memoryBlock[ virtualMemToPhysicalMem(0x20000031) ]);
    TEST_ASSERT_EQUAL( 0xdd, memoryBlock[ virtualMemToPhysicalMem(0x20000032) ]);
    TEST_ASSERT_EQUAL( 0xdd, memoryBlock[ virtualMemToPhysicalMem(0x20000033) ]);
    TEST_ASSERT_EQUAL( 0xee, memoryBlock[ virtualMemToPhysicalMem(0x20000034) ]);
    TEST_ASSERT_EQUAL( 0xee, memoryBlock[ virtualMemToPhysicalMem(0x20000035) ]);
    TEST_ASSERT_EQUAL( 0xee, memoryBlock[ virtualMemToPhysicalMem(0x20000036) ]);
    TEST_ASSERT_EQUAL( 0xee, memoryBlock[ virtualMemToPhysicalMem(0x20000037) ]);
  }
  Catch(err)
  {
    TEST_FAIL_MESSAGE("Not expect error to be throw\n");
  }
}


/*---------------------------------------------------------------------------------------------------------------------------------------------------*/
  //LDMT2
  
//test ldm r0, {r1-r12}
/* Expected:
 *  r1 = 0x20001000
 *  r2 = 0x08000009
 *  r3 = 0xf04fbf00
 *  r4 = 0xf04f30ff
 *  r5 = 0xf04f31ff
 *  r6 = 0xf04f3233
 *  r7 = 0xf04f3344  
 *  r8 = 0xf04f0400
 *  r9 = 0xf04f3566
 *  r10 = 0xf04f3677
 *  r11 = 0xf04f4700
 *  r12 = 0xf04f3899
 * 
 */
void test_LDMRegisterT2_given_writeback_0_should_get_the_expected_result(void)
{
  CEXCEPTION_T err;
  memoryBlock[ virtualMemToPhysicalMem(0x08000000) ] = 0x00;
  memoryBlock[ virtualMemToPhysicalMem(0x08000001) ] = 0x10;
  memoryBlock[ virtualMemToPhysicalMem(0x08000002) ] = 0x00;
  memoryBlock[ virtualMemToPhysicalMem(0x08000003) ] = 0x20;
  memoryBlock[ virtualMemToPhysicalMem(0x08000004) ] = 0x09;
  memoryBlock[ virtualMemToPhysicalMem(0x08000005) ] = 0x00;
  memoryBlock[ virtualMemToPhysicalMem(0x08000006) ] = 0x00;
  memoryBlock[ virtualMemToPhysicalMem(0x08000007) ] = 0x08;
  memoryBlock[ virtualMemToPhysicalMem(0x08000008) ] = 0x00;
  memoryBlock[ virtualMemToPhysicalMem(0x08000009) ] = 0xbf;
  memoryBlock[ virtualMemToPhysicalMem(0x0800000a) ] = 0x4f;
  memoryBlock[ virtualMemToPhysicalMem(0x0800000b) ] = 0xf0;
  memoryBlock[ virtualMemToPhysicalMem(0x0800000c) ] = 0xff;
  memoryBlock[ virtualMemToPhysicalMem(0x0800000d) ] = 0x30;
  memoryBlock[ virtualMemToPhysicalMem(0x0800000e) ] = 0x4f;
  memoryBlock[ virtualMemToPhysicalMem(0x0800000f) ] = 0xf0;
  memoryBlock[ virtualMemToPhysicalMem(0x08000010) ] = 0xff;
  memoryBlock[ virtualMemToPhysicalMem(0x08000011) ] = 0x31;
  memoryBlock[ virtualMemToPhysicalMem(0x08000012) ] = 0x4f;
  memoryBlock[ virtualMemToPhysicalMem(0x08000013) ] = 0xf0;
  memoryBlock[ virtualMemToPhysicalMem(0x08000014) ] = 0x33;
  memoryBlock[ virtualMemToPhysicalMem(0x08000015) ] = 0x32;
  memoryBlock[ virtualMemToPhysicalMem(0x08000016) ] = 0x4f;
  memoryBlock[ virtualMemToPhysicalMem(0x08000017) ] = 0xf0;
  memoryBlock[ virtualMemToPhysicalMem(0x08000018) ] = 0x44;
  memoryBlock[ virtualMemToPhysicalMem(0x08000019) ] = 0x33;
  memoryBlock[ virtualMemToPhysicalMem(0x0800001a) ] = 0x4f;
  memoryBlock[ virtualMemToPhysicalMem(0x0800001b) ] = 0xf0;
  memoryBlock[ virtualMemToPhysicalMem(0x0800001c) ] = 0x00;
  memoryBlock[ virtualMemToPhysicalMem(0x0800001d) ] = 0x04;
  memoryBlock[ virtualMemToPhysicalMem(0x0800001e) ] = 0x4f;
  memoryBlock[ virtualMemToPhysicalMem(0x0800001f) ] = 0xf0;
  memoryBlock[ virtualMemToPhysicalMem(0x08000020) ] = 0x66;
  memoryBlock[ virtualMemToPhysicalMem(0x08000021) ] = 0x35;
  memoryBlock[ virtualMemToPhysicalMem(0x08000022) ] = 0x4f;
  memoryBlock[ virtualMemToPhysicalMem(0x08000023) ] = 0xf0;
  memoryBlock[ virtualMemToPhysicalMem(0x08000024) ] = 0x77;
  memoryBlock[ virtualMemToPhysicalMem(0x08000025) ] = 0x36;
  memoryBlock[ virtualMemToPhysicalMem(0x08000026) ] = 0x4f;
  memoryBlock[ virtualMemToPhysicalMem(0x08000027) ] = 0xf0;
  memoryBlock[ virtualMemToPhysicalMem(0x08000028) ] = 0x00;
  memoryBlock[ virtualMemToPhysicalMem(0x08000029) ] = 0x47;
  memoryBlock[ virtualMemToPhysicalMem(0x0800002a) ] = 0x4f;
  memoryBlock[ virtualMemToPhysicalMem(0x0800002b) ] = 0xf0;
  memoryBlock[ virtualMemToPhysicalMem(0x0800002c) ] = 0x99;
  memoryBlock[ virtualMemToPhysicalMem(0x0800002d) ] = 0x38;
  memoryBlock[ virtualMemToPhysicalMem(0x0800002e) ] = 0x4f;
  memoryBlock[ virtualMemToPhysicalMem(0x0800002f) ] = 0xf0;
  coreReg[0] = 0x08000000;
  
  Try
  {
    writeInstructionToMemoryGivenByAddress(0xe8901ffe, 0x08000046);  // ldm r0, {r1-r12}
    coreReg[PC] = 0x08000046;
    armStep();
    
    TEST_ASSERT_EQUAL( 0x0800004a, coreReg[PC]);
    TEST_ASSERT_EQUAL( 0x20001000, coreReg[1]);
    TEST_ASSERT_EQUAL( 0x08000009, coreReg[2]);
    TEST_ASSERT_EQUAL( 0xf04fbf00, coreReg[3]);
    TEST_ASSERT_EQUAL( 0xf04f30ff, coreReg[4]);
    TEST_ASSERT_EQUAL( 0xf04f31ff, coreReg[5]);
    TEST_ASSERT_EQUAL( 0xf04f3233, coreReg[6]);
    TEST_ASSERT_EQUAL( 0xf04f3344, coreReg[7]);
    TEST_ASSERT_EQUAL( 0xf04f0400, coreReg[8]);
    TEST_ASSERT_EQUAL( 0xf04f3566, coreReg[9]);
    TEST_ASSERT_EQUAL( 0xf04f3677, coreReg[10]);
    TEST_ASSERT_EQUAL( 0xf04f4700, coreReg[11]);
    TEST_ASSERT_EQUAL( 0xf04f3899, coreReg[12]);
  }
  Catch(err)
  {
    TEST_FAIL_MESSAGE("Not expect error to be throw\n");
  }
}



//test ldm r0!, {r1-r12}
/* Expected:
 *  r0 = 0x08000030
 *  r1 = 0x20001000
 *  r2 = 0x08000009
 *  r3 = 0xf04fbf00
 *  r4 = 0xf04f30ff
 *  r5 = 0xf04f31ff
 *  r6 = 0xf04f3233
 *  r7 = 0xf04f3344  
 *  r8 = 0xf04f0400
 *  r9 = 0xf04f3566
 *  r10 = 0xf04f3677
 *  r11 = 0xf04f4700
 *  r12 = 0xf04f3899
 * 
 */
void test_LDMRegisterT2_given_writeback_1_should_get_the_expected_result(void)
{ 
  CEXCEPTION_T err;
  memoryBlock[ virtualMemToPhysicalMem(0x08000000) ] = 0x00;
  memoryBlock[ virtualMemToPhysicalMem(0x08000001) ] = 0x10;
  memoryBlock[ virtualMemToPhysicalMem(0x08000002) ] = 0x00;
  memoryBlock[ virtualMemToPhysicalMem(0x08000003) ] = 0x20;
  memoryBlock[ virtualMemToPhysicalMem(0x08000004) ] = 0x09;
  memoryBlock[ virtualMemToPhysicalMem(0x08000005) ] = 0x00;
  memoryBlock[ virtualMemToPhysicalMem(0x08000006) ] = 0x00;
  memoryBlock[ virtualMemToPhysicalMem(0x08000007) ] = 0x08;
  memoryBlock[ virtualMemToPhysicalMem(0x08000008) ] = 0x00;
  memoryBlock[ virtualMemToPhysicalMem(0x08000009) ] = 0xbf;
  memoryBlock[ virtualMemToPhysicalMem(0x0800000a) ] = 0x4f;
  memoryBlock[ virtualMemToPhysicalMem(0x0800000b) ] = 0xf0;
  memoryBlock[ virtualMemToPhysicalMem(0x0800000c) ] = 0xff;
  memoryBlock[ virtualMemToPhysicalMem(0x0800000d) ] = 0x30;
  memoryBlock[ virtualMemToPhysicalMem(0x0800000e) ] = 0x4f;
  memoryBlock[ virtualMemToPhysicalMem(0x0800000f) ] = 0xf0;
  memoryBlock[ virtualMemToPhysicalMem(0x08000010) ] = 0xff;
  memoryBlock[ virtualMemToPhysicalMem(0x08000011) ] = 0x31;
  memoryBlock[ virtualMemToPhysicalMem(0x08000012) ] = 0x4f;
  memoryBlock[ virtualMemToPhysicalMem(0x08000013) ] = 0xf0;
  memoryBlock[ virtualMemToPhysicalMem(0x08000014) ] = 0x33;
  memoryBlock[ virtualMemToPhysicalMem(0x08000015) ] = 0x32;
  memoryBlock[ virtualMemToPhysicalMem(0x08000016) ] = 0x4f;
  memoryBlock[ virtualMemToPhysicalMem(0x08000017) ] = 0xf0;
  memoryBlock[ virtualMemToPhysicalMem(0x08000018) ] = 0x44;
  memoryBlock[ virtualMemToPhysicalMem(0x08000019) ] = 0x33;
  memoryBlock[ virtualMemToPhysicalMem(0x0800001a) ] = 0x4f;
  memoryBlock[ virtualMemToPhysicalMem(0x0800001b) ] = 0xf0;
  memoryBlock[ virtualMemToPhysicalMem(0x0800001c) ] = 0x00;
  memoryBlock[ virtualMemToPhysicalMem(0x0800001d) ] = 0x04;
  memoryBlock[ virtualMemToPhysicalMem(0x0800001e) ] = 0x4f;
  memoryBlock[ virtualMemToPhysicalMem(0x0800001f) ] = 0xf0;
  memoryBlock[ virtualMemToPhysicalMem(0x08000020) ] = 0x66;
  memoryBlock[ virtualMemToPhysicalMem(0x08000021) ] = 0x35;
  memoryBlock[ virtualMemToPhysicalMem(0x08000022) ] = 0x4f;
  memoryBlock[ virtualMemToPhysicalMem(0x08000023) ] = 0xf0;
  memoryBlock[ virtualMemToPhysicalMem(0x08000024) ] = 0x77;
  memoryBlock[ virtualMemToPhysicalMem(0x08000025) ] = 0x36;
  memoryBlock[ virtualMemToPhysicalMem(0x08000026) ] = 0x4f;
  memoryBlock[ virtualMemToPhysicalMem(0x08000027) ] = 0xf0;
  memoryBlock[ virtualMemToPhysicalMem(0x08000028) ] = 0x00;
  memoryBlock[ virtualMemToPhysicalMem(0x08000029) ] = 0x47;
  memoryBlock[ virtualMemToPhysicalMem(0x0800002a) ] = 0x4f;
  memoryBlock[ virtualMemToPhysicalMem(0x0800002b) ] = 0xf0;
  memoryBlock[ virtualMemToPhysicalMem(0x0800002c) ] = 0x99;
  memoryBlock[ virtualMemToPhysicalMem(0x0800002d) ] = 0x38;
  memoryBlock[ virtualMemToPhysicalMem(0x0800002e) ] = 0x4f;
  memoryBlock[ virtualMemToPhysicalMem(0x0800002f) ] = 0xf0;
  coreReg[0] = 0x08000000;
  
  Try
  {
    writeInstructionToMemoryGivenByAddress(0xe8b01ffe, 0x08000046);  // ldm r0!, {r1-r12}
    coreReg[PC] = 0x08000046;
    armStep();
    
    TEST_ASSERT_EQUAL( 0x08000030, coreReg[0]);
    TEST_ASSERT_EQUAL( 0x0800004a, coreReg[PC]);
    TEST_ASSERT_EQUAL( 0x20001000, coreReg[1]);
    TEST_ASSERT_EQUAL( 0x08000009, coreReg[2]);
    TEST_ASSERT_EQUAL( 0xf04fbf00, coreReg[3]);
    TEST_ASSERT_EQUAL( 0xf04f30ff, coreReg[4]);
    TEST_ASSERT_EQUAL( 0xf04f31ff, coreReg[5]);
    TEST_ASSERT_EQUAL( 0xf04f3233, coreReg[6]);
    TEST_ASSERT_EQUAL( 0xf04f3344, coreReg[7]);
    TEST_ASSERT_EQUAL( 0xf04f0400, coreReg[8]);
    TEST_ASSERT_EQUAL( 0xf04f3566, coreReg[9]);
    TEST_ASSERT_EQUAL( 0xf04f3677, coreReg[10]);
    TEST_ASSERT_EQUAL( 0xf04f4700, coreReg[11]);
    TEST_ASSERT_EQUAL( 0xf04f3899, coreReg[12]);
  }
  Catch(err)
  {
    TEST_FAIL_MESSAGE("Not expect error to be throw\n");
  }
}


void test_LDMRegisterT2_given_condition_is_not_meet_and_PC_is_in_the_regsiter_list_should_add_pc_correctly(void)
{
  writeInstructionToMemoryGivenByAddress(0xbf080000, 0x0800000a);  // IT EQ
  writeInstructionToMemoryGivenByAddress(0xe8b08002, 0x0800000c);  // ldmeq r0!, {r1,pc}
  coreReg[PC] = 0x0800000a;
  
  armStep();
  armStep();

  TEST_ASSERT_EQUAL( 0x0, coreReg[0]);
  TEST_ASSERT_EQUAL( 0x08000010, coreReg[PC]);
}



/*---------------------------------------------------------------------------------------------------------------------------------------------------*/
  //LDMDB
  
  
//test ldmdb r0, {r1-r12}
/* Expected:
 *  r0 = 0x08000030
 *  r1 = 0x20001000
 *  r2 = 0x08000009
 *  r3 = 0xf04fbf00
 *  r4 = 0xf04f30ff
 *  r5 = 0xf04f31ff
 *  r6 = 0xf04f3233
 *  r7 = 0xf04f3344  
 *  r8 = 0xf04f0400
 *  r9 = 0xf04f3566
 *  r10 = 0xf04f3677
 *  r11 = 0xf04f4700
 *  r12 = 0xf04f3899
 * 
 */
void test_LDMDB_given_writeback_0_should_get_the_expected_result(void)
{
  CEXCEPTION_T err;
  memoryBlock[ virtualMemToPhysicalMem(0x08000000) ] = 0x00;
  memoryBlock[ virtualMemToPhysicalMem(0x08000001) ] = 0x10;
  memoryBlock[ virtualMemToPhysicalMem(0x08000002) ] = 0x00;
  memoryBlock[ virtualMemToPhysicalMem(0x08000003) ] = 0x20;
  memoryBlock[ virtualMemToPhysicalMem(0x08000004) ] = 0x09;
  memoryBlock[ virtualMemToPhysicalMem(0x08000005) ] = 0x00;
  memoryBlock[ virtualMemToPhysicalMem(0x08000006) ] = 0x00;
  memoryBlock[ virtualMemToPhysicalMem(0x08000007) ] = 0x08;
  memoryBlock[ virtualMemToPhysicalMem(0x08000008) ] = 0x00;
  memoryBlock[ virtualMemToPhysicalMem(0x08000009) ] = 0xbf;
  memoryBlock[ virtualMemToPhysicalMem(0x0800000a) ] = 0x4f;
  memoryBlock[ virtualMemToPhysicalMem(0x0800000b) ] = 0xf0;
  memoryBlock[ virtualMemToPhysicalMem(0x0800000c) ] = 0xff;
  memoryBlock[ virtualMemToPhysicalMem(0x0800000d) ] = 0x30;
  memoryBlock[ virtualMemToPhysicalMem(0x0800000e) ] = 0x4f;
  memoryBlock[ virtualMemToPhysicalMem(0x0800000f) ] = 0xf0;
  memoryBlock[ virtualMemToPhysicalMem(0x08000010) ] = 0xff;
  memoryBlock[ virtualMemToPhysicalMem(0x08000011) ] = 0x31;
  memoryBlock[ virtualMemToPhysicalMem(0x08000012) ] = 0x4f;
  memoryBlock[ virtualMemToPhysicalMem(0x08000013) ] = 0xf0;
  memoryBlock[ virtualMemToPhysicalMem(0x08000014) ] = 0x33;
  memoryBlock[ virtualMemToPhysicalMem(0x08000015) ] = 0x32;
  memoryBlock[ virtualMemToPhysicalMem(0x08000016) ] = 0x4f;
  memoryBlock[ virtualMemToPhysicalMem(0x08000017) ] = 0xf0;
  memoryBlock[ virtualMemToPhysicalMem(0x08000018) ] = 0x44;
  memoryBlock[ virtualMemToPhysicalMem(0x08000019) ] = 0x33;
  memoryBlock[ virtualMemToPhysicalMem(0x0800001a) ] = 0x4f;
  memoryBlock[ virtualMemToPhysicalMem(0x0800001b) ] = 0xf0;
  memoryBlock[ virtualMemToPhysicalMem(0x0800001c) ] = 0x00;
  memoryBlock[ virtualMemToPhysicalMem(0x0800001d) ] = 0x04;
  memoryBlock[ virtualMemToPhysicalMem(0x0800001e) ] = 0x4f;
  memoryBlock[ virtualMemToPhysicalMem(0x0800001f) ] = 0xf0;
  memoryBlock[ virtualMemToPhysicalMem(0x08000020) ] = 0x66;
  memoryBlock[ virtualMemToPhysicalMem(0x08000021) ] = 0x35;
  memoryBlock[ virtualMemToPhysicalMem(0x08000022) ] = 0x4f;
  memoryBlock[ virtualMemToPhysicalMem(0x08000023) ] = 0xf0;
  memoryBlock[ virtualMemToPhysicalMem(0x08000024) ] = 0x77;
  memoryBlock[ virtualMemToPhysicalMem(0x08000025) ] = 0x36;
  memoryBlock[ virtualMemToPhysicalMem(0x08000026) ] = 0x4f;
  memoryBlock[ virtualMemToPhysicalMem(0x08000027) ] = 0xf0;
  memoryBlock[ virtualMemToPhysicalMem(0x08000028) ] = 0x00;
  memoryBlock[ virtualMemToPhysicalMem(0x08000029) ] = 0x47;
  memoryBlock[ virtualMemToPhysicalMem(0x0800002a) ] = 0x4f;
  memoryBlock[ virtualMemToPhysicalMem(0x0800002b) ] = 0xf0;
  memoryBlock[ virtualMemToPhysicalMem(0x0800002c) ] = 0x99;
  memoryBlock[ virtualMemToPhysicalMem(0x0800002d) ] = 0x38;
  memoryBlock[ virtualMemToPhysicalMem(0x0800002e) ] = 0x4f;
  memoryBlock[ virtualMemToPhysicalMem(0x0800002f) ] = 0xf0;
  coreReg[0] = 0x08000030;
  
  Try
  {
    writeInstructionToMemoryGivenByAddress(0xe9101ffe, 0x08000046);  // ldmdb r0, {r1-r12}
    coreReg[PC] = 0x08000046;
    armStep();
    
    TEST_ASSERT_EQUAL( 0x08000030, coreReg[0]);
    TEST_ASSERT_EQUAL( 0x0800004a, coreReg[PC]);
    TEST_ASSERT_EQUAL( 0x20001000, coreReg[1]);
    TEST_ASSERT_EQUAL( 0x08000009, coreReg[2]);
    TEST_ASSERT_EQUAL( 0xf04fbf00, coreReg[3]);
    TEST_ASSERT_EQUAL( 0xf04f30ff, coreReg[4]);
    TEST_ASSERT_EQUAL( 0xf04f31ff, coreReg[5]);
    TEST_ASSERT_EQUAL( 0xf04f3233, coreReg[6]);
    TEST_ASSERT_EQUAL( 0xf04f3344, coreReg[7]);
    TEST_ASSERT_EQUAL( 0xf04f0400, coreReg[8]);
    TEST_ASSERT_EQUAL( 0xf04f3566, coreReg[9]);
    TEST_ASSERT_EQUAL( 0xf04f3677, coreReg[10]);
    TEST_ASSERT_EQUAL( 0xf04f4700, coreReg[11]);
    TEST_ASSERT_EQUAL( 0xf04f3899, coreReg[12]);
  }
  Catch(err)
  {
    TEST_FAIL_MESSAGE("Not expect error to be throw\n");
  }
}





//test ldmdb r0!, {r1-r12}
/* Expected:
 *  r0 = 0x08000000
 *  r1 = 0x20001000
 *  r2 = 0x08000009
 *  r3 = 0xf04fbf00
 *  r4 = 0xf04f30ff
 *  r5 = 0xf04f31ff
 *  r6 = 0xf04f3233
 *  r7 = 0xf04f3344  
 *  r8 = 0xf04f0400
 *  r9 = 0xf04f3566
 *  r10 = 0xf04f3677
 *  r11 = 0xf04f4700
 *  r12 = 0xf04f3899
 * 
 */
void test_LDMDB_given_writeback_1_should_get_the_expected_result(void)
{
  CEXCEPTION_T err;
  memoryBlock[ virtualMemToPhysicalMem(0x08000000) ] = 0x00;
  memoryBlock[ virtualMemToPhysicalMem(0x08000001) ] = 0x10;
  memoryBlock[ virtualMemToPhysicalMem(0x08000002) ] = 0x00;
  memoryBlock[ virtualMemToPhysicalMem(0x08000003) ] = 0x20;
  memoryBlock[ virtualMemToPhysicalMem(0x08000004) ] = 0x09;
  memoryBlock[ virtualMemToPhysicalMem(0x08000005) ] = 0x00;
  memoryBlock[ virtualMemToPhysicalMem(0x08000006) ] = 0x00;
  memoryBlock[ virtualMemToPhysicalMem(0x08000007) ] = 0x08;
  memoryBlock[ virtualMemToPhysicalMem(0x08000008) ] = 0x00;
  memoryBlock[ virtualMemToPhysicalMem(0x08000009) ] = 0xbf;
  memoryBlock[ virtualMemToPhysicalMem(0x0800000a) ] = 0x4f;
  memoryBlock[ virtualMemToPhysicalMem(0x0800000b) ] = 0xf0;
  memoryBlock[ virtualMemToPhysicalMem(0x0800000c) ] = 0xff;
  memoryBlock[ virtualMemToPhysicalMem(0x0800000d) ] = 0x30;
  memoryBlock[ virtualMemToPhysicalMem(0x0800000e) ] = 0x4f;
  memoryBlock[ virtualMemToPhysicalMem(0x0800000f) ] = 0xf0;
  memoryBlock[ virtualMemToPhysicalMem(0x08000010) ] = 0xff;
  memoryBlock[ virtualMemToPhysicalMem(0x08000011) ] = 0x31;
  memoryBlock[ virtualMemToPhysicalMem(0x08000012) ] = 0x4f;
  memoryBlock[ virtualMemToPhysicalMem(0x08000013) ] = 0xf0;
  memoryBlock[ virtualMemToPhysicalMem(0x08000014) ] = 0x33;
  memoryBlock[ virtualMemToPhysicalMem(0x08000015) ] = 0x32;
  memoryBlock[ virtualMemToPhysicalMem(0x08000016) ] = 0x4f;
  memoryBlock[ virtualMemToPhysicalMem(0x08000017) ] = 0xf0;
  memoryBlock[ virtualMemToPhysicalMem(0x08000018) ] = 0x44;
  memoryBlock[ virtualMemToPhysicalMem(0x08000019) ] = 0x33;
  memoryBlock[ virtualMemToPhysicalMem(0x0800001a) ] = 0x4f;
  memoryBlock[ virtualMemToPhysicalMem(0x0800001b) ] = 0xf0;
  memoryBlock[ virtualMemToPhysicalMem(0x0800001c) ] = 0x00;
  memoryBlock[ virtualMemToPhysicalMem(0x0800001d) ] = 0x04;
  memoryBlock[ virtualMemToPhysicalMem(0x0800001e) ] = 0x4f;
  memoryBlock[ virtualMemToPhysicalMem(0x0800001f) ] = 0xf0;
  memoryBlock[ virtualMemToPhysicalMem(0x08000020) ] = 0x66;
  memoryBlock[ virtualMemToPhysicalMem(0x08000021) ] = 0x35;
  memoryBlock[ virtualMemToPhysicalMem(0x08000022) ] = 0x4f;
  memoryBlock[ virtualMemToPhysicalMem(0x08000023) ] = 0xf0;
  memoryBlock[ virtualMemToPhysicalMem(0x08000024) ] = 0x77;
  memoryBlock[ virtualMemToPhysicalMem(0x08000025) ] = 0x36;
  memoryBlock[ virtualMemToPhysicalMem(0x08000026) ] = 0x4f;
  memoryBlock[ virtualMemToPhysicalMem(0x08000027) ] = 0xf0;
  memoryBlock[ virtualMemToPhysicalMem(0x08000028) ] = 0x00;
  memoryBlock[ virtualMemToPhysicalMem(0x08000029) ] = 0x47;
  memoryBlock[ virtualMemToPhysicalMem(0x0800002a) ] = 0x4f;
  memoryBlock[ virtualMemToPhysicalMem(0x0800002b) ] = 0xf0;
  memoryBlock[ virtualMemToPhysicalMem(0x0800002c) ] = 0x99;
  memoryBlock[ virtualMemToPhysicalMem(0x0800002d) ] = 0x38;
  memoryBlock[ virtualMemToPhysicalMem(0x0800002e) ] = 0x4f;
  memoryBlock[ virtualMemToPhysicalMem(0x0800002f) ] = 0xf0;
  coreReg[0] = 0x08000030;
  
  Try
  {
    writeInstructionToMemoryGivenByAddress(0xe9301ffe, 0x08000046);  // ldmdb r0!, {r1-r12}
    coreReg[PC] = 0x08000046;
    armStep();
    
    TEST_ASSERT_EQUAL( 0x08000000, coreReg[0]);
    TEST_ASSERT_EQUAL( 0x0800004a, coreReg[PC]);
    TEST_ASSERT_EQUAL( 0x20001000, coreReg[1]);
    TEST_ASSERT_EQUAL( 0x08000009, coreReg[2]);
    TEST_ASSERT_EQUAL( 0xf04fbf00, coreReg[3]);
    TEST_ASSERT_EQUAL( 0xf04f30ff, coreReg[4]);
    TEST_ASSERT_EQUAL( 0xf04f31ff, coreReg[5]);
    TEST_ASSERT_EQUAL( 0xf04f3233, coreReg[6]);
    TEST_ASSERT_EQUAL( 0xf04f3344, coreReg[7]);
    TEST_ASSERT_EQUAL( 0xf04f0400, coreReg[8]);
    TEST_ASSERT_EQUAL( 0xf04f3566, coreReg[9]);
    TEST_ASSERT_EQUAL( 0xf04f3677, coreReg[10]);
    TEST_ASSERT_EQUAL( 0xf04f4700, coreReg[11]);
    TEST_ASSERT_EQUAL( 0xf04f3899, coreReg[12]);
  }
  Catch(err)
  {
    TEST_FAIL_MESSAGE("Not expect error to be throw\n");
  }
}


void test_LDMDB_given_condition_is_not_meet_and_PC_is_in_the_regsiter_list_should_add_pc_correctly(void)
{
  writeInstructionToMemoryGivenByAddress(0xbf080000, 0x0800000a);  // IT EQ
  writeInstructionToMemoryGivenByAddress(0xe93087fe, 0x0800000c);  // ldmdbeq.w r0!, {r1,r2,r3,r4,r5,r6,r7,r8,r9,r10,pc}
  coreReg[PC] = 0x0800000a;
  
  armStep();
  armStep();

  TEST_ASSERT_EQUAL( 0x0, coreReg[0]);
  TEST_ASSERT_EQUAL( 0x08000010, coreReg[PC]);
}


/*---------------------------------------------------------------------------------------------------------------------------------------------------*/
  //POPT2
  

//test pop {r1-r12}
/* Expected:
 *  SP = 0x20001030
 *  r1 = 0x20001000
 *  r2 = 0x08000009
 *  r3 = 0xf04fbf00
 *  r4 = 0xf04f30ff
 *  r5 = 0xf04f31ff
 *  r6 = 0xf04f3233
 *  r7 = 0xf04f3344  
 *  r8 = 0xf04f0400
 *  r9 = 0xf04f3566
 *  r10 = 0xf04f3677
 *  r11 = 0xf04f4700
 *  r12 = 0xf04f3899
 * 
 */
void test_POPT2_should_get_the_expected_result(void)
{
  CEXCEPTION_T err;
  memoryBlock[ virtualMemToPhysicalMem(0x20001000) ] = 0x00;
  memoryBlock[ virtualMemToPhysicalMem(0x20001001) ] = 0x10;
  memoryBlock[ virtualMemToPhysicalMem(0x20001002) ] = 0x00;
  memoryBlock[ virtualMemToPhysicalMem(0x20001003) ] = 0x20;
  memoryBlock[ virtualMemToPhysicalMem(0x20001004) ] = 0x09;
  memoryBlock[ virtualMemToPhysicalMem(0x20001005) ] = 0x00;
  memoryBlock[ virtualMemToPhysicalMem(0x20001006) ] = 0x00;
  memoryBlock[ virtualMemToPhysicalMem(0x20001007) ] = 0x08;
  memoryBlock[ virtualMemToPhysicalMem(0x20001008) ] = 0x00;
  memoryBlock[ virtualMemToPhysicalMem(0x20001009) ] = 0xbf;
  memoryBlock[ virtualMemToPhysicalMem(0x2000100a) ] = 0x4f;
  memoryBlock[ virtualMemToPhysicalMem(0x2000100b) ] = 0xf0;
  memoryBlock[ virtualMemToPhysicalMem(0x2000100c) ] = 0xff;
  memoryBlock[ virtualMemToPhysicalMem(0x2000100d) ] = 0x30;
  memoryBlock[ virtualMemToPhysicalMem(0x2000100e) ] = 0x4f;
  memoryBlock[ virtualMemToPhysicalMem(0x2000100f) ] = 0xf0;
  memoryBlock[ virtualMemToPhysicalMem(0x20001010) ] = 0xff;
  memoryBlock[ virtualMemToPhysicalMem(0x20001011) ] = 0x31;
  memoryBlock[ virtualMemToPhysicalMem(0x20001012) ] = 0x4f;
  memoryBlock[ virtualMemToPhysicalMem(0x20001013) ] = 0xf0;
  memoryBlock[ virtualMemToPhysicalMem(0x20001014) ] = 0x33;
  memoryBlock[ virtualMemToPhysicalMem(0x20001015) ] = 0x32;
  memoryBlock[ virtualMemToPhysicalMem(0x20001016) ] = 0x4f;
  memoryBlock[ virtualMemToPhysicalMem(0x20001017) ] = 0xf0;
  memoryBlock[ virtualMemToPhysicalMem(0x20001018) ] = 0x44;
  memoryBlock[ virtualMemToPhysicalMem(0x20001019) ] = 0x33;
  memoryBlock[ virtualMemToPhysicalMem(0x2000101a) ] = 0x4f;
  memoryBlock[ virtualMemToPhysicalMem(0x2000101b) ] = 0xf0;
  memoryBlock[ virtualMemToPhysicalMem(0x2000101c) ] = 0x00;
  memoryBlock[ virtualMemToPhysicalMem(0x2000101d) ] = 0x04;
  memoryBlock[ virtualMemToPhysicalMem(0x2000101e) ] = 0x4f;
  memoryBlock[ virtualMemToPhysicalMem(0x2000101f) ] = 0xf0;
  memoryBlock[ virtualMemToPhysicalMem(0x20001020) ] = 0x66;
  memoryBlock[ virtualMemToPhysicalMem(0x20001021) ] = 0x35;
  memoryBlock[ virtualMemToPhysicalMem(0x20001022) ] = 0x4f;
  memoryBlock[ virtualMemToPhysicalMem(0x20001023) ] = 0xf0;
  memoryBlock[ virtualMemToPhysicalMem(0x20001024) ] = 0x77;
  memoryBlock[ virtualMemToPhysicalMem(0x20001025) ] = 0x36;
  memoryBlock[ virtualMemToPhysicalMem(0x20001026) ] = 0x4f;
  memoryBlock[ virtualMemToPhysicalMem(0x20001027) ] = 0xf0;
  memoryBlock[ virtualMemToPhysicalMem(0x20001028) ] = 0x00;
  memoryBlock[ virtualMemToPhysicalMem(0x20001029) ] = 0x47;
  memoryBlock[ virtualMemToPhysicalMem(0x2000102a) ] = 0x4f;
  memoryBlock[ virtualMemToPhysicalMem(0x2000102b) ] = 0xf0;
  memoryBlock[ virtualMemToPhysicalMem(0x2000102c) ] = 0x99;
  memoryBlock[ virtualMemToPhysicalMem(0x2000102d) ] = 0x38;
  memoryBlock[ virtualMemToPhysicalMem(0x2000102e) ] = 0x4f;
  memoryBlock[ virtualMemToPhysicalMem(0x2000102f) ] = 0xf0;
  
  Try
  {
    writeInstructionToMemoryGivenByAddress(0xe8bd1ffe, 0x08000046);  // pop {r1-r12}
    coreReg[PC] = 0x08000046;
    coreReg[SP] = 0x20001000;
    armStep();
    
    TEST_ASSERT_EQUAL( 0x0800004a, coreReg[PC]);
    TEST_ASSERT_EQUAL( 0x20001030, coreReg[SP]);
    TEST_ASSERT_EQUAL( 0x20001000, coreReg[1]);
    TEST_ASSERT_EQUAL( 0x08000009, coreReg[2]);
    TEST_ASSERT_EQUAL( 0xf04fbf00, coreReg[3]);
    TEST_ASSERT_EQUAL( 0xf04f30ff, coreReg[4]);
    TEST_ASSERT_EQUAL( 0xf04f31ff, coreReg[5]);
    TEST_ASSERT_EQUAL( 0xf04f3233, coreReg[6]);
    TEST_ASSERT_EQUAL( 0xf04f3344, coreReg[7]);
    TEST_ASSERT_EQUAL( 0xf04f0400, coreReg[8]);
    TEST_ASSERT_EQUAL( 0xf04f3566, coreReg[9]);
    TEST_ASSERT_EQUAL( 0xf04f3677, coreReg[10]);
    TEST_ASSERT_EQUAL( 0xf04f4700, coreReg[11]);
    TEST_ASSERT_EQUAL( 0xf04f3899, coreReg[12]);
  }
  Catch(err)
  {
    TEST_FAIL_MESSAGE("Not expect error to be throw\n");
  }
}


void test_POPT2_given_condition_is_not_meet_and_PC_is_in_the_regsiter_list_should_add_pc_correctly(void)
{
  writeInstructionToMemoryGivenByAddress(0xbf080000, 0x0800000a);  // IT EQ
  writeInstructionToMemoryGivenByAddress(0xe8bd87fe, 0x0800000c);  // popeq.w r0!, {r1,r2,r3,r4,r5,r6,r7,r8,r9,r10,pc}
  coreReg[PC] = 0x0800000a;
  
  armStep();
  armStep();

  TEST_ASSERT_EQUAL( 0x0, coreReg[0]);
  TEST_ASSERT_EQUAL( 0x08000010, coreReg[PC]);
}

/*---------------------------------------------------------------------------------------------------------------------------------------------------*/
  //PUSHT2



//test push {r0-r12, r14}
/*  r0 = 0x20000000
 *  r1 = 0xffffffff
 *  r2 = 0x33333333
 *  r3 = 0x44444444
 *  r4 = 0x00000000
 *  r5 = 0x66666666
 *  r6 = 0x77777777
 *  r7 = 0x80000000   
 *  r8 = 0x99999999
 *  r9 = 0xaaaaaaaa
 *  r10 = 0xbbbbbbbb
 *  r11 = 0xcccccccc
 *  r12 = 0xdddddddd
 *  r14 = 0xeeeeeeee
 * 
 * Expected:
 *  Memory address 0x20000000 = 0x00
 *  Memory address 0x20000001 = 0x00
 *  Memory address 0x20000002 = 0x00
 *  Memory address 0x20000003 = 0x20
 *  Memory address 0x20000004 = 0xff
 *  Memory address 0x20000005 = 0xff
 *  Memory address 0x20000006 = 0xff
 *  Memory address 0x20000007 = 0xff
 *  Memory address 0x20000008 = 0x33
 *  Memory address 0x20000009 = 0x33
 *  Memory address 0x2000000a = 0x33
 *  Memory address 0x2000000b = 0x33
 *  Memory address 0x2000000c = 0x44
 *  Memory address 0x2000000d = 0x44
 *  Memory address 0x2000000e = 0x44
 *  Memory address 0x2000000f = 0x44
 *  Memory address 0x20000010 = 0x00
 *  Memory address 0x20000011 = 0x00
 *  Memory address 0x20000012 = 0x00
 *  Memory address 0x20000013 = 0x00
 *  Memory address 0x20000014 = 0x66
 *  Memory address 0x20000015 = 0x66
 *  Memory address 0x20000016 = 0x66
 *  Memory address 0x20000017 = 0x66
 *  Memory address 0x20000018 = 0x77
 *  Memory address 0x20000019 = 0x77
 *  Memory address 0x2000001a = 0x77
 *  Memory address 0x2000001b = 0x77
 *  Memory address 0x2000001c = 0x00
 *  Memory address 0x2000001d = 0x00
 *  Memory address 0x2000001e = 0x00
 *  Memory address 0x2000001f = 0x80
 *  Memory address 0x20000020 = 0x99
 *  Memory address 0x20000021 = 0x99
 *  Memory address 0x20000022 = 0x99
 *  Memory address 0x20000023 = 0x99
 *  Memory address 0x20000024 = 0xaa
 *  Memory address 0x20000025 = 0xaa
 *  Memory address 0x20000026 = 0xaa
 *  Memory address 0x20000027 = 0xaa
 *  Memory address 0x20000028 = 0xbb
 *  Memory address 0x20000029 = 0xbb
 *  Memory address 0x2000002a = 0xbb
 *  Memory address 0x2000002b = 0xbb
 *  Memory address 0x2000002c = 0xcc
 *  Memory address 0x2000002d = 0xcc
 *  Memory address 0x2000002e = 0xcc
 *  Memory address 0x2000002f = 0xcc
 *  Memory address 0x20000030 = 0xdd
 *  Memory address 0x20000031 = 0xdd
 *  Memory address 0x20000032 = 0xdd
 *  Memory address 0x20000033 = 0xdd
 *  Memory address 0x20000034 = 0xee
 *  Memory address 0x20000035 = 0xee
 *  Memory address 0x20000036 = 0xee
 *  Memory address 0x20000037 = 0xee
 
 */
void test_PUSHT2_should_get_the_expected_result(void)
{
  CEXCEPTION_T err;
  coreReg[0] = 0x20000000;
  coreReg[1] = 0xffffffff;
  coreReg[2] = 0x33333333;
  coreReg[3] = 0x44444444;
  coreReg[4] = 0x00000000;
  coreReg[5] = 0x66666666;
  coreReg[6] = 0x77777777;
  coreReg[7] = 0x80000000;
  coreReg[8] = 0x99999999;
  coreReg[9] = 0xaaaaaaaa;
  coreReg[10] = 0xbbbbbbbb;
  coreReg[11] = 0xcccccccc;
  coreReg[12] = 0xdddddddd;
  coreReg[14] = 0xeeeeeeee;

  Try
  {
    writeInstructionToMemoryGivenByAddress(0xe92d5fff, 0x0800004a);  // push {r0-r12, r14}
    coreReg[PC] = 0x0800004a;
    coreReg[SP] = 0x20001038;
    armStep();
    
    TEST_ASSERT_EQUAL( 0x0800004e, coreReg[PC]);
    TEST_ASSERT_EQUAL( 0x20001000, coreReg[SP]);
    TEST_ASSERT_EQUAL( 0x00, memoryBlock[ virtualMemToPhysicalMem(0x20001000) ]);
    TEST_ASSERT_EQUAL( 0x00, memoryBlock[ virtualMemToPhysicalMem(0x20001001) ]);
    TEST_ASSERT_EQUAL( 0x00, memoryBlock[ virtualMemToPhysicalMem(0x20001002) ]);
    TEST_ASSERT_EQUAL( 0x20, memoryBlock[ virtualMemToPhysicalMem(0x20001003) ]);
    TEST_ASSERT_EQUAL( 0xff, memoryBlock[ virtualMemToPhysicalMem(0x20001004) ]);
    TEST_ASSERT_EQUAL( 0xff, memoryBlock[ virtualMemToPhysicalMem(0x20001005) ]);
    TEST_ASSERT_EQUAL( 0xff, memoryBlock[ virtualMemToPhysicalMem(0x20001006) ]);
    TEST_ASSERT_EQUAL( 0xff, memoryBlock[ virtualMemToPhysicalMem(0x20001007) ]);
    TEST_ASSERT_EQUAL( 0x33, memoryBlock[ virtualMemToPhysicalMem(0x20001008) ]);
    TEST_ASSERT_EQUAL( 0x33, memoryBlock[ virtualMemToPhysicalMem(0x20001009) ]);
    TEST_ASSERT_EQUAL( 0x33, memoryBlock[ virtualMemToPhysicalMem(0x2000100a) ]);
    TEST_ASSERT_EQUAL( 0x33, memoryBlock[ virtualMemToPhysicalMem(0x2000100b) ]);
    TEST_ASSERT_EQUAL( 0x44, memoryBlock[ virtualMemToPhysicalMem(0x2000100c) ]);
    TEST_ASSERT_EQUAL( 0x44, memoryBlock[ virtualMemToPhysicalMem(0x2000100d) ]);
    TEST_ASSERT_EQUAL( 0x44, memoryBlock[ virtualMemToPhysicalMem(0x2000100e) ]);
    TEST_ASSERT_EQUAL( 0x44, memoryBlock[ virtualMemToPhysicalMem(0x2000100f) ]);
    TEST_ASSERT_EQUAL( 0x00, memoryBlock[ virtualMemToPhysicalMem(0x20001010) ]);
    TEST_ASSERT_EQUAL( 0x00, memoryBlock[ virtualMemToPhysicalMem(0x20001011) ]);
    TEST_ASSERT_EQUAL( 0x00, memoryBlock[ virtualMemToPhysicalMem(0x20001012) ]);
    TEST_ASSERT_EQUAL( 0x00, memoryBlock[ virtualMemToPhysicalMem(0x20001013) ]);
    TEST_ASSERT_EQUAL( 0x66, memoryBlock[ virtualMemToPhysicalMem(0x20001014) ]);
    TEST_ASSERT_EQUAL( 0x66, memoryBlock[ virtualMemToPhysicalMem(0x20001015) ]);
    TEST_ASSERT_EQUAL( 0x66, memoryBlock[ virtualMemToPhysicalMem(0x20001016) ]);
    TEST_ASSERT_EQUAL( 0x66, memoryBlock[ virtualMemToPhysicalMem(0x20001017) ]);
    TEST_ASSERT_EQUAL( 0x77, memoryBlock[ virtualMemToPhysicalMem(0x20001018) ]);
    TEST_ASSERT_EQUAL( 0x77, memoryBlock[ virtualMemToPhysicalMem(0x20001019) ]);
    TEST_ASSERT_EQUAL( 0x77, memoryBlock[ virtualMemToPhysicalMem(0x2000101a) ]);
    TEST_ASSERT_EQUAL( 0x77, memoryBlock[ virtualMemToPhysicalMem(0x2000101b) ]);
    TEST_ASSERT_EQUAL( 0x00, memoryBlock[ virtualMemToPhysicalMem(0x2000101c) ]);
    TEST_ASSERT_EQUAL( 0x00, memoryBlock[ virtualMemToPhysicalMem(0x2000101d) ]);
    TEST_ASSERT_EQUAL( 0x00, memoryBlock[ virtualMemToPhysicalMem(0x2000101e) ]);
    TEST_ASSERT_EQUAL( 0x80, memoryBlock[ virtualMemToPhysicalMem(0x2000101f) ]);
    TEST_ASSERT_EQUAL( 0x99, memoryBlock[ virtualMemToPhysicalMem(0x20001020) ]);
    TEST_ASSERT_EQUAL( 0x99, memoryBlock[ virtualMemToPhysicalMem(0x20001021) ]);
    TEST_ASSERT_EQUAL( 0x99, memoryBlock[ virtualMemToPhysicalMem(0x20001022) ]);
    TEST_ASSERT_EQUAL( 0x99, memoryBlock[ virtualMemToPhysicalMem(0x20001023) ]);
    TEST_ASSERT_EQUAL( 0xaa, memoryBlock[ virtualMemToPhysicalMem(0x20001024) ]);
    TEST_ASSERT_EQUAL( 0xaa, memoryBlock[ virtualMemToPhysicalMem(0x20001025) ]);
    TEST_ASSERT_EQUAL( 0xaa, memoryBlock[ virtualMemToPhysicalMem(0x20001026) ]);
    TEST_ASSERT_EQUAL( 0xaa, memoryBlock[ virtualMemToPhysicalMem(0x20001027) ]);
    TEST_ASSERT_EQUAL( 0xbb, memoryBlock[ virtualMemToPhysicalMem(0x20001028) ]);
    TEST_ASSERT_EQUAL( 0xbb, memoryBlock[ virtualMemToPhysicalMem(0x20001029) ]);
    TEST_ASSERT_EQUAL( 0xbb, memoryBlock[ virtualMemToPhysicalMem(0x2000102a) ]);
    TEST_ASSERT_EQUAL( 0xbb, memoryBlock[ virtualMemToPhysicalMem(0x2000102b) ]);
    TEST_ASSERT_EQUAL( 0xcc, memoryBlock[ virtualMemToPhysicalMem(0x2000102c) ]);
    TEST_ASSERT_EQUAL( 0xcc, memoryBlock[ virtualMemToPhysicalMem(0x2000102d) ]);
    TEST_ASSERT_EQUAL( 0xcc, memoryBlock[ virtualMemToPhysicalMem(0x2000102e) ]);
    TEST_ASSERT_EQUAL( 0xcc, memoryBlock[ virtualMemToPhysicalMem(0x2000102f) ]);
    TEST_ASSERT_EQUAL( 0xdd, memoryBlock[ virtualMemToPhysicalMem(0x20001030) ]);
    TEST_ASSERT_EQUAL( 0xdd, memoryBlock[ virtualMemToPhysicalMem(0x20001031) ]);
    TEST_ASSERT_EQUAL( 0xdd, memoryBlock[ virtualMemToPhysicalMem(0x20001032) ]);
    TEST_ASSERT_EQUAL( 0xdd, memoryBlock[ virtualMemToPhysicalMem(0x20001033) ]);
    TEST_ASSERT_EQUAL( 0xee, memoryBlock[ virtualMemToPhysicalMem(0x20001034) ]);
    TEST_ASSERT_EQUAL( 0xee, memoryBlock[ virtualMemToPhysicalMem(0x20001035) ]);
    TEST_ASSERT_EQUAL( 0xee, memoryBlock[ virtualMemToPhysicalMem(0x20001036) ]);
    TEST_ASSERT_EQUAL( 0xee, memoryBlock[ virtualMemToPhysicalMem(0x20001037) ]);
  }
  Catch(err)
  {
    TEST_FAIL_MESSAGE("Not expect error to be throw\n");
  }
}


