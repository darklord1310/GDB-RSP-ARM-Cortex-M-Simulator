#include "InstructionDecoding.h"
#include <stdio.h>

void Instruction_16bits(unsigned int instruction)
{
	
	
	
	
	
}

/*
void Instruction_32bits(unsigned int instruction)
{
	unsigned int opcode1 = getFirst5BitsFromInstruction(instruction);
	
	switch(opcode1)
	{
		case 0b11110 : MOV_IMMEDIATE(instruction);
		case 0b11101 : MOV_RegisterToRegister(instruction);
	}
	
	
	
	
	
}
*/




/*	This function is to check the instruction is 32 bits or 16 bits
 *
 *	hw1[15:11] 
 *				0b11100 Thumb 16-bit unconditional branch instruction, defined in all Thumb architectures.
 *				0bxxxxx Thumb 16-bit instructions.	
 *				0b111xx Thumb 32-bit instructions, defined in Thumb-2, see Instruction encoding for 32-bit		
 *
 * Return : 0 if 32 bits
 *			1 if 16 bits
 *
 */
int is32or16instruction(unsigned int instruction)
{
	unsigned int firstFewBits;
	
	firstFewBits = getFirstFewBitsFromInstruction(instruction, 5);

	if(firstFewBits == 0b11100)											// if first 5 bits are 11100, then confirm is 16bits instruction
		return bit_16;
	else
	{
		firstFewBits = getFirstFewBitsFromInstruction(instruction, 3);	
		if( firstFewBits == 0b111)
			return bit_32;
		else
			return bit_16;
	}
	
	
}



/*	This function is responsible to get the first few bits from instruction, this will help to 
 *	categorize the instructions 
 *
 *	How many bits to get can be control by the user
 * 
 *
 *	Input  : noOfbits		the number of bits to get 
 *			 instruction	is the ARM instruction
 *
 *  Return : the first few bits get
 *			 
 *
 */
unsigned int getFirstFewBitsFromInstruction(unsigned int instruction, int noOfbits)
{
	unsigned int firstFewbits;
	
	switch(noOfbits)
	{
		case 3:	firstFewbits = getFirst3BitsFromInstruction(instruction);
				break;
		
		case 4:	firstFewbits = getFirst4BitsFromInstruction(instruction);
				break;
				
		case 5:	firstFewbits = getFirst5BitsFromInstruction(instruction);
				break;
				
		case 6:	firstFewbits = getFirst6BitsFromInstruction(instruction);
				break;
		
	}
	
	return firstFewbits;	
}



unsigned int getFirst3BitsFromInstruction(unsigned int instruction)
{
	unsigned int first3bits;
	unsigned int maskToClear = 0xE0000000;				//provide the mask to retain only the bit from 29 to 0
														//other bits are set to be 0

	first3bits = instruction & maskToClear;	
	first3bits = instruction >> 29;						//shift left 29 times until bit 29 is now bit 0
	
	return first3bits;
}
	
	
	
unsigned int getFirst4BitsFromInstruction(unsigned int instruction)
{
	unsigned int first4bits;
	unsigned int maskToClear = 0xF0000000;				//provide the mask to retain only the bit from 28 to 0
														//other bits are set to be 0

	first4bits = instruction & maskToClear;	
	first4bits = instruction >> 28;						//shift left 28 times until bit 28 is now bit 0
	
	return first4bits;
	
}


unsigned int getFirst5BitsFromInstruction(unsigned int instruction)
{
	unsigned int first5bits;
	unsigned int maskToClear = 0xF8000000;				//provide the mask to retain only the bit from 27 to 0
														//other bits are set to be 0

	first5bits = instruction & maskToClear;	
	first5bits = instruction >> 27;						//shift left 27 times until bit 27 is now bit 0
	
	return first5bits;

}


unsigned int getFirst6BitsFromInstruction(unsigned int instruction)
{
	unsigned int first6bits;
	unsigned int maskToClear = 0xFC000000;				//provide the mask to retain only the bit from 26 to 0
														//other bits are set to be 0

	first6bits = instruction & maskToClear;	
	first6bits = instruction >> 26;						//shift left 26 times until bit 26 is now bit 0
	
	return first6bits;
	
}
