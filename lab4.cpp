//Anthony Le, Christopher Jew

#include "mbed.h"
//#include "keypad4x4.h"
#include "seven_segment.h" 
#include "stdint.h"

SPI spy(PTD6,PTD7,PTD5); //specific pins fro specific functions

Serial pc(USBTX,USBRX);

DigitalOut rclk(PTD4);
DigitalOut pl(PTD2);
DigitalOut ce(PTA13);

uint8_t seg7, leds8, switches, buttons; //wont use all

int main(){
    pc.baud(115200); 
    
    while(true){

        pl = 0; // parallel load low
        wait(0.000001);
        pl = 1; // high; switches into 76hc165
        ce = 0;
        buttons = spy.write(0); //no useful datat to write, so we have to write 0 as a placeholder. Needs something.
        switches = spy.write(0);
        pc.printf("%2x %2x\n",switches,buttons);
        ce=1;
        seg7=seven_segment_find_pattern(switches); //seg7 not working
        spy.write(switches);
        //spy.write(seg7); //seg7 not working
        rclk=1;
        wait(0.000001);
        rclk=0;
    }
}
