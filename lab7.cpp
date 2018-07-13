#include "stdio.h"
#include "stdint.h"
#include "mbed.h"
#include "Freedom_headers.h"

/* UNCOMMENT THE FOLLOWING LINE TO ENABLE SERIAL CONNECTION TO PC */
#define USE_PC TRUE
/* UNCOMMENT THE FOLLOWING LINE TO ENABLE  KEYPAD USE */
//#define USE_KEYPAD4X4 TRUE
/* UNCOMMENT THE FOLLOWING LINE TO ENABLE 7 SEGMENT LED USE */
//#define USE_SEVEN_SEGMENT TRUE
/* UNCOMMENT THE FOLLOWING LINE TO ENABLE SLCD USE */
//#define USE_SLCD TRUE
/* UNCOMMENT THE FOLLOWING LINE TO ENABLE CHARACTER LCD USE */
//#define USE_CHARACTER_LCD TRUE
/* UNCOMMENT THE FOLLOWING LINE TO ENABLE SD CARD FILESYSTEM VIA DEFAULT SPI */
#define USE_SD_CARD TRUE
/* UNCOMMENT THE FOLLOWING LINE TO ENABLE DS1307 REAL-TIME CLOCK VIA IIC */
#define USE_DS1307 TRUE
/* UNCOMMENT THE FOLLOWING LINE TO ENABLE SIMPLE FIFO FUNCTIONS */
#define USE_SIMPLE_FIFO TRUE

/********************************************************************/
#ifdef USE_PC
Serial pc(USBTX,USBRX);
/* USBTX=PTA2, USBRX=PTA1 */
/* UART0_TX=PTA2, UART0_RX=PTA1, so actually UART0 */
/* UART0 on KL46Z routed through OpenSDA chip to USB */
/* now "pc" refers to this virtualized com port on host computer*/

/* available functions */
/*
pc.baud()
pc.format()
pc.readable()
pc.writeable()
pc.read()
pc.write()
pc.getc()
pc.putc()
pc.gets)
pc.puts()
pc.printf()
pc.scanf()

*/
#endif /* #ifdef USE_PC */
/********************************************************************/

/********************************************************************/

#ifdef USE_KEYPAD4X4
/* use the following definitions to utilize the 4x4 keypad routines */
/* comment out these definitions to use the library defaults */
/* feel free to alter these defines to whichever pins are convenient */
/*
#define KEYPAD4X4_COLUMN0 PTE31
#define KEYPAD4X4_COLUMN1 PTE19
#define KEYPAD4X4_COLUMN2 PTE18
#define KEYPAD4X4_COLUMN3 PTE17
#define KEYPAD4X4_ROW0 PTE16
#define KEYPAD4X4_ROW1 PTE6
#define KEYPAD4X4_ROW2 PTE3
#define KEYPAD4X4_ROW3 PTE2
*/
// #define KEYPAD4X4_TYPE 0  /* touch-tone telephone layout with * -> * and # -> # */   /* 123A,456B,789C,*0#D */
//#define KEYPAD4X4_TYPE 1  /* touch-tone telephone layout with * -> E and # -> F */  /* 123A,456B,789C,E0FD */
//#define KEYPAD4X4_TYPE 2  /* hexadecimal layout */  /* 0123,4567,89AB,CDEF */

//#include "keypad4x4.h"
/* available functions */
/* char keypad4x4_getc(void) */
/* int keypad4x4_input(char *key_value, int * key_row, int *key_column) */
/* int keypad4x4_query(char *key_value, int * key_row, int *key_column) */
#endif  /* #ifdef USE_KEYPAD4X4 */
/********************************************************************/

/********************************************************************/

#ifdef USE_SEVEN_SEGMENT
/* comment out these definitions to use the library defaults */
/* feel free to alter these defines to whichever pins are convenient */
/*#define SEVEN_SEGMENT_A PTC13
#define SEVEN_SEGMENT_B PTC16
#define SEVEN_SEGMENT_C PTA7
#define SEVEN_SEGMENT_D PTA6
#define SEVEN_SEGMENT_E PTA14
#define SEVEN_SEGMENT_F PTA15
#define SEVEN_SEGMENT_G PTA16
#define SEVEN_SEGMENT_DP PTA17
#include "seven_segment.h"*/
/* available functions */
/* int seven_segment_output(char ss_out) */
#endif  /* #ifdef USE_SEVEN_SEGMENT */
/********************************************************************/

/********************************************************************/
#ifdef USE_SLCD
#include "SLCD.h"
SLCD slcd;
/* available functions */
/*
slcd.printf("1234");    // standard printf function, only charaters in ASCII_TO_WF_CODIFICATION_TABLE will display
slcd.putc('A');         // prints a single character 
slcd.Write_Char('A');   // prints a single character
slcd.All_Segments(y);   // y=1 for ALL segments on, 0 for ALL segments off  
slcd.DPx(y);            // x=DP1 to DP3, y=1 for on 0 for off
slcd.Colon(y);          // y=1 for on, 0 for off
slcd.CharPosition=x;    // x=0 to 3, 0 is start position
slcd.Home();            // sets next charater to posistion 0 (start)
slcd.Contrast (x);      // set contrast x=0 - 15, 0 lightest, 15 darkest    
*/

#endif /* #ifdef USE_SLCD */
/********************************************************************/

/********************************************************************/
#ifdef USE_CHARACTER_LCD
/* comment out these definitions to use the library defaults */

#define CHARACTER_LCD_RS PTE17
#define CHARACTER_LCD_E PTE19
#define CHARACTER_LCD_DB4 PTE16
#define CHARACTER_LCD_DB5 PTE6
#define CHARACTER_LCD_DB6 PTE3
#define CHARACTER_LCD_DB7 PTE2
#define CHARACTER_LCD_ROWS 2
#define CHARACTER_LCD_COLUMNS 16

#include "character_lcd.h"
/* available functions */
/*
void character_lcd_initialize(void)
int character_lcd_set_data_address(uint8_t lcd_address)
int character_lcd_cursor(uint8_t row, uint8_t column)
int character_lcd_set_CG_address(uint8_t lcd_address)
void character_lcd_pulse_e(void)
int character_lcd_write_nybble(uint8_t lcd_data, uint8_t lcd_select)
int character_lcd_write_byte(uint8_t lcd_data, uint8_t lcd_select)
int character_lcd_putc(char lcd_data)
int character_lcd_puts(char *str)
//int character_lcd_read_nybble(uint8_t *lcd_data, uint8_t lcd_select)
//int character_lcd_read_byte(uint8_t *lcd_data, uint8_t lcd_select)
*/
#endif /* #ifdef USE_CHARACTER_LCD */

/********************************************************************/
#ifdef USE_SD_CARD
#include "SDFileSystem.h"
#define SD_MOSI PTD6
#define SD_MISO PTD7
#define SD_SCK  PTD5
#define SD_CS   PTD4
char sd_root_name[]="sd";
char filename[80];
SDFileSystem sd(SD_MOSI, SD_MISO, SD_SCK, SD_CS, sd_root_name);  /* MOSI,MISO,SCK,CS, "Name of directory structure" */

/* available functions include all normal filesystem commands */
/* filenames need to be prefixed with sd_root_name */
/* example code: */
    /*sprintf(filename,"/%s/%s",sd_root_name,"sdtest.txt");*/
    // /* filename = "/sd/sdtest.txt" */
    /*FILE *fp = fopen(filename, "w");  */
/* */

#endif /* #ifdef USE_SD_CARD*/
/********************************************************************/

/********************************************************************/
#ifdef USE_DS1307
#include "EE3420_time.h"

/* available functions */
/* 
void prompt_for_time(DS1307_DATA *tdata) 
void set_DS1307_time(DS1307_DATA *tdata)
void get_DS1307_time(DS1307_DATA *tdata) 
void set_KL46Z_RTC_from_DS1307()
void format_time_string_12(DS1307_DATA *tdata, char *time_str)
void format_time_string_24(DS1307_DATA *tdata, char *time_str)
void show_clock_12(DS1307_DATA *tdata)
void show_clock_24(DS1307_DATA *tdata)
 */

#endif /* #ifdef USE_DS1307*/
/********************************************************************/

/********************************************************************/
#ifdef USE_SIMPLE_FIFO

/* comment out the folloing definitions to use the library defaults */
#define SIMPLE_FIFO_SIZE 32

#include "simple_fifo.h"

/* available functions */
/* 
void simple_fifo_init(SIMPLE_FIFO *f)
int simple_fifo_writeable(SIMPLE_FIFO *f)
int simple_fifo_readable(SIMPLE_FIFO *f)
int simple_fifo_write(SIMPLE_FIFO *f, char c)
int simple_fifo_read(SIMPLE_FIFO *f, char *c)
char simple_fifo_putc(SIMPLE_FIFO *f, char c)
char simple_fifo_getc(SIMPLE_FIFO *f, char *c)
void simple_fifo_puts(SIMPLE_FIFO *f, char str[])
void simple_fifo_gets(SIMPLE_FIFO *f, char str[], int count)

In addition to the SIMPLE_FIFO type, a number of similar fifo types are constructed for various data types.
The following fifo types are defined:
FIFO_CHAR   //for character data, similar to SIMPLE_FIFO above
FIFO_INT   //for default integer type
FIFO_U8     //for uint8_t data
FIFO_U16    //for uint16_t data
FIFO_U32    //for uint32_t data
FIFO_I8     //for int8_t data
FIFO_I16    //for int16_t data
FIFO_I32    //for int32_t data
FIFO_FLOAT  //for float data
FIFO_DOUBLE  //for double data

The following functions are defined for the FIFO_?? types:
void fifo_??_init(FIFO_?? *f)
int fifo_??_writeable(FIFO_?? *f)
int fifo_??_readable(FIFO_?? *f)
int fifo_??_write(FIFO_?? *f, char c)
int fifo_??_read(FIFO_?? *f, char *c)
 */

#endif /* #ifdef USE_SIMPLE_FIFO*/
/********************************************************************/

FIFO_FLOAT temp_data;
int samples_active=0;
float temp_level;
float ftemp;
char timestr[80];
    
AnalogIn temp_sensor(PTB0);
InterruptIn left_button(PTC12);  /* button labeled SW3, wired active-low needing pull-up */
Ticker t;
#define SAMPLE_FREQUENCY 4250.0

void take_sample()
{
    if(samples_active==1)
    {    
        temp_level=(temp_sensor.read());
        fifo_float_write(&temp_data,temp_level);
    }
}

void start_sample()
{
    if(samples_active==0)
    {
        fifo_float_init(&temp_data);
        samples_active=1;  
    }
    else
    {
        samples_active=0;
    }
    wait(0.1);
}

int main()
{

#ifdef USE_PC    
    pc.baud(115200);    /* set serial port speed to 115200 - must be matched in terminal emulator */
#endif
#ifdef USE_SLCD
    slcd.All_Segments(0);
#endif
#ifdef USE_CHARACTER_LCD
    character_lcd_initialize();
#endif

    fifo_float_init(&temp_data);
    
#ifdef USE_PC
    pc.printf("\n");
#endif

    get_DS1307_time(&EE3420_DS1307_data);
    set_KL46Z_RTC_from_DS1307();

    sprintf(filename,"/sd/FGEN4250.csv");
    
    FILE *fp = fopen(filename, "w");
    if(fp == NULL) 
    {
        error("Could not open file ""%s"" for write\n", filename);
    }
  //  fprintf(fp,"date, time, temperature (Fahrenheit)\n");
    fclose(fp);

    samples_active=0;
    
    left_button.mode(PullUp);
    left_button.fall(&start_sample);

    t.attach(&take_sample,1.0/SAMPLE_FREQUENCY);

while(true)
{
    if(fifo_float_readable(&temp_data))
    {
        fp = fopen(filename, "a");
        while(fifo_float_readable(&temp_data))
        {
            get_DS1307_time(&EE3420_DS1307_data);
            format_time_string_24(&EE3420_DS1307_data, timestr);
            fifo_float_read(&temp_data,&ftemp);
          //  fprintf(fp, "20%02i/%02i/%02i, %02i:%02i:%02i, %f\n",EE3420_DS1307_data.year,EE3420_DS1307_data.month,EE3420_DS1307_data.day,EE3420_DS1307_data.hours,EE3420_DS1307_data.min,EE3420_DS1307_data.sec,ftemp);
            fprintf(fp, "%f\n",ftemp);
        }
        fclose(fp);    
    }
}
    


} //end of main()