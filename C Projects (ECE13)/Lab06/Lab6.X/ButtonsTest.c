/*********************************************************************************
 Name: Shota Tonari
 Cruz ID: 1828506
 ECE13
 *********************************************************************************/

// **** Include libraries here ****
// Standard libraries
#include <stdio.h>

//CMPE13 Support Library
#include "BOARD.h"
#include "Buttons.h"

// Microchip libraries
#include <xc.h>
#include <sys/attribs.h>

// User libraries

// **** Set macros and preprocessor directives ****

// **** Declare any datatypes here ****

// **** Define global, module-level, or external variables here ****
static uint8_t event = 0;
static uint8_t previous = 0;
static uint8_t status = 0;
// May need to comment this out
static uint8_t eventnone = BUTTON_EVENT_NONE;

#define AND &
#define DAND &&
#define NEQUAL !=

// **** Declare function prototypes ****

int main(void)
{
    BOARD_Init();

    // Configure Timer 1 using PBCLK as input. This default period will make the LEDs blink at a
    // pretty reasonable rate to start.
    T1CON = 0; // everything should be off
    T1CONbits.TCKPS = 2; // 1:64 prescaler
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
    printf("Welcome to 1828506's lab6 part4 (ButtonsTest).  Compiled on %s %s.\n", __TIME__, __DATE__);

    
    printf("Please press some buttons!\n");
    // Initiate Buttons
    ButtonsInit();
    // While Loop
    while(1) {
        char button1[] = "----";
        char button2[] = "----";
        char button3[] = "----";
        char button4[] = "----";
        
        if (status) {
            if (event AND BUTTON_EVENT_4DOWN) {
                sprintf(button4, "DOWN");
            }
            if (event AND BUTTON_EVENT_4UP) {
                sprintf(button4, "UP");
            }
            if (event AND BUTTON_EVENT_3DOWN) {
                sprintf(button3, "DOWN");
            }
            if (event AND BUTTON_EVENT_3UP) {
                sprintf(button3, "UP");
            }
            if (event AND BUTTON_EVENT_2DOWN) {
                sprintf(button2, "DOWN");
            }
            if (event AND BUTTON_EVENT_2UP) {
                sprintf(button2, "UP");
            }
            if (event AND BUTTON_EVENT_1DOWN) {
                sprintf(button1, "DOWN");
            }
            if (event AND BUTTON_EVENT_1UP) {
                sprintf(button1, "UP");
            }      
            printf("Event: 4:%s 3:%s 2:%s 1:%s\n", button4, button3, button2, button1);
            
            // Set event back to 0
            status = 0;
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
    event = ButtonsCheckEvents();
    if(event NEQUAL previous DAND event){
        status = 1;
        previous = event;
    }   

    /***************************************************************************************************
     * Your code goes in between this comment and the preceding one with asterisks
     **************************************************************************************************/

}