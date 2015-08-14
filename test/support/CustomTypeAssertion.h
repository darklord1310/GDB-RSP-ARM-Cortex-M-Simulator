#ifndef CustomTypeAssertion_H
#define CustomTypeAssertion_H

#include <stdio.h>
#include "FunctionalTest.h"
#include "ARMRegisters.h"

/* #define TEST_ASSERT_EQUAL_ReadLine(expectedLine, actualLine)	\
			   assertEqualReadLine(expectedLine,				\
								   actualLine,					\
								   __LINE__						\
								  ); */


#define TEST_ASSERT_EQUAL_Register(affectedReg)	                \
			   assertEqualRegister(affectedReg,					\
								   __LINE__						\
								  );

// void assertEqualReadLine(char *expectedLine, IntelHex16Data *data, int line);

void assertEqualRegister(AffectedReg *reg, int line);

#endif // CustomTypeAssertion_H