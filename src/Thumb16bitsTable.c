#include "Thumb16bitsTable.h"


/*
000xx     Logical Shift Left LSL (immediate) on page A6-134

001xx     Logical Shift Right LSR (immediate) on page A6-138

010xx     Arithmetic Shift Right ASR (immediate) on page A6-36

01100     Add register ADD (register) on page A6-24

01101     Subtract register SUB (register) on page A6-246

01110     Add 3-bit immediate ADD (immediate) on page A6-22

01111     Subtract 3-bit immediate SUB (immediate) on page A6-244

100xx     Move MOV (immediate) on page A6-148

101xx     Compare CMP (immediate) on page A6-62

110xx     Add 8-bit immediate ADD (immediate) on page A6-22

111xx     Subtract 8-bit immediate SUB (immediate) on page A6-244
*/
void initThumb16bitsOpcode00XXXX()
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




/*
0000          Bitwise AND AND (register) on page A6-34

0001          Exclusive OR EOR (register) on page A6-74

0010          Logical Shift Left LSL (register) on page A6-136

0011          Logical Shift Right LSR (register) on page A6-140

0100          Arithmetic Shift Right ASR (register) on page A6-38

0101          Add with Carry ADC (register) on page A6-20

0110          Subtract with Carry SBC (register) on page A6-206

0111          Rotate Right ROR (register) on page A6-196

1000          Set flags on bitwise AND TST (register) on page A6-264

1001          Reverse Subtract from 0 RSB (immediate) on page A6-200

1010          Compare Registers CMP (register) on page A6-64

1011          Compare Negative CMN (register) on page A6-60

1100          Logical OR ORR (register) on page A6-174

1101          Multiply Two Registers MUL on page A6-160

1110          Bit Clear BIC (register) on page A6-46

1111          Bitwise NOT MVN (register) on page A6-164
*/
void initThumb16bitsOpcode010000()
{
  Thumb16Opcode010000[0b0000] = ANDRegisterT1;
  Thumb16Opcode010000[0b0001] = EORRegisterT1;
  Thumb16Opcode010000[0b0010] = LSLRegisterToRegisterT1;
  Thumb16Opcode010000[0b0011] = LSRRegisterToRegisterT1;
  Thumb16Opcode010000[0b0100] = ASRRegisterToRegisterT1; 
  Thumb16Opcode010000[0b1010] = CMPRegisterT1;
  Thumb16Opcode010000[0b1011] = CMNRegisterT1;
  Thumb16Opcode010000[0b0111] = RORRegisterT1;
  Thumb16Opcode010000[0b1100] = ORRRegisterT1;
  Thumb16Opcode010000[0b1110] = BICRegisterT1;
  Thumb16Opcode010000[0b1111] = MVNRegisterT1;
  Thumb16Opcode010000[0b0101] = ADCRegisterT1;
  Thumb16Opcode010000[0b1101] = MULRegisterT1;
  Thumb16Opcode010000[0b1000] = TSTRegisterT1;
  Thumb16Opcode010000[0b1001] = RSBImmediateT1;
  Thumb16Opcode010000[0b0110] = SBCRegisterT1;
}




/*
00xx      Add Registers ADD (register) on page A6-24

0100      UNPREDICTABLE

0101      Compare Registers CMP (register) on page A6-64
011x

10xx      Move Registers MOV (register) on page A6-150

110x      Branch and Exchange BX on page A6-51

111x      Branch with Link and Exchange BLX (register) on page A6-50
*/
void initThumb16bitsOpcode010001()
{
  Thumb16Opcode010001[0b0000] = ADDRegisterToRegisterT2;
  Thumb16Opcode010001[0b0001] = ADDRegisterToRegisterT2;
  Thumb16Opcode010001[0b0010] = ADDRegisterToRegisterT2;
  Thumb16Opcode010001[0b0011] = ADDRegisterToRegisterT2;
  Thumb16Opcode010001[0b0101] = CMPRegisterT2;
  Thumb16Opcode010001[0b0110] = CMPRegisterT2;
  Thumb16Opcode010001[0b0111] = CMPRegisterT2;
  Thumb16Opcode010001[0b1100] = BX;
  Thumb16Opcode010001[0b1101] = BX;
  Thumb16Opcode010001[0b1110] = BLXRegister;
  Thumb16Opcode010001[0b1111] = BLXRegister;
  Thumb16Opcode010001[0b1000] = MOVRegisterToRegisterT1;
  Thumb16Opcode010001[0b1001] = MOVRegisterToRegisterT1;
  Thumb16Opcode010001[0b1010] = MOVRegisterToRegisterT1;
  Thumb16Opcode010001[0b1011] = MOVRegisterToRegisterT1;

  
}


void initThumb16bitsOpcode1011XX()
{
  Thumb16Opcode1011XX[0b1111000] = ITandHints;
  Thumb16Opcode1011XX[0b1111001] = ITandHints;
  Thumb16Opcode1011XX[0b1111010] = ITandHints;
  Thumb16Opcode1011XX[0b1111011] = ITandHints;
  Thumb16Opcode1011XX[0b1111100] = ITandHints;
  Thumb16Opcode1011XX[0b1111101] = ITandHints;
  Thumb16Opcode1011XX[0b1111110] = ITandHints;
  Thumb16Opcode1011XX[0b1111111] = ITandHints;
    
  
}



void initThumb16LoadStoreSingleData()
{
  Thumb16LoadStoreSingleData[0b0101000] = STRRegisterT1;
  Thumb16LoadStoreSingleData[0b0110100] = LDRImmediateT1;
  Thumb16LoadStoreSingleData[0b0110101] = LDRImmediateT1;
  Thumb16LoadStoreSingleData[0b0110110] = LDRImmediateT1;
  Thumb16LoadStoreSingleData[0b0110111] = LDRImmediateT1;

}

/*
    not 111x        Conditional branch B on page A6-40
    1110            Permanently UNDEFINED
    1111            Supervisor call SVC (formerly SWI) on page A6-252
*/
void initThumb16bitsOpcode1101XX()
{
  Thumb16Opcode1101XX[0b0000] = ConditionalBranchT1;
  Thumb16Opcode1101XX[0b0001] = ConditionalBranchT1;
  Thumb16Opcode1101XX[0b0010] = ConditionalBranchT1;
  Thumb16Opcode1101XX[0b0011] = ConditionalBranchT1;
  Thumb16Opcode1101XX[0b0100] = ConditionalBranchT1;
  Thumb16Opcode1101XX[0b0101] = ConditionalBranchT1;
  Thumb16Opcode1101XX[0b0110] = ConditionalBranchT1;
  Thumb16Opcode1101XX[0b0111] = ConditionalBranchT1;
  Thumb16Opcode1101XX[0b1000] = ConditionalBranchT1;
  Thumb16Opcode1101XX[0b1001] = ConditionalBranchT1;
  Thumb16Opcode1101XX[0b1010] = ConditionalBranchT1;
  Thumb16Opcode1101XX[0b1011] = ConditionalBranchT1;
  Thumb16Opcode1101XX[0b1100] = ConditionalBranchT1;
  Thumb16Opcode1101XX[0b1101] = ConditionalBranchT1;
  
}