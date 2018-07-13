#include "mbed.h"

Serial pc(USBTX, USBRX);

//Input analog samples via PTB1 & PTB2
AnalogIn input1(PTB1);
AnalogIn input2(PTB2);

//Output a PWM signal via PTE21
PwmOut output(PTE21);

//Set max and min for PWM period
float period_min = 0.05E-3;
float period_max = 50.05E-3;

//Set max and min for PWM duty cycle
float duty_min = 0.0;
float duty_max = 1.0;

float sample1, sample2, period, duty;

main()
{
    while(true)
    {
        sample1 = input1.read(); //recieve analog sample read from PTB1
        period = period_max - sample1*(period_max - period_min);
        output.period(period); //take analog sample value
        
        sample2 = input2.read(); //recieve analog sample read from PTB2
        duty = duty_min + sample2*(duty_max - duty_min);
        output.write(duty); //take duty cycle value
        
        wait(0.1);
    }
}