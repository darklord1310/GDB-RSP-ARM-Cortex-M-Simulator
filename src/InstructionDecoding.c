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
unsigned int getBits(unsigned int instruction, int higherRange, int lowerRange)
{
    unsigned int StreamOfBits;
    unsigned int mask = getMask(higherRange);               //get the mask to mask off the bits before 
                                                            //the higher limit 

    StreamOfBits = ( instruction & mask ) ;
    StreamOfBits = StreamOfBits >> lowerRange;
   
    return StreamOfBits;
    
}




/*  This function is to check the instruction is 32 bits or 16 bits
 *
 *  hw1[15:11] 
 *        0b11100 Thumb 16-bit unconditional branch instruction, defined in all Thumb architectures.
 *        0bxxxxx Thumb 16-bit instructions.	
 *        0b111xx Thumb 32-bit instructions, defined in Thumb-2, see Instruction encoding for 32-bit		
 *
 *  Return : bit_32 if 32 bits
 *           bit_16 if 16 bits
 *
 */
int is32or16instruction(unsigned int instruction)
{
	
  if( getBits(instruction, 31, 29) == 0b111 )                 // if first 3 bits are 111, it is possible to be a 32bits instruction      
  {                                                                   // further checking is needed
    if( getBits(instruction, 28, 27) == 0b00)                                       
      return INSTRUCTION16bits;
    else
      return INSTRUCTION32bits;  
	}
  else
      return INSTRUCTION16bits;
}


/*
void Instruction_32bits(unsigned int instruction)
{
  unsigned int opcode1 = getBits(instruction, 28, 27);
	
  switch(opcode1)
  {
    case 0b01 : MOV_IMMEDIATE(instruction);
                break;
    case 0b10 : MOV_RegisterToRegister(instruction);
                break;
    case 0b11 : MOV_RegisterToRegister(instruction);
                break;
  }
}
*/



void Instruction_16bits(unsigned int instruction)
{
	
	
	
	
	
}



