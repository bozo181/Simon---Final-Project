/*
 * File:   kruss008_definitions_FinalProject.c
 * Author: Tyler Krussow
 */

#include "xc.h"
#include "p24Fxxxx.h"
#include "kruss008_head_FinalProject.h"
#include <string.h>

//ASSUME WE HAVE A WAIT_MS FUNCTION

void wait_ms(long int ms)
    {
    long int i;
    i = 0;
    for(i = 0; i<ms; i++)\
    {
        delay_ms();
    }
    return;
}

void delay_ms(void){
    asm("repeat #15993");
    asm("nop");
    asm("return");
}

void lcd_init(void)
{
    CLKDIVbits.RCDIV = 0;
    AD1PCFG = 0x9fff;
    TRISA &= 0b1111111111111110;
    
    
    wait_ms(50);         // waits 50 ms
    lcd_cmd(0b00111000); // function set, normal instruction mode
    lcd_cmd(0b00111001); // function set, extended instruction mode
    lcd_cmd(0b00010100); // interval osc
    lcd_cmd(0b01110000); // contrast C3-C0
    lcd_cmd(0b01011110); // ion, Bon, C5-C4
    lcd_cmd(0b01101100); // follower control
    wait_ms(200);        // waits 200 ms
    lcd_cmd(0b00111000); // function set, normal instruction mode
    lcd_cmd(0b00001100); // display On
    lcd_cmd(0b00000001); // clear Display
    wait_ms(2);          // waits 2 ms
}

void lcd_setCursor(char x, char y)
{
   char destination = 0xC0 * y + x; // selecting the memory address we want
   lcd_cmd(destination);            // sending our memory address to the LCD
}

//void lcd_printChar(char character)
//{
//    I2C2CONbits.SEN = 1;            // begin start sequence
//    while(I2C2CONbits.SEN);         // assuring the LCD receives the start bit
//    IFS3bits.MI2C2IF = 0;           // clear interrupt flag
//    
//    I2C2TRN = 0b01111100;           // send 8-bits consisting of the slave address and the R/nW bit
//    while(!IFS3bits.MI2C2IF);       // wait for acknowledge
//    IFS3bits.MI2C2IF = 0;           // clear interrupt flag
//    
//    I2C2TRN = 0b01000000;           // 8-bits consisting of control byte /w RS=1
//    while(!IFS3bits.MI2C2IF);       // wait for acknowledge
//    IFS3bits.MI2C2IF = 0;           // clear interrupt flag
//    
//    I2C2TRN = character;            // 8-bits consisting of the data byte
//    while(!IFS3bits.MI2C2IF);       // wait for acknowledge
//    IFS3bits.MI2C2IF = 0;           // clear interrupt flag
//    
//    I2C2CONbits.PEN = 1;            // begin stop sequence  
//    while(I2C2CONbits.PEN);         // assuring the LCD receives the stop bit
//}

void lcd_cmd(char Package)          // takes care of sending the data to the LCD display. 
{                                   // input data we are sending
    I2C2CONbits.SEN = 1;            // begin start sequence
    while(I2C2CONbits.SEN);         // assuring the LCD receives the start bit
    IFS3bits.MI2C2IF = 0;           // clear interrupt flag
    
    I2C2TRN = 0b01111100;           // send 8-bits consisting of the slave address and the R/nW bit
    while(!IFS3bits.MI2C2IF);       // wait for acknowledge
    IFS3bits.MI2C2IF = 0;           // clear interrupt flag
    
    I2C2TRN = 0b00000000;           // 8-bits consisting of control byte /w RS=0
    while(!IFS3bits.MI2C2IF);       // wait for acknowledge
    IFS3bits.MI2C2IF = 0;           // clear interrupt flag
    
    I2C2TRN = Package;              // 8-bits consisting of the data byte
    while(!IFS3bits.MI2C2IF);       // wait for acknowledge
    IFS3bits.MI2C2IF = 0;           // clear interrupt flag
    
    I2C2CONbits.PEN = 1;            // Begin stop sequence  
    while(I2C2CONbits.PEN);         // Assuring the LCD receives the stop bit
}

//char lcd_roundCount(int round, int dig1, int dig2, int dig3)
//{
//    int i;
//    i = 0;
//    for (i = 0; i<round; i++)
//    {
//        
//        char display_array[] = {'R', 'O', 'U', 'N', 'D', ' ', dig1, dig2, dig3, ':', ' ', 'W', 'A', 'T', 'C', 'H', '\0'};
//    }
//}

void lcd_printString(char *s)
{
    int i;
    int a = strlen(s);
    lcd_setCursor(0,0);
    lcd_cmd(0x01);                          // Clear all display bits
	I2C2CONbits.SEN = 1;                    // Begin start sequence
    while(I2C2CONbits.SEN);                 // Assuring the LCD receives the start bit
    IFS3bits.MI2C2IF = 0;                   // clear interrupt flag
    
    I2C2TRN = 0b01111100;                   // send 8-bits consisting of the slave address and the R/nW bit
    while(!IFS3bits.MI2C2IF);               // wait for acknowledge
    IFS3bits.MI2C2IF = 0;                   // clear interrupt flag
    for(i = 0; i< a; i++){
        if(i != (a-1)){
                I2C2TRN = 0b11000000;       // 8-bits consisting of control byte to not show stop
                while(!IFS3bits.MI2C2IF);   // wait for acknowledge
                IFS3bits.MI2C2IF = 0;       // clear interrupt flag
        }

        //Happens when it is the last character
        if(i == (a-1)){

            I2C2TRN = 0b01000000;           // 8-bits consisting of control byte to show stop
            while(!IFS3bits.MI2C2IF);       // wait for acknowledge
            IFS3bits.MI2C2IF = 0;           // clear interrupt flag

        }
//        //If we don't have this, the first two characters don't display
//        if(i < 2){
//            wait_ms(1);
//        }
        I2C2TRN = *s;
        while(!IFS3bits.MI2C2IF);           // wait for acknowledge
        IFS3bits.MI2C2IF = 0;               // clear interrupt flag
        s++;        
    }
	I2C2CONbits.PEN = 1;                    // begin stop sequence
    while(I2C2CONbits.PEN);                 // assuring the LCD receives the stop bit
    IFS3bits.MI2C2IF = 0;                   // clear interrupt flag
}

void shift(void)
{
    wait_ms(500);                           // this sets the rate at which the display shifts
    lcd_cmd(0b00011000);                    // this commands the LCD to shift the screen to the left
}
