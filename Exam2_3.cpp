#include "mbed.h"

Serial pc(USBTX, USBRX);
AnalogIn batt1(PTB0);
AnalogIn batt12(PTB1);
unsigned int sample1, sample2, difference;

main()
{
    pc.baud(115200);
    
    while(true)
    {
        sample1 = batt1.read()*6;
        pc.printf("Voltage across battery 1 is: %u \n", sample1);
        
        sample2 = batt12.read()*12 - sample1;
        pc.printf("Voltage across battery 2 is: %u \n", sample2);
        
        difference = sample2 - sample1;
        
        if (difference >= 0.15)
        {
            pc.printf("Warning: check batteries. \n");
        }
        
        wait(15.0);
    }
}