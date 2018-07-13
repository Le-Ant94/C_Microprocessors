#include "mbed.h"

#define MOTOR_DRIVER_IN1 PTC11 /* the IN1 and IN2 drivers are PWM controlled by enable EN12 */
#define MOTOR_DRIVER_IN2 PTC10
#define MOTOR_DRIVER_EN12 PTB19 

#define MOTOR_FREQUENCY 10

Serial pc(USBTX, USBRX);

PwmOut en12(MOTOR_DRIVER_EN12);
DigitalOut in1(MOTOR_DRIVER_IN1);
DigitalOut in2(MOTOR_DRIVER_IN2);
++--++-+-+-+-
float states[9]={1.00, 0.75, 0.50, 0.25, 0.00, .25, 0.50, 0.75, 1.00};
int cwCCW[9]={0,0,0,0,0,1,1,1,1};


int main(){
        
        pc.baud(115200);
        int i = 4;
        en12.period(0.001f);
        en12.write(states[i]);
        char uin;
        
        pc.printf("+ = increment by 25%\n");
        pc.printf("- = decrement by 25%\n");
        pc.printf("Q/q = quit program\n");
        pc.printf("Enter command: \n");           
        while (true){    
            uin = pc.getc();
                
            switch(uin){
                case '-':
                    if (i > 0){
                        i--;
                    }
                    break;
                        
                case '+':
                    if( i < 8){
                        i++;
                    }
                    break;
                        
                case 'q':
                case 'Q':
                    pc.printf("Exitting Program...");
                    return 0;
                    
                default:
                    //For any other input do nothing
            }
            en12.write(states[i]); //Write the % duty cycle using array
            in1 = cwCCW[i]; //Sets voltage high or low for input 1
            in2 = !in1;  //Sets voltage for input2 opposite of input1
      }
}