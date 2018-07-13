#include "mbed.h"
#include "stdint.h"
#include "keypad4x4.h"

int keypad4x4_integer()
{
    int sum = 0;
    int num = 0;
    int prev = 1;
    int posneg = 1;
    char x;

    while(true)
    {
        x = keypad4x4_getc();   
        posneg = prev;
        
        if (x == '0')
        {
           num = 0;
        }
        
        if (x == '1')
        {
           num = 1;
        }
        
        if (x == '2')
        {
           num = 2;
        }
        
        if (x == '3')
        {
           num = 3;
        }
        
        if (x == '4')
        {
           num = 4;
        }
        
        if (x == '5')
        {
           num = 5;
        }
        
        if (x == '6')
        {
           num = 6;
        }
        
        if (x == '7')
        {
           num = 7;
        }
        
        if (x == '8')
        {
           num = 8;
        }
        
        if (x == '9')
        {
           num = 9;
        }
        
        if (x == '#')
        {
            return (sum);
        }
        
        if (x == '*')
        {
            prev = -1;
            continue;
        }
        
        else
        {
            prev = 1;
        }
        
        if (num >= 0 && num <= 9)
        {
            sum += num*posneg;
        }
    }
}