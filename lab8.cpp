#include "mbed.h"
#include "stdint.h"

Serial pc(USBTX, USBRX);
char current_command = ' ';

/* Serial Bluetooth adapter */
/* you will need to establish a bluetooth connection with a host PC */
/* see adapter label for connection information */
Serial bt(PTE16,PTE17);  /*bluetooth adapter operates at 9600/8/N/1 */


/*SN754410 motor driver */
PwmOut motor_en12(PTB18);    /*this could be replaced with DigitalOut if speed control is not needed */
PwmOut motor_en34(PTB19);    /*this could be replaced with DigitalOut if speed control is not needed */
DigitalOut motor_in1(PTE3);
DigitalOut motor_in2(PTE2);
DigitalOut motor_in3(PTC6);
DigitalOut motor_in4(PTC7);

/* Servo Motor Drivers */
/* servo frequency 50 Hz, minimum duty 5%, maximum duty 10%, center duty 7.5% */
PwmOut servo1(PTA6);
PwmOut servo2(PTA7);

/* Infrared Line Sensors */
DigitalIn ir1(PTE18);
DigitalIn ir2(PTE19);

/* HC-SR04 Ultrasonic distance sensor */
DigitalOut distance_trigger(PTC13);
// DigitalIn distance_echo(PTC16); /* option */
InterruptIn distance_echo(PTC16); /* option */

Ticker distance_start;
Timer distance_timer;
float distance_time, distance_inches, distance_cm;

void pulse_trigger()
{
    distance_trigger.write(1);
    wait(10E-6);
    distance_trigger.write(0);
}

void echo_start()
{
    distance_timer.reset();
}

void echo_end()
{
    distance_time=distance_timer.read();
    if(distance_time < 30E-3)   // delay longer than 30 ms indicates no echo
    {
        distance_inches=distance_time*13503.9*0.5;     // speed of sound = 13503.9 inches/second and distance to object is 1/2 path length;
        distance_cm=distance_time*34300.0*0.5;     // speed of sound = 34300 cm/second and distance to object is 1/2 path length;
        
        if(current_command == 'w' && distance_inches < 5){
            motor_en12.write(0.0);
            motor_in1.write(0);
            motor_in2.write(0);
            motor_en34.write(0.0);
            motor_in3.write(0);
            motor_in4.write(0);
        }
        
    }
    else
    {
        distance_inches=-1.0;
        distance_cm=-1.0;
    }
}

void getDirection(char c);

int main()
{

pc.baud(115200);  /* interface to host via USB at 115200 */
bt.baud(9600);  /* interface via Bluetooth at 9600 */

distance_timer.start();
distance_echo.rise(&echo_start);
distance_echo.fall(&echo_end);
distance_start.attach(&pulse_trigger, 100E-3);

motor_en12.period(1.0E-3); /* dc motor PWM at 1kHz */
motor_en34.period(1.0E-3);
motor_en12.write(0.0);  /*dc motor PWM initially at 0% duty cycle, i.e. off */
motor_en12.write(0.0);
motor_in1.write(0); /* motors initially poered down */
motor_in2.write(0);
motor_in3.write(0);
motor_in4.write(0);

servo1.period(20.0E-3); /* servo motor PWM at 50 Hz */
servo2.period(20.0E-3);
servo1.write(7.5E-2); /*servo initially at 7.5%, i.e. center position for standard, stationary for continuous */
servo2.write(7.5E-2);

/* Your code goes HERE */

/*pc.printf("PC serial port test\n");
bt.printf("Bluetooth serial port test\n");

pc.printf("dc motor 1 forward 100 speed\n");
bt.printf("dc motor 1 forward 100 speed\n");
motor_en12.write(1.0);
motor_in1.write(1);
motor_in2.write(0);
wait(5.0);

pc.printf("dc motor 1 forward 50 speed\n");
bt.printf("dc motor 1 forward 50 speed\n");
motor_en12.write(0.5);
motor_in1.write(1);
motor_in2.write(0);
wait(5.0);

pc.printf("dc motor 1 reverse 100 speed\n");
bt.printf("dc motor 1 reverse 100 speed\n");
motor_en12.write(1.0);
motor_in1.write(0);
motor_in2.write(1);
wait(5.0);

pc.printf("dc motor 1 reverse 50 speed\n");
bt.printf("dc motor 1 reverse 50 speed\n");
motor_en12.write(0.5);
motor_in1.write(0);
motor_in2.write(1);
wait(5.0);

pc.printf("dc motor 1 stopped\n");
bt.printf("dc motor 1 stopped\n");
motor_en12.write(0.0);
motor_in1.write(0);
motor_in2.write(0);
wait(1.0);

pc.printf("dc motor 2 forward 100 speed\n");
bt.printf("dc motor 2 forward 100 speed\n");
motor_en34.write(1.0);
motor_in3.write(1);
motor_in4.write(0);
wait(5.0);

pc.printf("dc motor 2 forward 50 speed\n");
bt.printf("dc motor 2 forward 50 speed\n");
motor_en34.write(0.5);
motor_in3.write(1);
motor_in4.write(0);
wait(5.0);

pc.printf("dc motor 2 reverse 100 speed\n");
bt.printf("dc motor 2 reverse 100 speed\n");
motor_en34.write(1.0);
motor_in3.write(0);
motor_in4.write(1);
wait(5.0);

pc.printf("dc motor 2 reverse 50 speed\n");
bt.printf("dc motor 2 reverse 50 speed\n");
motor_en34.write(0.5);
motor_in3.write(0);
motor_in4.write(1);
wait(5.0);

pc.printf("dc motor 2 stopped\n");
bt.printf("dc motor 2 stopped\n");
motor_en34.write(0.0);
motor_in3.write(0);
motor_in4.write(0);
wait(1.0);

pc.printf("servo 1 minimum duty cycle\n");
bt.printf("servo 1 minimum duty cycle\n");
servo1.write(5.0E-2);
wait(5.0);

pc.printf("servo 1 maximum duty cycle\n");
bt.printf("servo 1 maximum duty cycle\n");
servo1.write(10.0E-2);
wait(5.0);

pc.printf("servo 1 centered\n");
bt.printf("servo 1 centered\n");
servo1.write(7.5E-2);
wait(5.0);

pc.printf("servo 2 minimum duty cycle\n");
bt.printf("servo 2 minimum duty cycle\n");
servo2.write(5.0E-2);
wait(5.0);

pc.printf("servo 2 maximum duty cycle\n");
bt.printf("servo 2 maximum duty cycle\n");
servo2.write(10.0E-2);
wait(5.0);

pc.printf("servo 2 centered\n");
bt.printf("servo 2 centered\n");
servo2.write(7.5E-2);
wait(5.0);

pc.printf("distance measurement (20 measures)\n");
bt.printf("distance measurement (20 measures)\n");
for(int i=0; i<20; i++)
{
    if(distance_inches>0.0)
    {
        pc.printf("%7.2f inches, %7.2f cm\n",distance_inches, distance_cm);
        bt.printf("%7.2f inches, %7.2f cm\n",distance_inches, distance_cm);
    }
    else
    {
        pc.printf("distance out of range\n");
        bt.printf("distance out of range\n");
   }
   wait(0.5);
}
        
pc.printf("Infrared Line Followers (200 measures)\n");
bt.printf("Infrared Line Followers (200 measures)\n");
for(int i=0; i<200; i++)
{
    int ir_l, ir_r;
    ir_l=ir1.read();
    ir_r=ir2.read();
    pc.printf("IR1: %1i,  IR2: %1i\n",ir_l,ir_r);
    bt.printf("IR1: %1i,  IR2: %1i\n",ir_l,ir_r);
    wait(0.1);
}
*/
pc.printf("Command Test.  Press a key.\n");
bt.printf("Command Test.  Press a key.)\n");
while(true)
{ 
    
      
    pc.printf("Command from PC: ");
    pc.scanf(" %c",&current_command);
    
    /*if(bt.readable())
    {
        current_command=bt.getc();
        pc.printf("Command from Bluetooth: %c \n",current_command);
        bt.printf("Command from Bluetooth %c \n",current_command);
    }*/
    
    getDirection(current_command);
    
                
}

} //end of main()

void getDirection(char c){
    switch(c){
        case 'w':
            
            motor_en12.write(1.0);
            motor_en34.write(1.0);
            motor_in1.write(1);
            motor_in2.write(0);
            motor_in3.write(0);
            motor_in4.write(1);
            wait(1.0);
            
            motor_en12.write(0.0);
            motor_in1.write(0);
            motor_in2.write(0);
            motor_en34.write(0.0);
            motor_in3.write(0);
            motor_in4.write(0);
            
            break;
            
        case 's':
            motor_en12.write(1.0);
            motor_en34.write(1.0);
            motor_in1.write(0);
            motor_in2.write(1);
            motor_in3.write(1);
            motor_in4.write(0);
            wait(1.0);
            
            motor_en12.write(0.0);
            motor_in1.write(0);
            motor_in2.write(0);
            motor_en34.write(0.0);
            motor_in3.write(0);
            motor_in4.write(0);
            
            break;
            
        case 'a':
            motor_en12.write(0.0);
            motor_en34.write(1.0);
            motor_in1.write(0);
            motor_in2.write(0);
            motor_in3.write(0);
            motor_in4.write(1);
            wait(1.0);
            
            motor_en12.write(0.0);
            motor_in1.write(0);
            motor_in2.write(0);
            motor_en34.write(0.0);
            motor_in3.write(0);
            motor_in4.write(0);
            
            break;
            
        case 'd':
            motor_en12.write(1.0);
            motor_en34.write(0.0);
            motor_in1.write(1);
            motor_in2.write(0);
            motor_in3.write(0);
            motor_in4.write(0);
            wait(1.0);
            
            motor_en12.write(0.0);
            motor_in1.write(0);
            motor_in2.write(0);
            motor_en34.write(0.0);
            motor_in3.write(0);
            motor_in4.write(0);
            
            break;
            
        case 'f':
            motor_en12.write(0.0);
            motor_en34.write(0.0);
            motor_in1.write(0);
            motor_in2.write(0);
            motor_in3.write(0);
            motor_in4.write(0);
            break;
            
        default:
            break;    
    
    }
    
}

