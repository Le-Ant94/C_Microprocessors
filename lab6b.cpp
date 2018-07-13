#include "mbed.h"
#include "stdint.h"

Serial pc(USBTX, USBRX);
/* USBTX=PTA2, USBRX=PTA1, so actually UART0 */

// PWM with pins designation
PwmOut servo0(PTE20); // one of the 4 pins the servo is connected to (in this case, servo0)

/* Controlling a 4-phase unipolar stepper motor requires 4 half-H drivers */
/* PWM is not used and the enable pins may be digital outputs. */
/* One SN754410 can control one 4-phase unipolar stepper motor */
/* The direction of motor rotation is controlled by step sequence */
/* The speed of motor rotation is controlled by duration of each step. */
/* The coils A and C should be opposite one another and the coils B and D should be opposite one another */

// I also changed the pins accordingly
/* This code assumes the use of a SN754410 quad half-H driver or similar */
/* The SN754410 has 4 push-pull driver stages with inputs IN1, IN2, IN3, IN4 */
#define MOTOR_DRIVER_IN1 PTC11 /* the IN1 and IN2 drivers are PWM controlled by enable EN12 */
#define MOTOR_DRIVER_IN2 PTC10
#define MOTOR_DRIVER_IN3 PTC9 /* the IN3 and IN4 drivers are PWM controlled by enable EN34 */
#define MOTOR_DRIVER_IN4 PTC8
#define MOTOR_DRIVER_EN12 PTB19 
#define MOTOR_DRIVER_EN34 PTB18

#define MOTOR_FREQUENCY 10

#define COIL_A 0x01        /* binary: 0001 */
#define COIL_B 0x02        /* binary: 0010 */
#define COIL_C 0x04        /* binary: 0100 */
#define COIL_D 0x08        /* binary: 1000 */

int stepper_sequence[8]={ COIL_A, COIL_A+COIL_B, COIL_B, COIL_B+COIL_C, COIL_C, COIL_C+COIL_D, COIL_D, COIL_D+COIL_A };
int stepper_pointer=0;      /* pointer determines which is the current step in the sequence */
int stepper_increment=1;    /* how far apart in the sequence each step is */
int stepper_direction=1;    /* increment (1) or decrement (-1) through the sequence */
int stepper_enable=1;       /* take a step (1) or don't take a step (0) */
int stepper_mode=1;         /* continouosly step (1) or take only one step at a time (0) */
/* defaults are half steps, clockwise, continuous */


/* STEPPER */
/* assumes phase order of A, C, B, D so that A&C share one Enable and B&D share an enable. */
BusOut stepper_input(MOTOR_DRIVER_IN1, MOTOR_DRIVER_IN3, MOTOR_DRIVER_IN2, MOTOR_DRIVER_IN4);
DigitalOut stepper_enAC(MOTOR_DRIVER_EN12,1);
DigitalOut stepper_enBD(MOTOR_DRIVER_EN34,1);

Ticker step_clock;

void stepper_step()
{
    stepper_pointer = ( stepper_pointer +  (stepper_enable * stepper_direction * stepper_increment) +8 ) % 8;
    stepper_enAC = (stepper_sequence[stepper_pointer] & (COIL_A+COIL_C))?1:0;   /* an unused coil is disabled to prevent motor drag */
    stepper_enBD = (stepper_sequence[stepper_pointer] & (COIL_B+COIL_D))?1:0;
    stepper_input = stepper_sequence[stepper_pointer];
    stepper_enable = stepper_mode;
   
}

void get_information(char &stepSize, char &coil, char &cw, char &continuous){
    
    pc.printf("Half size steps or full size steps? 1 for half | 2 for full : ");
    pc.scanf("%c", &stepSize);
    while(stepSize != '1' && stepSize != '2'){
        pc.printf("\nInvalid input. 1 for half step size | 2 for full step size :");
        pc.scanf("%c", &stepSize);
    }
    pc.printf("\n");
    
    if(stepSize == '2'){
        pc.printf("Full size using single or dual coils? 1 for single | 2 for dual :");
        pc.scanf("%c", &coil);
        while(coil != '1' && coil != '2'){
            pc.printf("\nInvalid input. 1 for single coil | 2 for dual coil :");
            pc.scanf("%c", &coil);
        }   
    } else {
        coil = '3'; // default case for half steps alternating single/dual
    }
    pc.printf("\n");
    
    pc.printf("Clockwise or counter clock wise? 1 for clockwise | 2 for counter clockwise :");
    pc.scanf("%c", &cw);
    while(cw != '1' && cw != '2'){
        pc.printf("\nInvalid input. 1 for clockwise | 2 for counter clockwise: ");
        pc.scanf("%c", &cw);
    }
    pc.printf("\n");
    
    pc.printf("Single step or continuous step? 1 for single | 2 for continuous: ");
    pc.scanf("%c", &continuous);
    while(continuous != '1' && continuous != '2'){
        pc.printf("\nInvalid input. 1 for single | 2 for continuous: ");
        pc.scanf("%c", &continuous);
    }
    pc.printf("\n");
    
}

int main(){

    pc.baud(115200);
    char stepSize, coil, cw, continuous;
    get_information(stepSize, coil, cw, continuous);

    step_clock.attach(&stepper_step,(1.0/MOTOR_FREQUENCY));
    /* Ticker automatically calls stepper_step every (1.0/MOTOR_FREQUENCY) seconds */

    stepper_input=stepper_sequence[stepper_pointer]; /* initial position of motor */


    while(true){
        
        if(stepSize == '1'){
            pc.printf("Half size steps alternating single coils and dual coils. \n");
            stepper_increment=1;
            if(cw == '1'){
                pc.printf("Clock Wise \n");
                stepper_direction=1;
            
            } else {
                pc.printf("Counter Clockwise \n");
                stepper_direction=-1;
            }
            if(continuous == '1'){
                stepper_mode=0;
                stepper_enable=1;
            } else {
                stepper_mode=1;
                stepper_enable=1;
            }
            
        } else {
            pc.printf("Full size steps with ");
            if(coil == '1'){
                pc.printf("single coils only. \n");
                stepper_increment=2;
                stepper_pointer=stepper_pointer & 0xFE; // 0xFE = 254 in hex   
            } else {
                pc.printf("dual coils only. \n");
                stepper_increment=2;
                stepper_pointer=stepper_pointer | 0x01;
            if(cw == '1'){
                pc.printf("Clock Wise \n");
                stepper_direction=1;
            } else {
                pc.printf("Counter Clockwise \n");
                stepper_direction=-1;
            }
            if(continuous == '1'){
                stepper_mode=0;
                stepper_enable=1;
            } else {
                stepper_mode=1;
                stepper_enable=1;
            }
        }
    }
    }
}   