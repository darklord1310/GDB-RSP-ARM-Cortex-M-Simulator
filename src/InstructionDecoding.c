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



/*  This function will categorize all the 16bits Thumb Instructions
 *  15  14  13  12  11  10  9   8   7   6   5   4   3   2   1   0
 *  |   |   |           | 
 *   op1        op2
 *
 *  Check opcode 1 first, then branch out to check opcode 2
 *
 *  opcode 1
 *    00    ------->  000 --->  LSL(immediate)
 *          |______>  001 --->  LSR(immediate)
 *          |______>  010 --->  ASR(immediate)
 *          |______>  011 --->  Add or Subtract (register/immediate) -----> 00 ---> Add (register)
 *                                                                  |_____> 01 ---> Subtract (register)
 *                                                                  |_____> 10 ---> Add (3 bit immediate)   
 *                                                                  |_____> 11 ---> Subtract (3 bit immediate)   
 *
 *
 *
 *
 *
 *    01
 *
 *
 *    10
 *
 *
 *    11
 *
 */
void Categorize16bitsThumbInstruction(unsigned int instruction)
{
  unsigned int opcode1 = getBits(instruction, 31, 30);
	
  switch(opcode1)
  {
    case 0b00 : OP1IS00(instruction);      //shift(immediate), add, subtract, move, and compare
                break;
    case 0b01 : OP1IS01(instruction); //data processing, special data instructions and branch and exchange, load from literal pool, load/store data
                break;
    case 0b10 : OP1IS10(instruction);
                break;
    case 0b11 : OP1IS11(instruction);
                break;
  }
}



void OP1IS01()
{
  unsigned int opcode = getBits(instruction, 31, 30);
  
}

int checkOpcode1(unsigned int opcode1)
{
  switch(opcode1)
  {
    case 0b00 : return OP1IS00; //shift(immediate), add, subtract, move, and compare
                break;
    case 0b01 : return OP1IS01; //data processing, special data instructions and branch and exchange, load from literal pool, load/store data
                break;
    case 0b10 : whenOpcode1is10(instruction);
                break;
    case 0b11 : whenOpcode1is11(instruction);
                break;
  }
}




void Instruction_16bits(unsigned int instruction)
{
	
	
	
	
	
}



