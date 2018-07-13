#include "mbed.h"
#include "stdint.h"

int main(char sentence[])
{
    int sumSpaces = 1;
    int x;
    
    while (sentence[x] != '\0')
    {
        if (sentence[x] == ' ')
        {
            sumSpaces++;
        }
        
        if (sentence[x - 1] == ' ' && sentence[x] == ' ')
        {
            sumSpaces--;
        }
    
        x++;
    }
    
    return (sumSpaces);
}