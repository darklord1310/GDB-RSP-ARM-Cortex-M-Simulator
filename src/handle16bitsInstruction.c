#include "handle16bitsInstruction.h"


/*  This function will categorize all the 16bits Thumb Instructions
 *  15  14  13  12  11  10  9   8   7   6   5   4   3   2   1   0
 *  |   |   
 *   op1       
 *
 *  Check opcode 1 first, then branch out
 *
 *  opcode 1
 *    00    ------->  000 --->  LSL(immediate)
 *          |______>  001 --->  LSR(immediate)
 *          |______>  010 --->  ASR(immediate)
 *          |______>  011 --->  Add or Subtract (register/immediate) -----> 00 ---> Add (register)
 *          |                                                       |_____> 01 ---> Subtract (register)
 *          |                                                       |_____> 10 ---> Add (3 bit immediate)   
 *          |                                                       |_____> 11 ---> Subtract (3 bit immediate)   
 *          |
 *          |______> 100 --->   Move(immediate) 
 *          |______> 101 --->   CMP(immediate)
 *          |______> 110 --->   Add(8 bit immediate)
 *          |______> 111 --->   Subtract(8 bit immediate)
 *
 *
 *    01    -------> 0000 -----> Data processing ----> 0000 ----> AND(register)
 *          |                                    |___> 0001 ----> EOR(register)
 *          |                                    |___> 0010 ----> LSL(register)
 *          |                                    |___> 0011 ----> LSR(register)
 *          |                                    |___> 0100 ----> ASR(register)
 *          |                                    |___> 
 *          |
 *          |
 *          |
 *          |
 *          |
 *          |
 *          |
 *          |
 *          |______> 0001 ----->                
 *          |______> 001x ----->
 *          |______> 01xx ----->
 *          |______> 1xxx ----->
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
    case 0b00 : handleOpcode1Equal00(instruction);         //shift(immediate), add, subtract, move, and compare
                break;
    case 0b01 : handleOpcode1Equal01(instruction);         //data processing, special data instructions and branch and exchange, load from literal pool, load/store data
                break;
    case 0b10 : handleOpcode1Equal10(instruction);         
                break;
    case 0b11 : handleOpcode1Equal11(instruction);
                break;
  }
}




void handleOpcode1Equal00(unsigned int instruction)
{
  unsigned int opcode = getBits(instruction, 29, 27);
  
  switch(opcode)
  {
    case 0b000 : LSLImmediate(instruction);              //LSL(immediate)
                 break;
    case 0b001 : LSRImmediate(instruction);              //LSR(immediate)  
                 break;
    case 0b010 : ASRImmediate(instruction);
                 break;
    case 0b011 : AddOrSub(instruction);
                 break;
    case 0b100 : MoveImmediate(instruction);
                 break;
    case 0b101 : CMP(instruction);
                 break;
    case 0b110 : Add8bitImmediate(instruction);
                 break;
    case 0b111 : Subtract8bitImmediate(instruction);
                 break;
  }
}


void AddOrSub(unsigned int instruction)
{
  unsigned int opcode = getBits(instruction, 26, 25);
	
  switch(opcode)
  {
    case 0b00 : AddRegister(instruction);      
                break;
    case 0b01 : SubtractRegister(instruction); 
                break;
    case 0b10 : Add3bitImmediate(instruction);
                break;
    case 0b11 : Subtract3bitImmediate(instruction);
                break;
  }
}


void handleOpcode1Equal01(unsigned int instruction)
{
  unsigned int opcode = getBits(instruction, 29, 27);
  

}


void handleOpcode1Equal10(unsigned int instruction)
{
  unsigned int opcode = getBits(instruction, 29, 27);

}


void handleOpcode1Equal11(unsigned int instruction)
{
  unsigned int opcode = getBits(instruction, 29, 27);

}



