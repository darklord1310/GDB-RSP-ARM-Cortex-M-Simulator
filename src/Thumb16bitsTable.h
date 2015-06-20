#ifndef Thumb16bitsTable_H
#define Thumb16bitsTable_H

#include <stdint.h>


typedef struct Thumb16bitsTableEntry Thumb16bitsTableEntry;


struct Thumb16bitsTableEntry{
  
    void (*execute)(uint32_t instruction);
  
};


Thumb16bitsTableEntry Thumb16Opcode00[64]; //= {
  
  //[0b00000] = {} ,
  //[00001] = {} ,
  //[0b10000] = { MOVImmediate16bitsT1}
  //[10001] = { MOVImmediate16bitsT1},
  //[10010] = { MOVImmediate16bitsT1},
  //[10011] = { MOVImmediate16bitsT1}
  
  
  
//};



#endif // Thumb16bitsTable_H
