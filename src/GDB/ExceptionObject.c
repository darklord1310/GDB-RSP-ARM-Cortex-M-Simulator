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

#include <stdio.h>
#include <malloc.h>
#include "ExceptionObject.h"

Exception *createException(char *msg, int errorCode, ExceptionType exceptionType)
{
    Exception *e = malloc(sizeof(Exception));
    e->msg = msg;
    e->errorCode = errorCode;
    e->exceptionType = exceptionType;
    return e;
}

void freeException(Exception *e)
{
    free(e);
}

void dumpException(Exception *e)
{
    printf("%s (%c%d)\n", e->msg, e->exceptionType, e->errorCode);
}