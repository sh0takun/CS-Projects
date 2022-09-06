// **** Include libraries here ****
// Standard libraries
#include <stdio.h>

//CMPE13 Support Library
#include "BOARD.h"
#include "Leds_Lab06.h"

// Microchip libraries
#include <xc.h>
#include <sys/attribs.h>

// User libraries

// **** Set macros and preprocessor directives ****

// **** Declare any datatypes here ****

// **** Define global, module-level, or external variables here ****
static uint8_t previous = 0;
static uint8_t event = 0;
static uint8_t button = 0;
static uint8_t switchS = 0;

#define AND &
#define NEQUAL !=
#define DAND &

// **** Declare function prototypes ****

int main(void)
{
    BOARD_Init();

    // Configure Timer 1 using PBCLK as input. This default period will make the LEDs blink at a
    // pretty reasonable rate to start.
    T1CON = 0; // everything should be off
    T1CONbits.TCKPS = 1; // 1:8 prescaler
    PR1 = 0xFFFF; // interrupt at max interval
    T1CONbits.ON = 1; // turn the timer on

    // Set up the timer interrupt with a priority of 4.
    IFS0bits.T1IF = 0; //clear the interrupt flag before configuring
    IPC1bits.T1IP = 4; // priority of  4
    IPC1bits.T1IS = 0; // subpriority of 0 arbitrarily 
    IEC0bits.T1IE = 1; // turn the interrupt on

    /***************************************************************************************************
     * Your code goes in between this comment and the following one with asterisks.
     **************************************************************************************************/
    printf("Welcome to 1828506's lab6 part5 (bounce_buttons).  Compiled on %s %s.\n", __TIME__, __DATE__);
    
    
    ButtonsInit();
    LEDS_INIT();
    
    while(1) {
        if (event) {
            switchS = SWITCH_STATES();
            
            //Switch 4
            if (switchS AND SWITCH_STATE_SW4) { 
                if (button AND BUTTON_EVENT_4UP) {
                    LATEbits.LATE7 = ~LATEbits.LATE7;
                    LATEbits.LATE6 = ~LATEbits.LATE6;
                }

            } else { 
                if (button AND BUTTON_EVENT_4DOWN) {
                    LATEbits.LATE7 = ~LATEbits.LATE7;
                    LATEbits.LATE6 = ~LATEbits.LATE6;
                }
            }
            
            // Switch 3
            if (switchS AND SWITCH_STATE_SW3) { 
                if (button AND BUTTON_EVENT_3UP) {
                    LATEbits.LATE5 = ~LATEbits.LATE5;
                    LATEbits.LATE4 = ~LATEbits.LATE4;
                }

            } else { 
                if (button AND BUTTON_EVENT_3DOWN) {
                    LATEbits.LATE5 = ~LATEbits.LATE5;
                    LATEbits.LATE4 = ~LATEbits.LATE4;
                }
            }
            
            // Switch 2
            if (switchS AND SWITCH_STATE_SW2) { 
                if (button AND BUTTON_EVENT_2UP) {
                    LATEbits.LATE3 = ~LATEbits.LATE3;
                    LATEbits.LATE2 = ~LATEbits.LATE2;
                }

            } else { 
                if (button AND BUTTON_EVENT_2DOWN) {
                    LATEbits.LATE3 = ~LATEbits.LATE3;
                    LATEbits.LATE2 = ~LATEbits.LATE2;
                }
            }

            // Switch 1
            if (switchS AND SWITCH_STATE_SW1) { 
                if (button AND BUTTON_EVENT_1UP) {
                    LATEbits.LATE1 = ~LATEbits.LATE1;
                    LATEbits.LATE0 = ~LATEbits.LATE0;
                }

            } else { 
                if (button AND BUTTON_EVENT_1DOWN) {
                    LATEbits.LATE1 = ~LATEbits.LATE1;
                    LATEbits.LATE0 = ~LATEbits.LATE0;
                }
            }
            
            // Clear event
            event = 0;

        }
    }
    /***************************************************************************************************
     * Your code goes in between this comment and the preceding one with asterisks
     **************************************************************************************************/

    while (1);
}

/**
 * This is the interrupt for the Timer1 peripheral. It should check for button events and stores them in a
 * module-level variable.
 * 
 * You should not modify this function for ButtonsTest.c or bounce_buttons.c!
 */
void __ISR(_TIMER_1_VECTOR, ipl4auto) Timer1Handler(void)
{
    // Clear the interrupt flag.
    IFS0bits.T1IF = 0;

    /***************************************************************************************************
     * Your code goes in between this comment and the following one with asterisks.
     **************************************************************************************************/
    button = ButtonsCheckEvents();
    if ((button NEQUAL previous) DAND (button)) {
        previous = button;
        event = 1;
    }
    /***************************************************************************************************
     * Your code goes in between this comment and the preceding one with asterisks
     **************************************************************************************************/

}