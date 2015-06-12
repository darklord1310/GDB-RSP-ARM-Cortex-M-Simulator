#include "ChkSumCal.h"

int chkSumCal(char *buf)
{
    int sum = 0;

    for(int i = 2; buf[i] != '#'; i++)
    {
        sum += buf[i];
    }
    
    return sum;
    
    // while(quotient != 0)
    // {
        // temp = quotient % 16;

        //To convert integer into character
        // if( temp < 10)
            // temp =temp + 48;
        // else
            // temp = temp + 55;

        // hex[j--]= temp;
        // quotient = quotient / 16;
    // }
}