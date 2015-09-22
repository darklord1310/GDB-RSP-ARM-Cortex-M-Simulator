/*  
    GDB RSP and ARM Simulator

    Copyright (C) 2015 Wong Yan Yin, <jet_wong@hotmail.com>,
    Jackson Teh Ka Sing, <jackson_dmc69@hotmail.com>

    This file is part of GDB RSP and ARM Simulator.

    This program is free software, you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY, without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with This program.  If not, see <http://www.gnu.org/licenses/>.
*/


#include <stdio.h>
#include "unity.h"
#include "CustomTypeAssertion.h"

/* void assertEqualReadLine(char *expectedLine, IntelHex16Data *data, int line)
{
	char buffer[128];
	int i;


	for(i = 0; expectedLine[i] != '\n'; i++)
	{
		if(expectedLine[i] != data->line[i])
		{
			sprintf(buffer, "Expected %c but was %c at position %d. \nExpected %s is not the same with actual %s\n", expectedLine[i], data->line[i], i, expectedLine, data->line);
			UNITY_TEST_FAIL(line, buffer);
		}
	}
}

void assertEqualTLV(char type, char length, char value[], TLV *actual, int line)
{
	int i = 0;
    char msg[64];

	TEST_ASSERT_EQUAL(type, actual->type);
	TEST_ASSERT_EQUAL(length, actual->length);

	for(i = 0; i < length; i++)
	{
        if(value[i] != actual->value[i])
            sprintf(msg, "Data not the same at index %d", i);
		UNITY_TEST_ASSERT_EQUAL_INT(value[i], actual->value[i], line, msg);
		// printf("actual->value[%d]: %2x\n", i, actual->value[i]);
	}
} */

void assertEqualRegister(AffectedReg *reg, int line)
{
    char msg[64];
    
    if(reg->regValue != coreReg[reg->regNum])
    {
        sprintf(msg, "Register r%d not the same as expected. Expected %x but was %x", reg->regNum, reg->regValue, coreReg[reg->regNum]);
        UNITY_TEST_FAIL(line, msg);
    }
}
