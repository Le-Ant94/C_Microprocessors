#include "mbed.h" // looks thru local directory, instead of <> that looks through entire lib
#include "stdio.h"
#include "ctype.h"

Serial pc(USBTX, USBRX);


int main()
{
    pc.baud(115200); //processing speed of FRDM

    char name[100];
    int sumASCII = 0;
    int x = 0;
    int month, day, lucky;

    pc.printf("Enter your name (max 100 characters): ");
    pc.scanf ("%s", name);
    
    while (name[x] != '\0')
    {
        sumASCII += name[x];
        x++;    
    }

    pc.printf("\n The ASCII sum of your name is %i.\n", sumASCII);

    pc.printf("\n Enter your date of birth in format 'mm dd': ");
    pc.scanf("%i %i", &month, &day);

    lucky = sumASCII%(month+day);

    pc.printf("\n Your lucky number is %i.\n", lucky);
}