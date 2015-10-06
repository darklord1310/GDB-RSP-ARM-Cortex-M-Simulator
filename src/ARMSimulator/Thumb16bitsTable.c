/*  
    GDB RSP and ARM Simulator

    Copyright (C) 2015 Wong Yan Yin, <jet_wong@hotmail.com>,
    Jackson Teh Ka Sing, <jackson_dmc69@hotmail.com>

    This file is part of GDB RSP and ARM Simulator.

    This program is free software, you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY, without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with This program.  If not, see <http://www.gnu.org/licenses/>.
*/


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
  Thumb16Opcode1011XX[0b0000000] = ADDSPImmediateT2;
  Thumb16Opcode1011XX[0b0000001] = ADDSPImmediateT2;
  Thumb16Opcode1011XX[0b0000010] = ADDSPImmediateT2;
  Thumb16Opcode1011XX[0b0000011] = ADDSPImmediateT2;
  Thumb16Opcode1011XX[0b1010000] = REVT1;
  Thumb16Opcode1011XX[0b1010001] = REVT1;
  Thumb16Opcode1011XX[0b1010010] = REV16T1;
  Thumb16Opcode1011XX[0b1010011] = REV16T1;
  Thumb16Opcode1011XX[0b1010110] = REVSHT1;
  Thumb16Opcode1011XX[0b1010111] = REVSHT1;
  Thumb16Opcode1011XX[0b0010000] = SXTHT1;
  Thumb16Opcode1011XX[0b0010001] = SXTHT1;
  Thumb16Opcode1011XX[0b0010010] = SXTBT1;
  Thumb16Opcode1011XX[0b0010011] = SXTBT1;
  Thumb16Opcode1011XX[0b0010100] = UXTHT1;
  Thumb16Opcode1011XX[0b0010101] = UXTHT1;
  Thumb16Opcode1011XX[0b0010110] = UXTBT1;
  Thumb16Opcode1011XX[0b0010111] = UXTBT1;
  Thumb16Opcode1011XX[0b0001000] = CBNZorCBZ;
  Thumb16Opcode1011XX[0b0001001] = CBNZorCBZ;
  Thumb16Opcode1011XX[0b0001010] = CBNZorCBZ;
  Thumb16Opcode1011XX[0b0001011] = CBNZorCBZ;
  Thumb16Opcode1011XX[0b0001100] = CBNZorCBZ;
  Thumb16Opcode1011XX[0b0001101] = CBNZorCBZ;
  Thumb16Opcode1011XX[0b0001110] = CBNZorCBZ;
  Thumb16Opcode1011XX[0b0001111] = CBNZorCBZ;
  Thumb16Opcode1011XX[0b0011000] = CBNZorCBZ;
  Thumb16Opcode1011XX[0b0011000] = CBNZorCBZ;
  Thumb16Opcode1011XX[0b0011001] = CBNZorCBZ;
  Thumb16Opcode1011XX[0b0011010] = CBNZorCBZ;
  Thumb16Opcode1011XX[0b0011011] = CBNZorCBZ;
  Thumb16Opcode1011XX[0b0011100] = CBNZorCBZ;
  Thumb16Opcode1011XX[0b0011101] = CBNZorCBZ;
  Thumb16Opcode1011XX[0b0011110] = CBNZorCBZ;
  Thumb16Opcode1011XX[0b0011111] = CBNZorCBZ;
  Thumb16Opcode1011XX[0b1001000] = CBNZorCBZ;
  Thumb16Opcode1011XX[0b1001001] = CBNZorCBZ;
  Thumb16Opcode1011XX[0b1001010] = CBNZorCBZ;
  Thumb16Opcode1011XX[0b1001011] = CBNZorCBZ;
  Thumb16Opcode1011XX[0b1001100] = CBNZorCBZ;
  Thumb16Opcode1011XX[0b1001101] = CBNZorCBZ;
  Thumb16Opcode1011XX[0b1001110] = CBNZorCBZ;
  Thumb16Opcode1011XX[0b1001111] = CBNZorCBZ;
  Thumb16Opcode1011XX[0b1011000] = CBNZorCBZ;
  Thumb16Opcode1011XX[0b1011001] = CBNZorCBZ;
  Thumb16Opcode1011XX[0b1011010] = CBNZorCBZ;
  Thumb16Opcode1011XX[0b1011011] = CBNZorCBZ;
  Thumb16Opcode1011XX[0b1011100] = CBNZorCBZ;
  Thumb16Opcode1011XX[0b1011101] = CBNZorCBZ;
  Thumb16Opcode1011XX[0b1011110] = CBNZorCBZ;
  Thumb16Opcode1011XX[0b1011111] = CBNZorCBZ;
  Thumb16Opcode1011XX[0b0100000] = PUSHT1;
  Thumb16Opcode1011XX[0b0100001] = PUSHT1;
  Thumb16Opcode1011XX[0b0100010] = PUSHT1;
  Thumb16Opcode1011XX[0b0100011] = PUSHT1;
  Thumb16Opcode1011XX[0b0100100] = PUSHT1;
  Thumb16Opcode1011XX[0b0100101] = PUSHT1;
  Thumb16Opcode1011XX[0b0100110] = PUSHT1;
  Thumb16Opcode1011XX[0b0100111] = PUSHT1;
  Thumb16Opcode1011XX[0b0101000] = PUSHT1;
  Thumb16Opcode1011XX[0b0101001] = PUSHT1;
  Thumb16Opcode1011XX[0b0101010] = PUSHT1;
  Thumb16Opcode1011XX[0b0101011] = PUSHT1;
  Thumb16Opcode1011XX[0b0101100] = PUSHT1;
  Thumb16Opcode1011XX[0b0101101] = PUSHT1;
  Thumb16Opcode1011XX[0b0101110] = PUSHT1;
  Thumb16Opcode1011XX[0b0101111] = PUSHT1;
  Thumb16Opcode1011XX[0b1100000] = POPT1;
  Thumb16Opcode1011XX[0b1100001] = POPT1;
  Thumb16Opcode1011XX[0b1100010] = POPT1;
  Thumb16Opcode1011XX[0b1100011] = POPT1;
  Thumb16Opcode1011XX[0b1100100] = POPT1;
  Thumb16Opcode1011XX[0b1100101] = POPT1;
  Thumb16Opcode1011XX[0b1100110] = POPT1;
  Thumb16Opcode1011XX[0b1100111] = POPT1;
  Thumb16Opcode1011XX[0b1101000] = POPT1;
  Thumb16Opcode1011XX[0b1101001] = POPT1;
  Thumb16Opcode1011XX[0b1101010] = POPT1;
  Thumb16Opcode1011XX[0b1101011] = POPT1;
  Thumb16Opcode1011XX[0b1101100] = POPT1;
  Thumb16Opcode1011XX[0b1101101] = POPT1;
  Thumb16Opcode1011XX[0b1101110] = POPT1;
  Thumb16Opcode1011XX[0b1101111] = POPT1;
  Thumb16Opcode1011XX[0b0000100] = SUBSPImmediateT1;
  Thumb16Opcode1011XX[0b0000101] = SUBSPImmediateT1;
  Thumb16Opcode1011XX[0b0000110] = SUBSPImmediateT1;
  Thumb16Opcode1011XX[0b0000111] = SUBSPImmediateT1;
  Thumb16Opcode1011XX[0b1110000] = BKPT;
  Thumb16Opcode1011XX[0b1110001] = BKPT;
  Thumb16Opcode1011XX[0b1110010] = BKPT;
  Thumb16Opcode1011XX[0b1110011] = BKPT;
  Thumb16Opcode1011XX[0b1110100] = BKPT;
  Thumb16Opcode1011XX[0b1110101] = BKPT;
  Thumb16Opcode1011XX[0b1110110] = BKPT;
  Thumb16Opcode1011XX[0b1110111] = BKPT;
}



void initThumb16LoadStoreSingleData()
{
  Thumb16LoadStoreSingleData[0b0101000] = STRRegisterT1;
  Thumb16LoadStoreSingleData[0b0110100] = LDRImmediateT1;
  Thumb16LoadStoreSingleData[0b0110101] = LDRImmediateT1;
  Thumb16LoadStoreSingleData[0b0110110] = LDRImmediateT1;
  Thumb16LoadStoreSingleData[0b0110111] = LDRImmediateT1;
  Thumb16LoadStoreSingleData[0b0111100] = LDRBImmediateT1;
  Thumb16LoadStoreSingleData[0b0111101] = LDRBImmediateT1;
  Thumb16LoadStoreSingleData[0b0111110] = LDRBImmediateT1;
  Thumb16LoadStoreSingleData[0b0111111] = LDRBImmediateT1;
  Thumb16LoadStoreSingleData[0b1000100] = LDRHImmediateT1;
  Thumb16LoadStoreSingleData[0b1000101] = LDRHImmediateT1;
  Thumb16LoadStoreSingleData[0b1000110] = LDRHImmediateT1;
  Thumb16LoadStoreSingleData[0b1000111] = LDRHImmediateT1;
  Thumb16LoadStoreSingleData[0b0110000] = STRImmediateT1;
  Thumb16LoadStoreSingleData[0b0110001] = STRImmediateT1;
  Thumb16LoadStoreSingleData[0b0110010] = STRImmediateT1;
  Thumb16LoadStoreSingleData[0b0110011] = STRImmediateT1;
  Thumb16LoadStoreSingleData[0b0111000] = STRBImmediateT1;
  Thumb16LoadStoreSingleData[0b0111001] = STRBImmediateT1;
  Thumb16LoadStoreSingleData[0b0111010] = STRBImmediateT1;
  Thumb16LoadStoreSingleData[0b0111011] = STRBImmediateT1;
  Thumb16LoadStoreSingleData[0b1000000] = STRHImmediateT1;
  Thumb16LoadStoreSingleData[0b1000001] = STRHImmediateT1;
  Thumb16LoadStoreSingleData[0b1000010] = STRHImmediateT1;
  Thumb16LoadStoreSingleData[0b1000011] = STRHImmediateT1;
  Thumb16LoadStoreSingleData[0b1001100] = LDRImmediateT2;
  Thumb16LoadStoreSingleData[0b1001101] = LDRImmediateT2;
  Thumb16LoadStoreSingleData[0b1001110] = LDRImmediateT2;
  Thumb16LoadStoreSingleData[0b1001111] = LDRImmediateT2;
  Thumb16LoadStoreSingleData[0b1001000] = STRImmediateT2;  
  Thumb16LoadStoreSingleData[0b1001001] = STRImmediateT2; 
  Thumb16LoadStoreSingleData[0b1001010] = STRImmediateT2; 
  Thumb16LoadStoreSingleData[0b1001011] = STRImmediateT2; 
  Thumb16LoadStoreSingleData[0b0101001] = STRHRegisterT1;
  Thumb16LoadStoreSingleData[0b0101010] = STRBRegisterT1; 
  Thumb16LoadStoreSingleData[0b0101100] = LDRRegisterT1; 
  Thumb16LoadStoreSingleData[0b0101011] = LDRSBRegisterT1;
  Thumb16LoadStoreSingleData[0b0101101] = LDRHRegisterT1;
  Thumb16LoadStoreSingleData[0b0101110] = LDRBRegisterT1;
  Thumb16LoadStoreSingleData[0b0101111] = LDRSHRegisterT1;
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
  Thumb16Opcode1101XX[0b1111] = SVC;
}



