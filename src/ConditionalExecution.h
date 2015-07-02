#ifndef ConditionalExecution_H
#define ConditionalExecution_H

#include <stdint.h>

typedef enum {EQ,NE,CS,CC,MI,PL,VS,VC,HI,LS,GE,LT,GT,LE,AL} conditionCases;

uint32_t cond;               //global variable 

int checkCondition();

#endif // ConditionalExecution_H
