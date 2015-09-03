#include "Thumb32bitsTable.h"




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
  //00100XXXX
  Thumb32DataProcessingPlainImmediate[0b001000000] = MOVImmediateT3;
  Thumb32DataProcessingPlainImmediate[0b001000001] = MOVImmediateT3;
  Thumb32DataProcessingPlainImmediate[0b001000010] = MOVImmediateT3;
  Thumb32DataProcessingPlainImmediate[0b001000011] = MOVImmediateT3;
  Thumb32DataProcessingPlainImmediate[0b001000100] = MOVImmediateT3;
  Thumb32DataProcessingPlainImmediate[0b001000101] = MOVImmediateT3;
  Thumb32DataProcessingPlainImmediate[0b001000110] = MOVImmediateT3;
  Thumb32DataProcessingPlainImmediate[0b001000111] = MOVImmediateT3;
  Thumb32DataProcessingPlainImmediate[0b001001000] = MOVImmediateT3;
  Thumb32DataProcessingPlainImmediate[0b001001001] = MOVImmediateT3;
  Thumb32DataProcessingPlainImmediate[0b001001010] = MOVImmediateT3;
  Thumb32DataProcessingPlainImmediate[0b001001011] = MOVImmediateT3;
  Thumb32DataProcessingPlainImmediate[0b001001100] = MOVImmediateT3;
  Thumb32DataProcessingPlainImmediate[0b001001101] = MOVImmediateT3;
  Thumb32DataProcessingPlainImmediate[0b001001110] = MOVImmediateT3;
  Thumb32DataProcessingPlainImmediate[0b001001111] = MOVImmediateT3;


}


void initThumb32bitsDataProcessingModifiedImmediate()
{
  Thumb32DataProcessingModifiedImmediate[0b0010011110000] = MOVImmediateT2;
  Thumb32DataProcessingModifiedImmediate[0b0010011110001] = MOVImmediateT2;
  Thumb32DataProcessingModifiedImmediate[0b0010011110010] = MOVImmediateT2;
  Thumb32DataProcessingModifiedImmediate[0b0010011110011] = MOVImmediateT2;
  Thumb32DataProcessingModifiedImmediate[0b0010011110100] = MOVImmediateT2;
  Thumb32DataProcessingModifiedImmediate[0b0010011110101] = MOVImmediateT2;
  Thumb32DataProcessingModifiedImmediate[0b0010011110110] = MOVImmediateT2;
  Thumb32DataProcessingModifiedImmediate[0b0010011110111] = MOVImmediateT2;
  Thumb32DataProcessingModifiedImmediate[0b0010011111000] = MOVImmediateT2;
  Thumb32DataProcessingModifiedImmediate[0b0010011111001] = MOVImmediateT2;
  Thumb32DataProcessingModifiedImmediate[0b0010011111010] = MOVImmediateT2;
  Thumb32DataProcessingModifiedImmediate[0b0010011111011] = MOVImmediateT2;
  Thumb32DataProcessingModifiedImmediate[0b0010011111100] = MOVImmediateT2;
  Thumb32DataProcessingModifiedImmediate[0b0010011111101] = MOVImmediateT2;
  Thumb32DataProcessingModifiedImmediate[0b0010011111110] = MOVImmediateT2;
  Thumb32DataProcessingModifiedImmediate[0b0010011111111] = MOVImmediateT2;
  Thumb32DataProcessingModifiedImmediate[0b0010111110000] = MOVImmediateT2;
  Thumb32DataProcessingModifiedImmediate[0b0010111110001] = MOVImmediateT2;
  Thumb32DataProcessingModifiedImmediate[0b0010111110010] = MOVImmediateT2;
  Thumb32DataProcessingModifiedImmediate[0b0010111110011] = MOVImmediateT2;
  Thumb32DataProcessingModifiedImmediate[0b0010111110100] = MOVImmediateT2;
  Thumb32DataProcessingModifiedImmediate[0b0010111110101] = MOVImmediateT2;
  Thumb32DataProcessingModifiedImmediate[0b0010111110110] = MOVImmediateT2;
  Thumb32DataProcessingModifiedImmediate[0b0010111110111] = MOVImmediateT2;
  Thumb32DataProcessingModifiedImmediate[0b0010111111000] = MOVImmediateT2;
  Thumb32DataProcessingModifiedImmediate[0b0010111111001] = MOVImmediateT2;
  Thumb32DataProcessingModifiedImmediate[0b0010111111010] = MOVImmediateT2;
  Thumb32DataProcessingModifiedImmediate[0b0010111111011] = MOVImmediateT2;
  Thumb32DataProcessingModifiedImmediate[0b0010111111100] = MOVImmediateT2;
  Thumb32DataProcessingModifiedImmediate[0b0010111111101] = MOVImmediateT2;
  Thumb32DataProcessingModifiedImmediate[0b0010111111110] = MOVImmediateT2;
  Thumb32DataProcessingModifiedImmediate[0b0010111111111] = MOVImmediateT2;
  //
  
  int i;

  for(i = 0b0000000000000; i < 0b0001000000000; i++)
  {
      if((i & 0b0000000001111) != 0b1111)
          Thumb32DataProcessingModifiedImmediate[i] = ANDImmediateT1;
      else
      {
          if(i >= 0b0000100000000)
              Thumb32DataProcessingModifiedImmediate[i] = TSTImmediateT1;
      }
  }
  
  //
  
  for(i = 0b0001000000000; i < 0b0010000000000; i++)
    Thumb32DataProcessingModifiedImmediate[i] = BICImmediateT1;

  //
  
  
}
