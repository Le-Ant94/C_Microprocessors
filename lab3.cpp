#include "mbed.h"
#include "stdint.h"
#include "seven_segment.h"
#include "keypad4x4.h"

Serial pc(USBTX, USBRX); 
/* USBTX=PTA2, USBRX=PTA1, so actually UART0 */
/* UART0 on KL46Z routed through OpenSDA chip to USB */
/* now "vcom" refers to this virtualized com port */

int main()
{
    pc.baud(115200);
    
    int col;
    int row;
    int keyword;
    char charac;
    char temp = 'y'; //'' is for char vars, "" is for string vars; "temp" has to be a char to compare with "keyword"
    
    while (true) // program runs until board has no more power
    {
        keyword = keypad4x4_input(&charac, &row, &col); // & is pass by ref that changes the value in int; &charac saves the input, and &row & &col find the input
        seven_segment_output(charac);
        
        if(temp != charac)
        {
            printf("%x\n", keyword);
            temp = charac;
        }
    }
}