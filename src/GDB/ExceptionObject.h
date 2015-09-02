#ifndef ExceptionObject_H
#define ExceptionObject_H

typedef enum {SIGNAL = 'S', ERROR = 'E'} ExceptionType;

typedef struct Exception Exception;
typedef struct Exception *ExceptionPtr;

struct Exception
{
    char *msg;
    int  errorCode;
    ExceptionType exceptionType;
};

Exception *createException(char *msg, int errorCode, ExceptionType exceptionType);
void freeException(Exception *e);
void dumpException(Exception *e);

#endif // ExceptionObject_H
