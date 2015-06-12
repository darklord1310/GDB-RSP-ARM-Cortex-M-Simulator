#ifndef Thumb16bitsTable_H
#define Thumb16bitsTable_H

#include <stdint.h>

typedef struct {
  
    void (*execute)(uint32_t instruction);
  
  
}Thumb16TableEntry;

/*
Thumb16TableEntry Thumb16Opcode[64] = {
  
  [0b000000] = {} ,
  [0b000001] = {} 

  
  
  
};
*/
#endif // Thumb16bitsTable_H
