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