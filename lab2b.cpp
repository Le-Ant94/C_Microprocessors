#include "mbed.h"
#include "stdio.h"
#include "ctype.h"

Serial pc(USBTX, USBRX);

int main()
{
    pc.baud(115200);
    
    int num, smallestFactor, i;
    smallestFactor = 1;
    i = 2;

    pc.printf("Enter an integer greater than 1: ");
    pc.scanf("%i", &num);

    while(num <= 1)
    {
        pc.printf("Invalid Entry. Enter an integer greater than 1: ");
        pc.scanf("%i", &num);
    }

    while(num%i != num)
    {
        if(num%i == 0)
        {
            smallestFactor = i;
            pc.printf("Smallest factor of %i is %i.\n", num, smallestFactor);
            num = num/smallestFactor;
            pc.printf("The new number is %i.\n", num);
            i=2;
        }
        
        else
        {
            i++;
        }
        
        if(num%i == num)
        {
            pc.printf("Smallest Factor found. Smallest factor is %i.\n", smallestFactor);
        }
    }
}