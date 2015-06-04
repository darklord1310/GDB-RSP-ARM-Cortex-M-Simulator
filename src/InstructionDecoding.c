#include "InstructionDecoding.h"
#include <stdio.h>


/*  This function will get the number of bits based on the range given by user from the instructions
 *  
 *  Input :     higherRange     is the higher limit of the stream of bits to be obtain
 *              lowerRange      is the lower limit of the stream of bits to be obtain
 *
 *  Return :    the stream of bits that obtain
 *
 *  Note:       It is possible also for this function to only get a single bit
 *              If the higherRange and lowerRange is the same
 *
 */
unsigned int getStreamOfBits(unsigned int instruction, int higherRange, int lowerRange)
{
    unsigned int StreamOfBits;
    unsigned int mask = setMask(higherRange);               //get the mask to mask off the bits before 
                                                            //the higher limit 
                                                            
    StreamOfBits = ( instruction & mask ) ;
    StreamOfBits = StreamOfBits >> lowerRange;
   
    return StreamOfBits;
    
}


/*	This will set the mask which is needed according to the bitPosition
 *  Eg. if bitPosition is 16
 *		XXXX	XXXX	XXXX	XXXX	XXXX	XXXX	XXXX    XXXX		---> this is a 32 bits integer
 *	                               ^      
 *                                 |      
 *                                16     
 *
 *  Then this function will provide the mask to mask off the bits before bit16 
 *  It will provide and return a mask of 0x0001FFFF
 *
 */
unsigned int setMask(int bitPosition)
{
	int i;
	unsigned int mask = 0x00;									//initialize the mask to be 0x00 first, then slowly
																//shift to left to the get the mask we wanted
																
	unsigned int timeToLoop = (31 - bitPosition) / 4;			//to determine how many times need to shift left, use
																//the MSB which is 31 minus the bitPosition and divide by 4
	
	for(i = 0; i < timeToLoop ; i++)
	{
		mask = (mask << 4) |  0x00;								//shift left and OR with 0 to create the mask
	}

	if( ( (31 - bitPosition) % 4) != 0)                         //to handle if the bitPosition+1 is multiple of 4
	{
		switch ( (31 - bitPosition) % 4 )
		{
			case 1 : mask = (mask << 4) | 0b0111;
                     break;
			case 2 : mask = (mask << 4) | 0x03;
                     break;
			case 3 : mask = (mask << 4) | 0b0001;
                     break;
		}
        
        timeToLoop = (bitPosition - 0) / 4;                     //determine how many times to shift left again to fill it with 0x0f

		for(i = 0; i < timeToLoop ; i++)
        {
            mask = (mask << 4) |  0x0f;							//shift left and OR with 0x0f to create the mask
        }
	}
    else
    {
        timeToLoop = (bitPosition + 1) / 4;                     //determine how many times to shift left again to fill it with 0x0f
        for(i = 0; i < timeToLoop ; i++)
        {
            mask = (mask << 4) |  0x0f;							//shift left and OR with 0x0f to create the mask
        }
    }
	return mask;
}



/*	This function is to check the instruction is 32 bits or 16 bits
 *
 *	hw1[15:11] 
 *				0b11100 Thumb 16-bit unconditional branch instruction, defined in all Thumb architectures.
 *				0bxxxxx Thumb 16-bit instructions.	
 *				0b111xx Thumb 32-bit instructions, defined in Thumb-2, see Instruction encoding for 32-bit		
 *
 * Return : bit_32 if 32 bits
 *			bit_16 if 16 bits
 *
 */
int is32or16instruction(unsigned int instruction)
{
	
	if( getStreamOfBits(instruction, 31, 29) == 0b111 )                 // if first 3 bits are 111, it is possible to be a 32bits instruction      
    {                                                                   // further checking is needed
		if( getStreamOfBits(instruction, 28, 27) == 0b00)                                       
			return bit_16;
		else
			return bit_32;
        
	}
    else
        return bit_16;
	
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



void Instruction_16bits(unsigned int instruction)
{
	
	
	
	
	
}



