/*
 * File:   kruss008_main.c
 * Author: Tyler Krussow
 */


#include "xc.h"
#include "p24Fxxxx.h"
#include "kruss008_head_FinalProject.h"
//#include <string.h>

// CW1: FLASH CONFIGURATION WORD 1 (see PIC24 Family Reference Manual 24.1)
#pragma config ICS = PGx1          // Comm Channel Select (Emulator EMUC1/EMUD1 pins are shared with PGC1/PGD1)
#pragma config FWDTEN = OFF        // Watchdog Timer Enable (Watchdog Timer is disabled)
#pragma config GWRP = OFF          // General Code Segment Write Protect (Writes to program memory are allowed)
#pragma config GCP = OFF           // General Code Segment Code Protect (Code protection is disabled)
#pragma config JTAGEN = OFF        // JTAG Port Enable (JTAG port is disabled)


// CW2: FLASH CONFIGURATION WORD 2 (see PIC24 Family Reference Manual 24.1)
#pragma config POSCMOD = NONE           // Primary Oscillator Select (Primary oscillator disabled. 
					// Primary Oscillator refers to an external osc connected to the OSC1 and OSC2 pins)
#pragma config I2C1SEL = PRI       // I2C1 Pin Location Select (Use default SCL1/SDA1 pins)
#pragma config IOL1WAY = OFF       // IOLOCK Protection (IOLOCK may be changed via unlocking seq)
#pragma config OSCIOFNC = ON       // OSC2/CLKO/RC15 functions as port I/O (RC15)
#pragma config FCKSM = CSECME      // Clock Switching and Monitor (Clock switching is enabled, 
                                       // Fail-Safe Clock Monitor is enabled)
#pragma config FNOSC = FRCPLL      // Oscillator Select (Fast RC Oscillator with PLL module (FRCPLL))

char start_array[]          = {'W', 'E', 'L', 'C', 'O', 'M', 'E', ' ', 'T', 'O', ' ', 'S', 'I', 'M', 'O', 'N', '.', 
'P', 'R', 'E', 'S', 'S', ' ', 'A', 'N', 'Y', ' ', 'B', 'U', 'T', 'T', 'O', 'N', ' ', 'T', 'O', ' ', 'S', 'T', 'A', 'R', 'T', '\0'};
//char start_array1[]       = {'W', 'E', 'L', 'C', 'O', 'M', 'E', ' ', 'T', 'O', ' ', 'S', 'I', 'M', 'O', 'N', '.', '\0'};
//char start_array2[]       = {'P', 'R', 'E', 'S', 'S', ' ', 'A', 'N', 'Y', ' ', 'B', 'U', 'T', 'T', 'O', 'N', ' ', 'T', 'O', ' ', 'S', 'T', 'A', 'R', 'T', '\0'};
//char display_array[]      = {'R', 'O', 'U', 'N', 'D', ' ',  ':', ' ', 'W', 'A', 'T', 'C', 'H', '\0'};
char input_array[]          = {'B', 'E', 'G', 'I', 'N', '\0'};
char transition_array[]     = {'R', 'O', 'U', 'N', 'D', ' ', 'C', 'O', 'M', 'P', 'L', 'E', 'T', 'E', '\0'};
char winner_array[]         = {'C', 'O', 'N', 'G', 'R', 'A', 'T', 'S', '!', ' ', 'Y', 'O', 'U', ' ', 'W', 'I', 'N', '.', '\0'};
char loser_array[]          = {'G', 'A', 'M', 'E', ' ', 'O', 'V', 'E', 'R', '\0'};
char red_array[]            = {'R', 'E', 'D', '\0'};
char green_array[]          = {'G', 'R', 'E', 'E', 'N', '\0'};
char blue_array[]           = {'B', 'L', 'U', 'E', '\0'};
char yellow_array[]         = {'Y', 'E', 'L', 'L', 'O', 'W', '\0'};
char yourTurn_array[]       = {'Y', 'O', 'U', 'R', ' ', 'T', 'U', 'R', 'N', '!', '\0'};

void __attribute__ ((__interrupt__,__auto_psv__)) _T2Interrupt(void)
{
    _T2IF = 0;
    lcd_cmd(0b00011000);            // this commands the LCD to shift the screen to the left
}

int main(void) {
    lcd_init();                             
    lcd_printString(transition_array);       //Displaying an array, for testing
    while(1)
    {
        shift();
    }
        
    return 0;
}
