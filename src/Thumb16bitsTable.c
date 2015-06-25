#include "Thumb16bitsTable.h"

void initThumb16bitsTable()
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