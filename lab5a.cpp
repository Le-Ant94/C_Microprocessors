/*
    Names: Christopher Jew, Anthony Le
    Program: Lab 5 - PWM for DTMF generation
    Function: Uses Pulse width modulation to generate a dual tone multiple frequency. Input from a 4x4 keypad
              is read and then the KL46Z writes to the speaker and is outputted as a sound.
    Pins: KEYPAD  - PTC4 PTC0 PTB19 PTB18 PTC11 PTC10 PTC7 PTC6
          SPEAKER - PTE21 PTE23
    Libraries: mbed.h stdint.h keypad4x4.h
*/

#include "mbed.h"

//Define pins used before including 4x4keypad.h
//Let us define the pins used in main rather than the header

#ifndef KEYPAD4X4_ROW0
#define KEYPAD4X4_ROW0 PTC4
#endif
#ifndef KEYPAD4X4_ROW1
#define KEYPAD4X4_ROW1 PTC0
#endif
#ifndef KEYPAD4X4_ROW2
#define KEYPAD4X4_ROW2 PTB19
#endif
#ifndef KEYPAD4X4_ROW3
#define KEYPAD4X4_ROW3 PTB18
#endif
#ifndef KEYPAD4X4_COLUMN0
#define KEYPAD4X4_COLUMN0 PTC11
#endif
#ifndef KEYPAD4X4_COLUMN1
#define KEYPAD4X4_COLUMN1 PTC10
#endif
#ifndef KEYPAD4X4_COLUMN2
#define KEYPAD4X4_COLUMN2 PTC7
#endif
#ifndef KEYPAD4X4_COLUMN3
#define KEYPAD4X4_COLUMN3 PTC6
#endif

#include "keypad4x4.h"
#include "stdint.h"


Serial pc(USBTX, USBRX);

//Pulse Width Modulation ports designation
PwmOut rowPWM (PTE21); 
PwmOut colPWM (PTC9); 

//Arrays of Frequencies
float colFreq[5] = {1209, 1336, 1477, 1633, 0};
float rowFreq[5] = {697, 770, 852, 941, 0}; 

//Prototype
void keyTone(int,int);

//Main
int main()
{    
    //Sets data transfer rate
    pc.baud(115200);
    
    int row, column, key_ret;
    char keycode;
    
    //Sets pwm period
    rowPWM.period(0.0f);
    colPWM.period(0.0f);
    
    pc.printf("\r\nBeginning Keypad input\r\n");
    
    //Loop to read 4x4 Keypad inputs
    while(true)
    {
        //Write sets duty cycle percentage (speaker off)
        rowPWM.write(0.0f);
        colPWM.write(0.0f);
        //Wait 10 ms
        wait(0.01f);
        row = 0;
        column = 0;
        //Call keypad4x4_input() to get key pressed
        key_ret=keypad4x4_input(&keycode, &row, &column);
        //Error checks input
        if(key_ret < 0)
        {
            pc.printf("keypad4x4 error %i \r\n",key_ret);
        } 
        else 
        {
            pc.printf("\nKey %c at row %i, column %i, return code %i \r\n",keycode,row,column,key_ret);  
            
            pc.printf("\nASCII code: %i", keycode);
        } 
        
        //Calls function keyTown()
        keyTone(row, column);
    } 
}

/**********************************************
 Function: keyTone
 Parameters: two integers representing a row and a column
 Returns: Void
 
 Function outputs the sound of the frequency

************************************************/
void keyTone(int row, int col)
{ 
    //Sets period based on row/col
    rowPWM.period(1/rowFreq[row]);
    colPWM.period(1/colFreq[col]);
    //Write sets duty cycle percentage (speaker on)
    rowPWM.write(0.5f);
    colPWM.write(0.5f);
    //Output frequency for half a second
    wait(0.5f);
}