#ifndef ConditionalExecution_H
#define ConditionalExecution_H

#include "getBits.h"
#include "getMask.h"
#include <stdint.h>
#include "StatusRegisters.h"

typedef enum {EQ,NE,CS,CC,MI,PL,VS,VC,HI,LS,GE,LT,GT,LE,AL} conditionCases;

int checkCondition(uint32_t cond);

#endif // ConditionalExecution_H
