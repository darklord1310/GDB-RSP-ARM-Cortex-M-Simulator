#include "Thumb32bitsTable.h"
#include <stdio.h>




void initThumb32Table()
{
  Thumb32Table[0b1000000000] = executeDataProcessingModifiedImmediate;
  Thumb32Table[0b1000000010] = executeDataProcessingModifiedImmediate;
  Thumb32Table[0b1000000010] = executeDataProcessingModifiedImmediate;
  Thumb32Table[0b1000000100] = executeDataProcessingModifiedImmediate;
  Thumb32Table[0b1000000110] = executeDataProcessingModifiedImmediate;
  Thumb32Table[0b1000001000] = executeDataProcessingModifiedImmediate;
  Thumb32Table[0b1000001010] = executeDataProcessingModifiedImmediate;
  Thumb32Table[0b1000001100] = executeDataProcessingModifiedImmediate;
  Thumb32Table[0b1000001110] = executeDataProcessingModifiedImmediate;
  Thumb32Table[0b1000010000] = executeDataProcessingModifiedImmediate;
  Thumb32Table[0b1000010010] = executeDataProcessingModifiedImmediate;
  Thumb32Table[0b1000010100] = executeDataProcessingModifiedImmediate;
  Thumb32Table[0b1000010110] = executeDataProcessingModifiedImmediate;
  Thumb32Table[0b1000011000] = executeDataProcessingModifiedImmediate;
  Thumb32Table[0b1000011010] = executeDataProcessingModifiedImmediate;
  Thumb32Table[0b1000011100] = executeDataProcessingModifiedImmediate;
  Thumb32Table[0b1000011110] = executeDataProcessingModifiedImmediate;
  Thumb32Table[0b1000011110] = executeDataProcessingModifiedImmediate;
  Thumb32Table[0b1000100000] = executeDataProcessingModifiedImmediate;
  Thumb32Table[0b1000100010] = executeDataProcessingModifiedImmediate;
  Thumb32Table[0b1000100100] = executeDataProcessingModifiedImmediate;
  Thumb32Table[0b1000100110] = executeDataProcessingModifiedImmediate;
  Thumb32Table[0b1000101000] = executeDataProcessingModifiedImmediate;
  Thumb32Table[0b1000101010] = executeDataProcessingModifiedImmediate;
  Thumb32Table[0b1000101100] = executeDataProcessingModifiedImmediate;
  Thumb32Table[0b1000101110] = executeDataProcessingModifiedImmediate;
  Thumb32Table[0b1000110000] = executeDataProcessingModifiedImmediate;
  Thumb32Table[0b1000110010] = executeDataProcessingModifiedImmediate;
  Thumb32Table[0b1000110100] = executeDataProcessingModifiedImmediate;
  Thumb32Table[0b1000110110] = executeDataProcessingModifiedImmediate;
  Thumb32Table[0b1000111000] = executeDataProcessingModifiedImmediate;
  Thumb32Table[0b1000111010] = executeDataProcessingModifiedImmediate;
  Thumb32Table[0b1000111100] = executeDataProcessingModifiedImmediate;
  Thumb32Table[0b1000111110] = executeDataProcessingModifiedImmediate;
  Thumb32Table[0b1010000000] = executeDataProcessingModifiedImmediate;
  Thumb32Table[0b1010000010] = executeDataProcessingModifiedImmediate;
  Thumb32Table[0b1010000010] = executeDataProcessingModifiedImmediate;
  Thumb32Table[0b1010000100] = executeDataProcessingModifiedImmediate;
  Thumb32Table[0b1010000110] = executeDataProcessingModifiedImmediate;
  Thumb32Table[0b1010001000] = executeDataProcessingModifiedImmediate;
  Thumb32Table[0b1010001010] = executeDataProcessingModifiedImmediate;
  Thumb32Table[0b1010001100] = executeDataProcessingModifiedImmediate;
  Thumb32Table[0b1010001110] = executeDataProcessingModifiedImmediate;
  Thumb32Table[0b1010010000] = executeDataProcessingModifiedImmediate;
  Thumb32Table[0b1010010010] = executeDataProcessingModifiedImmediate;
  Thumb32Table[0b1010010100] = executeDataProcessingModifiedImmediate;
  Thumb32Table[0b1010010110] = executeDataProcessingModifiedImmediate;
  Thumb32Table[0b1010011000] = executeDataProcessingModifiedImmediate;
  Thumb32Table[0b1010011010] = executeDataProcessingModifiedImmediate;
  Thumb32Table[0b1010011100] = executeDataProcessingModifiedImmediate;
  Thumb32Table[0b1010011110] = executeDataProcessingModifiedImmediate;
  Thumb32Table[0b1010011110] = executeDataProcessingModifiedImmediate;
  Thumb32Table[0b1010100000] = executeDataProcessingModifiedImmediate;
  Thumb32Table[0b1010100010] = executeDataProcessingModifiedImmediate;
  Thumb32Table[0b1010100100] = executeDataProcessingModifiedImmediate;
  Thumb32Table[0b1010100110] = executeDataProcessingModifiedImmediate;
  Thumb32Table[0b1010101000] = executeDataProcessingModifiedImmediate;
  Thumb32Table[0b1010101010] = executeDataProcessingModifiedImmediate;
  Thumb32Table[0b1010101100] = executeDataProcessingModifiedImmediate;
  Thumb32Table[0b1010101110] = executeDataProcessingModifiedImmediate;
  Thumb32Table[0b1010110000] = executeDataProcessingModifiedImmediate;
  Thumb32Table[0b1010110010] = executeDataProcessingModifiedImmediate;
  Thumb32Table[0b1010110100] = executeDataProcessingModifiedImmediate;
  Thumb32Table[0b1010110110] = executeDataProcessingModifiedImmediate;
  Thumb32Table[0b1010111000] = executeDataProcessingModifiedImmediate;
  Thumb32Table[0b1010111010] = executeDataProcessingModifiedImmediate;
  Thumb32Table[0b1010111100] = executeDataProcessingModifiedImmediate;
  Thumb32Table[0b1010111110] = executeDataProcessingModifiedImmediate;
  //
  Thumb32Table[0b1001000000] = executeDataProcessingPlainImmediate;
  Thumb32Table[0b1001000010] = executeDataProcessingPlainImmediate;
  Thumb32Table[0b1001000010] = executeDataProcessingPlainImmediate;
  Thumb32Table[0b1001000100] = executeDataProcessingPlainImmediate;
  Thumb32Table[0b1001000110] = executeDataProcessingPlainImmediate;
  Thumb32Table[0b1001001000] = executeDataProcessingPlainImmediate;
  Thumb32Table[0b1001001010] = executeDataProcessingPlainImmediate;
  Thumb32Table[0b1001001100] = executeDataProcessingPlainImmediate;
  Thumb32Table[0b1001001110] = executeDataProcessingPlainImmediate;
  Thumb32Table[0b1001010000] = executeDataProcessingPlainImmediate;
  Thumb32Table[0b1001010010] = executeDataProcessingPlainImmediate;
  Thumb32Table[0b1001010100] = executeDataProcessingPlainImmediate;
  Thumb32Table[0b1001010110] = executeDataProcessingPlainImmediate;
  Thumb32Table[0b1001011000] = executeDataProcessingPlainImmediate;
  Thumb32Table[0b1001011010] = executeDataProcessingPlainImmediate;
  Thumb32Table[0b1001011100] = executeDataProcessingPlainImmediate;
  Thumb32Table[0b1001011110] = executeDataProcessingPlainImmediate;
  Thumb32Table[0b1001011110] = executeDataProcessingPlainImmediate;
  Thumb32Table[0b1001100000] = executeDataProcessingPlainImmediate;
  Thumb32Table[0b1001100010] = executeDataProcessingPlainImmediate;
  Thumb32Table[0b1001100100] = executeDataProcessingPlainImmediate;
  Thumb32Table[0b1001100110] = executeDataProcessingPlainImmediate;
  Thumb32Table[0b1001101000] = executeDataProcessingPlainImmediate;
  Thumb32Table[0b1001101010] = executeDataProcessingPlainImmediate;
  Thumb32Table[0b1001101100] = executeDataProcessingPlainImmediate;
  Thumb32Table[0b1001101110] = executeDataProcessingPlainImmediate;
  Thumb32Table[0b1001110000] = executeDataProcessingPlainImmediate;
  Thumb32Table[0b1001110010] = executeDataProcessingPlainImmediate;
  Thumb32Table[0b1001110100] = executeDataProcessingPlainImmediate;
  Thumb32Table[0b1001110110] = executeDataProcessingPlainImmediate;
  Thumb32Table[0b1001111000] = executeDataProcessingPlainImmediate;
  Thumb32Table[0b1001111010] = executeDataProcessingPlainImmediate;
  Thumb32Table[0b1001111100] = executeDataProcessingPlainImmediate;
  Thumb32Table[0b1001111110] = executeDataProcessingPlainImmediate;
  Thumb32Table[0b1011000000] = executeDataProcessingPlainImmediate;
  Thumb32Table[0b1011000010] = executeDataProcessingPlainImmediate;
  Thumb32Table[0b1011000010] = executeDataProcessingPlainImmediate;
  Thumb32Table[0b1011000100] = executeDataProcessingPlainImmediate;
  Thumb32Table[0b1011000110] = executeDataProcessingPlainImmediate;
  Thumb32Table[0b1011001000] = executeDataProcessingPlainImmediate;
  Thumb32Table[0b1011001010] = executeDataProcessingPlainImmediate;
  Thumb32Table[0b1011001100] = executeDataProcessingPlainImmediate;
  Thumb32Table[0b1011001110] = executeDataProcessingPlainImmediate;
  Thumb32Table[0b1011010000] = executeDataProcessingPlainImmediate;
  Thumb32Table[0b1011010010] = executeDataProcessingPlainImmediate;
  Thumb32Table[0b1011010100] = executeDataProcessingPlainImmediate;
  Thumb32Table[0b1011010110] = executeDataProcessingPlainImmediate;
  Thumb32Table[0b1011011000] = executeDataProcessingPlainImmediate;
  Thumb32Table[0b1011011010] = executeDataProcessingPlainImmediate;
  Thumb32Table[0b1011011100] = executeDataProcessingPlainImmediate;
  Thumb32Table[0b1011011110] = executeDataProcessingPlainImmediate;
  Thumb32Table[0b1011011110] = executeDataProcessingPlainImmediate;
  Thumb32Table[0b1011100000] = executeDataProcessingPlainImmediate;
  Thumb32Table[0b1011100010] = executeDataProcessingPlainImmediate;
  Thumb32Table[0b1011100100] = executeDataProcessingPlainImmediate;
  Thumb32Table[0b1011100110] = executeDataProcessingPlainImmediate;
  Thumb32Table[0b1011101000] = executeDataProcessingPlainImmediate;
  Thumb32Table[0b1011101010] = executeDataProcessingPlainImmediate;
  Thumb32Table[0b1011101100] = executeDataProcessingPlainImmediate;
  Thumb32Table[0b1011101110] = executeDataProcessingPlainImmediate;
  Thumb32Table[0b1011110000] = executeDataProcessingPlainImmediate;
  Thumb32Table[0b1011110010] = executeDataProcessingPlainImmediate;
  Thumb32Table[0b1011110100] = executeDataProcessingPlainImmediate;
  Thumb32Table[0b1011110110] = executeDataProcessingPlainImmediate;
  Thumb32Table[0b1011111000] = executeDataProcessingPlainImmediate;
  Thumb32Table[0b1011111010] = executeDataProcessingPlainImmediate;
  Thumb32Table[0b1011111100] = executeDataProcessingPlainImmediate;
  Thumb32Table[0b1011111110] = executeDataProcessingPlainImmediate;
  //
  Thumb32Table[0b0101000000] = executeDataProcessingShiftedRegister;
  Thumb32Table[0b0101000001] = executeDataProcessingShiftedRegister;
  Thumb32Table[0b0101000010] = executeDataProcessingShiftedRegister;
  Thumb32Table[0b0101000011] = executeDataProcessingShiftedRegister;
  Thumb32Table[0b0101000100] = executeDataProcessingShiftedRegister;
  Thumb32Table[0b0101000101] = executeDataProcessingShiftedRegister;
  Thumb32Table[0b0101000110] = executeDataProcessingShiftedRegister;
  Thumb32Table[0b0101000111] = executeDataProcessingShiftedRegister;
  Thumb32Table[0b0101001000] = executeDataProcessingShiftedRegister;
  Thumb32Table[0b0101001001] = executeDataProcessingShiftedRegister;
  Thumb32Table[0b0101001010] = executeDataProcessingShiftedRegister;
  Thumb32Table[0b0101001011] = executeDataProcessingShiftedRegister;
  Thumb32Table[0b0101001100] = executeDataProcessingShiftedRegister;
  Thumb32Table[0b0101001101] = executeDataProcessingShiftedRegister;
  Thumb32Table[0b0101001110] = executeDataProcessingShiftedRegister;
  Thumb32Table[0b0101001111] = executeDataProcessingShiftedRegister;
  Thumb32Table[0b0101010000] = executeDataProcessingShiftedRegister;
  Thumb32Table[0b0101010001] = executeDataProcessingShiftedRegister;
  Thumb32Table[0b0101010010] = executeDataProcessingShiftedRegister;
  Thumb32Table[0b0101010011] = executeDataProcessingShiftedRegister;
  Thumb32Table[0b0101010100] = executeDataProcessingShiftedRegister;
  Thumb32Table[0b0101010101] = executeDataProcessingShiftedRegister;
  Thumb32Table[0b0101010111] = executeDataProcessingShiftedRegister;
  Thumb32Table[0b0101011000] = executeDataProcessingShiftedRegister;
  Thumb32Table[0b0101011001] = executeDataProcessingShiftedRegister;
  Thumb32Table[0b0101011010] = executeDataProcessingShiftedRegister;
  Thumb32Table[0b0101011011] = executeDataProcessingShiftedRegister;
  Thumb32Table[0b0101011100] = executeDataProcessingShiftedRegister;
  Thumb32Table[0b0101011101] = executeDataProcessingShiftedRegister;
  Thumb32Table[0b0101011110] = executeDataProcessingShiftedRegister;
  Thumb32Table[0b0101011111] = executeDataProcessingShiftedRegister;
  Thumb32Table[0b0101100000] = executeDataProcessingShiftedRegister;
  Thumb32Table[0b0101100001] = executeDataProcessingShiftedRegister;
  Thumb32Table[0b0101100010] = executeDataProcessingShiftedRegister;
  Thumb32Table[0b0101100011] = executeDataProcessingShiftedRegister;
  Thumb32Table[0b0101100100] = executeDataProcessingShiftedRegister;
  Thumb32Table[0b0101100101] = executeDataProcessingShiftedRegister;
  Thumb32Table[0b0101100110] = executeDataProcessingShiftedRegister;
  Thumb32Table[0b0101100111] = executeDataProcessingShiftedRegister;
  Thumb32Table[0b0101101000] = executeDataProcessingShiftedRegister;
  Thumb32Table[0b0101101001] = executeDataProcessingShiftedRegister;
  Thumb32Table[0b0101101010] = executeDataProcessingShiftedRegister;
  Thumb32Table[0b0101101011] = executeDataProcessingShiftedRegister;
  Thumb32Table[0b0101101100] = executeDataProcessingShiftedRegister;
  Thumb32Table[0b0101101101] = executeDataProcessingShiftedRegister;
  Thumb32Table[0b0101101110] = executeDataProcessingShiftedRegister;
  Thumb32Table[0b0101101111] = executeDataProcessingShiftedRegister;
  Thumb32Table[0b0101110000] = executeDataProcessingShiftedRegister;
  Thumb32Table[0b0101110001] = executeDataProcessingShiftedRegister;
  Thumb32Table[0b0101110010] = executeDataProcessingShiftedRegister;
  Thumb32Table[0b0101110011] = executeDataProcessingShiftedRegister;
  Thumb32Table[0b0101110100] = executeDataProcessingShiftedRegister;
  Thumb32Table[0b0101110101] = executeDataProcessingShiftedRegister;
  Thumb32Table[0b0101110110] = executeDataProcessingShiftedRegister;
  Thumb32Table[0b0101110111] = executeDataProcessingShiftedRegister;
  Thumb32Table[0b0101111000] = executeDataProcessingShiftedRegister;
  Thumb32Table[0b0101111001] = executeDataProcessingShiftedRegister;
  Thumb32Table[0b0101111010] = executeDataProcessingShiftedRegister;
  Thumb32Table[0b0101111011] = executeDataProcessingShiftedRegister;
  Thumb32Table[0b0101111100] = executeDataProcessingShiftedRegister;
  Thumb32Table[0b0101111101] = executeDataProcessingShiftedRegister;
  Thumb32Table[0b0101111110] = executeDataProcessingShiftedRegister;
  Thumb32Table[0b0101111111] = executeDataProcessingShiftedRegister;
  //
  Thumb32Table[0b1100001010] = executeLoadWord;
  Thumb32Table[0b1100011010] = executeLoadWord;
  Thumb32Table[0b1100101010] = executeLoadWord;
  Thumb32Table[0b1100111010] = executeLoadWord;
  Thumb32Table[0b1100001011] = executeLoadWord;
  Thumb32Table[0b1100011011] = executeLoadWord;
  Thumb32Table[0b1100101011] = executeLoadWord;
  Thumb32Table[0b1100111011] = executeLoadWord;
  //
  Thumb32Table[0b1101100000] = executeMultiplyAccumulate;
  Thumb32Table[0b1101100001] = executeMultiplyAccumulate;
  Thumb32Table[0b1101100010] = executeMultiplyAccumulate;
  Thumb32Table[0b1101100011] = executeMultiplyAccumulate;
  Thumb32Table[0b1101100100] = executeMultiplyAccumulate;
  Thumb32Table[0b1101100101] = executeMultiplyAccumulate;
  Thumb32Table[0b1101100110] = executeMultiplyAccumulate;
  Thumb32Table[0b1101100111] = executeMultiplyAccumulate;
  Thumb32Table[0b1101101000] = executeMultiplyAccumulate;
  Thumb32Table[0b1101101001] = executeMultiplyAccumulate;
  Thumb32Table[0b1101101010] = executeMultiplyAccumulate;
  Thumb32Table[0b1101101011] = executeMultiplyAccumulate;
  Thumb32Table[0b1101101100] = executeMultiplyAccumulate;
  Thumb32Table[0b1101101101] = executeMultiplyAccumulate;
  Thumb32Table[0b1101101110] = executeMultiplyAccumulate;
  Thumb32Table[0b1101101111] = executeMultiplyAccumulate;

}




void initThumb32bitsDataProcessingShiftedRegister()
{
  Thumb32DataProcessingShiftedRegister[0b001111110000] = MVNRegisterT2;
  Thumb32DataProcessingShiftedRegister[0b001111110001] = MVNRegisterT2;
  Thumb32DataProcessingShiftedRegister[0b001111110010] = MVNRegisterT2;
  Thumb32DataProcessingShiftedRegister[0b001111110011] = MVNRegisterT2;
  Thumb32DataProcessingShiftedRegister[0b001111110100] = MVNRegisterT2;
  Thumb32DataProcessingShiftedRegister[0b001111110101] = MVNRegisterT2;
  Thumb32DataProcessingShiftedRegister[0b001111110110] = MVNRegisterT2;
  Thumb32DataProcessingShiftedRegister[0b001111110111] = MVNRegisterT2;
  Thumb32DataProcessingShiftedRegister[0b001111111000] = MVNRegisterT2;
  Thumb32DataProcessingShiftedRegister[0b001111111001] = MVNRegisterT2;
  Thumb32DataProcessingShiftedRegister[0b001111111010] = MVNRegisterT2;
  Thumb32DataProcessingShiftedRegister[0b001111111011] = MVNRegisterT2;
  Thumb32DataProcessingShiftedRegister[0b001111111100] = MVNRegisterT2;
  Thumb32DataProcessingShiftedRegister[0b001111111101] = MVNRegisterT2;
  Thumb32DataProcessingShiftedRegister[0b001111111110] = MVNRegisterT2;
  Thumb32DataProcessingShiftedRegister[0b001111111111] = MVNRegisterT2;
}


void initThumb32bitsDataProcessingPlainImmediate()
{
  // ADD Immediate T4 and ADR T3
  int i;

  for(i = 0b000000000; i < 0b000010000; i++)
  {
      if((i & 0b000001111) != 0b1111)
      {
        if((i & 0b000001101) != 0b1101)
          Thumb32DataProcessingPlainImmediate[i] = ADDImmediateT4;
      }
      else
        Thumb32DataProcessingPlainImmediate[i] = ADRT3;
  }
  // MOV Immediate T3
  for(i = 0b001000000; i < 0b001010000; i++)
    Thumb32DataProcessingPlainImmediate[i] = MOVImmediateT3;
  // SUB Immediate T4 and ADR T2
  for(i = 0b010100000; i < 0b010110000; i++)
  {
      if((i & 0b000001111) != 0b1111)
      {
        if((i & 0b000001101) != 0b1101)
          Thumb32DataProcessingPlainImmediate[i] = SUBImmediateT4;
      }
      else
        Thumb32DataProcessingPlainImmediate[i] = ADRT2;
  }
  //
  
}


void initThumb32bitsDataProcessingModifiedImmediate()
{
  // AND and TST Immediate T1
  int i;

  for(i = 0b0000000000000; i < 0b0001000000000; i++)
  {
      if((i & 0b0000000001111) != 0b1111)
          Thumb32DataProcessingModifiedImmediate[i] = ANDImmediateT1;
      else
      {
          if(i >= 0b0000100000000)      // S == 1 and Rd == 1111
              Thumb32DataProcessingModifiedImmediate[i] = TSTImmediateT1;
      }
  }
  // BIC Immediate T1
  for(i = 0b0001000000000; i < 0b0010000000000; i++)
    Thumb32DataProcessingModifiedImmediate[i] = BICImmediateT1;
  // ORR Immediate T1 and MOV Immediate T2
  for(i = 0b0010000000000; i < 0b0011000000000; i++)
  {
      if((i & 0b0000011110000) != 0b11110000)
          Thumb32DataProcessingModifiedImmediate[i] = ORRImmediateT1;
      else
          Thumb32DataProcessingModifiedImmediate[i] = MOVImmediateT2;
  }
  // ORN and MVN Immediate T1
  for(i = 0b0011000000000; i < 0b0100000000000; i++)
  {
      if((i & 0b0000011110000) != 0b11110000)
          Thumb32DataProcessingModifiedImmediate[i] = ORNImmediateT1;
      else
          Thumb32DataProcessingModifiedImmediate[i] = MVNImmediateT1;
  }
  // EOR and TEQ Immediate T1
  for(i = 0b0100000000000; i < 0b0101000000000; i++)
  {
      if((i & 0b0000000001111) != 0b1111)
          Thumb32DataProcessingModifiedImmediate[i] = EORImmediateT1;
      else
      {
          if(i >= 0b0100100000000)      // S == 1 and Rd == 1111
            Thumb32DataProcessingModifiedImmediate[i] = TEQImmediateT1;
      }
  }
  // ADD Immediate T3 and CMN Immediate T1
  for(i = 0b1000000000000; i < 0b1001000000000; i++)
  {
      if((i & 0b0000000001111) != 0b1111)
      {
          if((i & 0b0000011010000) != 0b11010000)    // Rd != 1111 and Rn != 1101
            Thumb32DataProcessingModifiedImmediate[i] = ADDImmediateT3;
      }
      else
      {
          if(i >= 0b1000100000000)      // S == 1 and Rd == 1111
            Thumb32DataProcessingModifiedImmediate[i] = CMNImmediateT1;
      }
  }
  // ADC Immediate T1
  for(i = 0b1010000000000; i < 0b1011000000000; i++)
    Thumb32DataProcessingModifiedImmediate[i] = ADCImmediateT1;
  // SBC Immediate T1
  for(i = 0b1011000000000; i < 0b1110000000000; i++)
    Thumb32DataProcessingModifiedImmediate[i] = SBCImmediateT1;
  // SUB Immediate T3 and CMP Immediate T1
  for(i = 0b1101000000000; i < 0b1110000000000; i++)
  {
      if((i & 0b0000000001111) != 0b1111)
      {
          if((i & 0b0000011010000) != 0b11010000)    // Rd != 1111 and Rn != 1101
            Thumb32DataProcessingModifiedImmediate[i] = SUBImmediateT3;
      }
      else
      {
          if(i >= 0b1101100000000)      // S == 1 and Rd == 1111
            Thumb32DataProcessingModifiedImmediate[i] = CMPImmediateT2;
      }
  }
  // RSB Immediate T2
  for(i = 0b1110000000000; i < 0b1111000000000; i++)
    Thumb32DataProcessingModifiedImmediate[i] = RSBImmediateT2;
}



void initThumb32bitsLoadWord()
{
  int i,j,k;
  uint32_t dummy;

  //LDRLiteral T2
  dummy = 0b000000001111;
  for(i = 0b0000000; i <= 0b1111111; i++)
  {
    dummy = setBits(dummy,i,10,4);
    Thumb32LoadWord[dummy] = LDRLiteralT2;
  }

  //LDRImmediate T3
  for(k = 0b000000; k <= 0b111111; k++)
  {
    dummy = setBits(dummy,k,9,4);
    for(j = 0; j < 0b1111; j ++)
    {
      dummy = setBits(dummy,j,3,0);
      Thumb32LoadWord[dummy] = LDRImmediateT3;
    }
  }


  //LDRImmediate T4
  dummy = 0b001001000000;
  for(k = 0; k < 4; k++)
  {
    dummy = setBits(dummy,k,8,7);
    for(i = 0; i < 4; i ++)
    {
      dummy = setBits(dummy, i, 5, 4);
      for(j = 0; j < 0b1111; j ++)
      {
        dummy = setBits(dummy,j,3,0);
        Thumb32LoadWord[dummy] = LDRImmediateT4;
      }
    }
  }

  dummy = 0b001100000000;
  for(i = 0; i < 4; i ++)
  {
    dummy = setBits(dummy, i, 5, 4);
    for(j = 0; j < 0b1111; j ++)
    {
      dummy = setBits(dummy,j,3,0);
      Thumb32LoadWord[dummy] = LDRImmediateT4;
    }
  }

  //LDR Register T2
  dummy = 0b000000000000;
  for(j = 0; j < 0b1111; j ++)
  {
    dummy = setBits(dummy,j,3,0);
    Thumb32LoadWord[dummy] = LDRRegisterT2;
  }

  //LDRT T1
  dummy = 0b001110000000;
  for(i = 0; i < 4; i ++)
  {
    dummy = setBits(dummy, i, 5, 4);
    for(j = 0; j < 0b1111; j ++)
    {
      dummy = setBits(dummy,j,3,0);
      Thumb32LoadWord[dummy] = LDRTT1;
    }
  }

}


void initThumb32bitsMultiplyAccumulate()
{
  int i,j,k;
  uint32_t dummy;

  //MLA T1
  dummy = 0b000000000;
  for(j = 0; j < 0b1111; j ++)
  {
    dummy = setBits(dummy,j,3,0);
    Thumb32MultiplyAccumulate[dummy] = MLAT1;
  }

  //MUL T2
  Thumb32MultiplyAccumulate[0b000001111] = MULRegisterT2;

  //MLS
  dummy = 0b000010000;
  for(j = 0; j <= 0b1111; j ++)
  {
    dummy = setBits(dummy,j,3,0);
    Thumb32MultiplyAccumulate[dummy] = MLST1;
  }
}


















