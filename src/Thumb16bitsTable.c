#include "Thumb16bitsTable.h"

/*
000xx Logical Shift Left LSL (immediate) on page A6-134
001xx Logical Shift Right LSR (immediate) on page A6-138
010xx Arithmetic Shift Right ASR (immediate) on page A6-36
01100 Add register ADD (register) on page A6-24
01101 Subtract register SUB (register) on page A6-246
01110 Add 3-bit immediate ADD (immediate) on page A6-22
01111 Subtract 3-bit immediate SUB (immediate) on page A6-244
100xx Move MOV (immediate) on page A6-148
101xx Compare CMP (immediate) on page A6-62
110xx Add 8-bit immediate ADD (immediate) on page A6-22
111xx Subtract 8-bit immediate SUB (immediate) on page A6-244
*/
void initThumb16bitsOpcode00XXX()
{
  Thumb16Opcode00XXXX[0b00000] = LSLImmediateT1;
  Thumb16Opcode00XXXX[0b00001] = LSLImmediateT1;
  Thumb16Opcode00XXXX[0b00010] = LSLImmediateT1;
  Thumb16Opcode00XXXX[0b00011] = LSLImmediateT1;
  Thumb16Opcode00XXXX[0b00100] = LSRImmediateT1;
  Thumb16Opcode00XXXX[0b00101] = LSRImmediateT1;
  Thumb16Opcode00XXXX[0b00110] = LSRImmediateT1;
  Thumb16Opcode00XXXX[0b00111] = LSRImmediateT1;
  Thumb16Opcode00XXXX[0b01000] = ASRImmediateT1;
  Thumb16Opcode00XXXX[0b01001] = ASRImmediateT1;
  Thumb16Opcode00XXXX[0b01010] = ASRImmediateT1;
  Thumb16Opcode00XXXX[0b01011] = ASRImmediateT1;
  Thumb16Opcode00XXXX[0b01100] = ADDRegisterToRegisterT1;
  Thumb16Opcode00XXXX[0b01101] = SUBRegisterToRegisterT1;
  Thumb16Opcode00XXXX[0b01110] = ADDImmediateT1;
  Thumb16Opcode00XXXX[0b01111] = SUBImmediateT1;
  Thumb16Opcode00XXXX[0b10000] = MOVImmediateT1;
  Thumb16Opcode00XXXX[0b10001] = MOVImmediateT1;
  Thumb16Opcode00XXXX[0b10010] = MOVImmediateT1;
  Thumb16Opcode00XXXX[0b10011] = MOVImmediateT1;
  Thumb16Opcode00XXXX[0b10100] = CMPImmediateT1;
  Thumb16Opcode00XXXX[0b10101] = CMPImmediateT1;
  Thumb16Opcode00XXXX[0b10110] = CMPImmediateT1;
  Thumb16Opcode00XXXX[0b10111] = CMPImmediateT1;
  Thumb16Opcode00XXXX[0b11000] = ADDImmediateT2;
  Thumb16Opcode00XXXX[0b11001] = ADDImmediateT2;
  Thumb16Opcode00XXXX[0b11010] = ADDImmediateT2;
  Thumb16Opcode00XXXX[0b11011] = ADDImmediateT2;
  Thumb16Opcode00XXXX[0b11100] = SUBImmediateT2;
  Thumb16Opcode00XXXX[0b11101] = SUBImmediateT2;
  Thumb16Opcode00XXXX[0b11110] = SUBImmediateT2;
  Thumb16Opcode00XXXX[0b11111] = SUBImmediateT2;
}


void initThumb16bitsOpcode1011XX()
{
  Thumb16Opcode00XXXX[0b1111000] = ITandHints;
  Thumb16Opcode00XXXX[0b1111001] = ITandHints;
  Thumb16Opcode00XXXX[0b1111010] = ITandHints;
  Thumb16Opcode00XXXX[0b1111011] = ITandHints;
  Thumb16Opcode00XXXX[0b1111100] = ITandHints;
  Thumb16Opcode00XXXX[0b1111101] = ITandHints;
  Thumb16Opcode00XXXX[0b1111110] = ITandHints;
  Thumb16Opcode00XXXX[0b1111111] = ITandHints;
    
  
}