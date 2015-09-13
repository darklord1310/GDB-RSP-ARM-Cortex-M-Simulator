/*  
    Program Name       : GDB RSP and ARM Simulator
    Author             : Wong Yan Yin, Jackson Teh Ka Sing 
    Copyright (C) 2015 TARUC

    This file is part of GDB RSP and ARM Simulator.

    GDB RSP and ARM Simulator is free software, you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    GDB RSP and ARM Simulator is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY, without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with GDB RSP and ARM Simulator.  If not, see <http://www.gnu.org/licenses/>.

*/

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