#include "InstructionDecoding.h"
#include <stdio.h>


/*  This function is to check the instruction is 32 bits or 16 bits
 *
 *  hw1[15:11] 
 *        0b11100 Thumb 16-bit unconditional branch instruction, defined in all Thumb architectures.
 *        0bxxxxx Thumb 16-bit instructions.	
 *        0b111xx Thumb 32-bit instructions, defined in Thumb-2, see Instruction encoding for 32-bit		
 *
 *  Return : INSTRUCTION32bits if 32 bits
 *           INSTRUCTION16bits if 16 bits
 *
 */
int is32or16instruction(unsigned int instruction)
{
	
  if( getBits(instruction, 31, 29) == 0b111 )                 // if first 3 bits are 111, it is possible to be a 32bits instruction      
  {                                                           // further checking is needed
    if( getBits(instruction, 28, 27) == 0b00)                                       
      return INSTRUCTION16bits;
    else
      return INSTRUCTION32bits;  
	}
  else
      return INSTRUCTION16bits;
}









