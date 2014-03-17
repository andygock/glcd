#include <stdio.h>
#include <stdlib.h>


// 'C' source line config statements

#include <xc.h>
#include <plib.h>

// DEVCFG3
// USERID = No Setting

// DEVCFG2
#pragma config FPLLIDIV = DIV_12        // PLL Input Divider (12x Divider)
#pragma config FPLLMUL = MUL_24         // PLL Multiplier (24x Multiplier)
#pragma config UPLLIDIV = DIV_12        // USB PLL Input Divider (12x Divider)
#pragma config UPLLEN = OFF             // USB PLL Enable (Disabled and Bypassed)
#pragma config FPLLODIV = DIV_256       // System PLL Output Clock Divider (PLL Divide by 256)

// DEVCFG1
#pragma config FNOSC = PRI              // Oscillator Selection Bits (Primary Osc (XT,HS,EC))
#pragma config FSOSCEN = OFF            // Secondary Oscillator Enable (Disabled)
#pragma config IESO = ON                // Internal/External Switch Over (Enabled)
#pragma config POSCMOD = OFF            // Primary Oscillator Configuration (Primary osc disabled)
#pragma config OSCIOFNC = OFF           // CLKO Output Signal Active on the OSCO Pin (Disabled)
#pragma config FPBDIV = DIV_8           // Peripheral Clock Divisor (Pb_Clk is Sys_Clk/8)
#pragma config FCKSM = CSDCMD           // Clock Switching and Monitor Selection (Clock Switch Disable, FSCM Disabled)
#pragma config WDTPS = PS1048576        // Watchdog Timer Postscaler (1:1048576)
#pragma config FWDTEN = OFF             // Watchdog Timer Enable (WDT Disabled (SWDTEN Bit Controls))

// DEVCFG0
#pragma config DEBUG = ON               // Background Debugger Enable (Debugger is enabled)
#pragma config ICESEL = ICS_PGx2        // ICE/ICD Comm Channel Select (ICE EMUC2/EMUD2 pins shared with PGC2/PGD2)
#pragma config PWP = OFF                // Program Flash Write Protect (Disable)
#pragma config BWP = OFF                // Boot Flash Write Protect bit (Protection Disabled)
#pragma config CP = OFF                 // Code Protect (Protection Disabled)


// LED1 at RG6/SCK2/PMA5/CN8
#define GREEN_LED_PORT  IOPORT_G
#define GREEN_LED_PIN   BIT_6

// LED2 at #U1RTS/OC2/RD1
#define YELLOW_LED_PORT IOPORT_D
#define YELLOW_LED_PIN  BIT_1

#define MMC_SC_PORT IOPORT_B
#define MMC_SC_PIN  BIT_13


#include "glcd.h"
#include "fonts/font5x7.h"


#define SYS_FREQ                (8000000L)


void delay_ms(unsigned int ms)
{
    OpenTimer1(T1_ON | T1_PS_1_256, 0xFFFF);
    while (ms--)
    {  // t x 1ms loop
        WriteTimer1(0);
        while (ReadTimer1() < SYS_FREQ/256/1000);
    }
    CloseTimer1();
}


/*
 * 
 */
int main(int argc, char** argv)
{
    SYSTEMConfigPerformance(SYS_FREQ);

    // disabel mmc
    PORTSetPinsDigitalOut(MMC_SC_PORT, MMC_SC_PIN);
    PORTSetBits(MMC_SC_PORT, MMC_SC_PIN);

    glcd_init();

    while(1){
        glcd_test_circles();
        //glcd_test_counter_and_graph();
        //glcd_test_text_up_down();
        //glcd_test_tiny_text();
        //glcd_test_hello_world();
        //glcd_test_rectangles();
        //glcd_test_scrolling_graph();
        //glcd_test_bitmap_128x64();
    }

    return (EXIT_SUCCESS);
}
