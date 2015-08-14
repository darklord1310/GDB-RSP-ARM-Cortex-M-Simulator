#include "Thumb32bitsTable.h"






void initThumb32Table()
{
  Thumb32Table[0b1000000000] = Thumb32DataProcessingModifiedImmediate;
  Thumb32Table[0b1010001010] = Thumb32DataProcessingModifiedImmediate;
  Thumb32Table[0b1000000010] = Thumb32DataProcessingModifiedImmediate;
  Thumb32Table[0b1000000010] = Thumb32DataProcessingModifiedImmediate;
  Thumb32Table[0b1000000100] = Thumb32DataProcessingModifiedImmediate;
  Thumb32Table[0b1000000110] = Thumb32DataProcessingModifiedImmediate;
  Thumb32Table[0b1000001000] = Thumb32DataProcessingModifiedImmediate;
  Thumb32Table[0b1000001010] = Thumb32DataProcessingModifiedImmediate;
  Thumb32Table[0b1000001100] = Thumb32DataProcessingModifiedImmediate;
  Thumb32Table[0b1000001110] = Thumb32DataProcessingModifiedImmediate;
  Thumb32Table[0b1000010000] = Thumb32DataProcessingModifiedImmediate;
  Thumb32Table[0b1000010010] = Thumb32DataProcessingModifiedImmediate;
  Thumb32Table[0b1000010100] = Thumb32DataProcessingModifiedImmediate;
  Thumb32Table[0b1000010110] = Thumb32DataProcessingModifiedImmediate;
  Thumb32Table[0b1000011000] = Thumb32DataProcessingModifiedImmediate;
  Thumb32Table[0b1000011010] = Thumb32DataProcessingModifiedImmediate;
  Thumb32Table[0b1000011100] = Thumb32DataProcessingModifiedImmediate;
  Thumb32Table[0b1000011110] = Thumb32DataProcessingModifiedImmediate;
  Thumb32Table[0b1000011110] = Thumb32DataProcessingModifiedImmediate;
  Thumb32Table[0b1000100000] = Thumb32DataProcessingModifiedImmediate;
  Thumb32Table[0b1000100010] = Thumb32DataProcessingModifiedImmediate;
  Thumb32Table[0b1000100100] = Thumb32DataProcessingModifiedImmediate;
  Thumb32Table[0b1000100110] = Thumb32DataProcessingModifiedImmediate;
  Thumb32Table[0b1000101000] = Thumb32DataProcessingModifiedImmediate;
  Thumb32Table[0b1000101010] = Thumb32DataProcessingModifiedImmediate;
  Thumb32Table[0b1000101100] = Thumb32DataProcessingModifiedImmediate;
  Thumb32Table[0b1000101110] = Thumb32DataProcessingModifiedImmediate;
  Thumb32Table[0b1000110000] = Thumb32DataProcessingModifiedImmediate;
  Thumb32Table[0b1000110010] = Thumb32DataProcessingModifiedImmediate;
  Thumb32Table[0b1000110100] = Thumb32DataProcessingModifiedImmediate;
  Thumb32Table[0b1000110110] = Thumb32DataProcessingModifiedImmediate;
  Thumb32Table[0b1000111000] = Thumb32DataProcessingModifiedImmediate;
  Thumb32Table[0b1000111010] = Thumb32DataProcessingModifiedImmediate;
  Thumb32Table[0b1000111100] = Thumb32DataProcessingModifiedImmediate;
  Thumb32Table[0b1000111110] = Thumb32DataProcessingModifiedImmediate;
  //Thumb32Table[0b1000xxxxx0] = Thumb32DataProcessingModifiedImmediate;
  //Thumb32Table[0b10x0xxxxx0] = Thumb32DataProcessingModifiedImmediate;
  //10x0xxxxx0
  /*
  xxxxx

  
  
  
  

  */
}


void initThumb32bitsDataProcessingShiftedRegister()
{
    
  
}




/*
  AND (immediate) on page A6-32
  1111 Test TST (immediate) on page A6-262
  0001x Bitwise Clear BIC (immediate) on page A6-44
  0010x not 1111 Bitwise Inclusive OR ORR (immediate) on page A6-172
  1111 Move MOV (immediate) on page A6-148
  0011x not 1111 Bitwise OR NOT ORN (immediate) on page A6-168
  1111 Bitwise NOT MVN (immediate) on page A6-162
  0100x not 1111 Bitwise Exclusive OR EOR (immediate) on page A6-72
  1111 Test Equivalence TEQ (immediate) on page A6-260
  1000x not 1111 Add ADD (immediate) on page A6-22
  1111 Compare Negative CMN (immediate) on page A6-58
  1010x Add with Carry ADC (immediate) on page A6-18
  1011x Subtract with Carry SBC (immediate) on page A6-204
  1101x not 1111 Subtract SUB (immediate) on page A6-244
  1111 Compare CMP (immediate) on page A6-62
  1110x Reverse Subtract RSB (immediate) on page A6-200
*/
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
  
}
