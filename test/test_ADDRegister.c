#include "unity.h"
#include "ADDRegister.h"
#include "ARMRegisters.h"
#include "ADDSPRegister.h"
#include "getAndSetBits.h"
#include "getMask.h"
#include <stdint.h>
#include <stdbool.h>
#include "StatusRegisters.h"
#include "ModifiedImmediateConstant.h"
#include "ITandHints.h"
#include "ConditionalExecution.h"


void setUp(void)
{
  initCoreRegister();
}

void tearDown(void)
{
}





