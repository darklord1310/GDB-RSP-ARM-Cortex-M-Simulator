#ifndef ConditionalExecution_H
#define ConditionalExecution_H

#include <stdint.h>

typedef enum {EQ,NE,CS,CC,MI,PL,VS,VC,HI,LS,GE,LT,GT,LE,AL} conditionCases;

int checkCondition(uint32_t cond);

#endif // ConditionalExecution_H
