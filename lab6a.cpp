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
    pc.printf("%1i",stepper_pointer);
}

int main()
{

pc.baud(115200);

step_clock.attach(&stepper_step,(1.0/MOTOR_FREQUENCY));
/* Ticker automatically calls stepper_step every (1.0/MOTOR_FREQUENCY) seconds */

stepper_input=stepper_sequence[stepper_pointer]; /* initial position of motor */

char motor_command;
/* Motor commands from keypad */
/* '1' - half size steps alternating single coils and dual coils */
/* '2' - full size steps using single coils only */
/* '3' - full size steps using dual coils only */
/* '4' - clockwise rotation */
/* '5' - counter-clockwise rotation */
/* '6' - continuous rotation at given step speed */
/* '7' - single step at a time (one step per 'D' keypress */

while(true)
{
    pc.printf("Available Options: \n");
    pc.printf(" '1' - half size steps alternating single coils and dual coils \n");
    pc.printf(" '2' - full size steps using single coils only \n");
    pc.printf(" '3' - full size steps using dual coils only \n");
    pc.printf(" '4' - clockwise rotation \n");
    pc.printf(" '5' - counter-clockwise rotation \n");
    pc.printf(" '6' - continuous rotation at given step speed \n");
    pc.printf(" '7' - single step at a time (one step per 'D' keypress) \n");
    pc.printf(" 'Q' or 'q' - quit program \n");
    pc.printf("Enter option: ");
    //pc.scanf("%c", &motor_command);
    motor_command=pc.getc();
    
    if(motor_command == 'Q' || motor_command == 'q'){
        pc.printf("Quitting Program...");
        break;
    }

    switch(motor_command)
    {
        case '1':
        {   
            stepper_increment=1;
            break;
        }
        case '2':
        {   
            stepper_increment=2;
            stepper_pointer=stepper_pointer & 0xFE; // 0xFE = 254 in hex
            break;
        }
        case '3':
        {   
            stepper_increment=2;
            stepper_pointer=stepper_pointer | 0x01;
            break;
        }
        case '4':
        {   
            stepper_direction=1;
            break;
        }
        case '5':
       {   
            stepper_direction=-1;
            break;
        }
        case '6':
        {   
            stepper_mode=1;
            stepper_enable=1;
            break;
        }
        case '7':
        {   
            stepper_mode=0;
            stepper_enable=1;
            break;
        }
    
        default:
        {/* any other key, make no changes */}
    }

}

}