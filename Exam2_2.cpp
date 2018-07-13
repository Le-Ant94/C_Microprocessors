#include "mbed.h"

Serial pc(USBTX, USBRX);

Timer t;
InterruptIn anemo(PTA13);
float pulse, speed;

void pulse_reset()
{
    t.reset();
}
    
void pulse_read()
{
    pulse = t.read_us();
    t.start();
}

main()
{
    pc.baud(115200);
    
    while(true)
    {
        anemo.fall(&pulse_reset);
        anemo.rise(&pulse_read);
        anemo.fall(&pulse_read);
        
        speed = 1.0E-6 / (10.0 * pulse);
        pc.printf("%f \n", &speed);
        
        wait(1.0);
    }
}