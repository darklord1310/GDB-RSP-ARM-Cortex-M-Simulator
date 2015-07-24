#ifndef State_H
#define State_H

typedef enum{
    INITIAL,
    ACK,
    NACK,
    SERVE_RSP,
    KILL
} State;

#endif // State_H