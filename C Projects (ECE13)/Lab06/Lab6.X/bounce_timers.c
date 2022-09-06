/*********************************************************************************
 Name: Shota Tonari
 Cruz ID: 1828506
 ECE13
 *********************************************************************************/


// **** Include libraries here ****
// old bounce
// Standard libraries
#include <stdio.h>
#include <GenericTypeDefs.h>

//CMPE13 Support Library
#include "BOARD.h"

// Microchip libraries
#include <xc.h>
#include <sys/attribs.h>

// User libraries
#include "Leds_Lab06.h"


// **** Declare any datatypes here ****

struct Timer {
    uint8_t event;
    int16_t timeRemaining;
};

// **** Define global, module-level, or external variables here ****
static struct Timer TimerC;
static struct Timer TimerB;
static struct Timer TimerA;
// For 2, 3, and 5 seconds
#define C_Time_Remain 190  
#define B_Time_Remain 114
#define A_Time_Remain 76
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
    printf("Welcome to 1828506's lab6 part1 (timers).  Compiled on %s %s.\n", __TIME__, __DATE__);

    // Initialize these LED
    LEDS_INIT();
    
    // Initialize variables assigned to the 3 Timers
    TimerC.event = FALSE;
    TimerB.event = FALSE;
    TimerA.event = FALSE;
    TimerC.timeRemaining = C_Time_Remain;
    TimerB.timeRemaining = B_Time_Remain;
    TimerA.timeRemaining = A_Time_Remain;
    
    while (1) {
        if (TimerC.event == TRUE){
            printf("C ");
            TimerA.event = FALSE;
            LATEbits.LATE2 = ~LATEbits.LATE2;
            //If this doesn't work
            //value ^= 0x04;
        }
        if (TimerB.event == TRUE){
            printf("B ");
            TimerB.event = FALSE;
            LATEbits.LATE1 = ~LATEbits.LATE1;
            //If this doesn't work
            //value ^= 0x02;
        }
        if (TimerA.event == TRUE){
            printf("A ");
            TimerA.event = FALSE;
            LATEbits.LATE0 = ~LATEbits.LATE0;
            //If this doesn't work
            //value ^=0x01;
        }
        //poll timer A
            //react to timer A events
            //clear timer A event flag
    }
    
    /***************************************************************************************************
     * Your code goes in between this comment and the preceding one with asterisks
     **************************************************************************************************/

}

/**
 * This is the interrupt for the Timer1 peripheral. It will trigger at the frequency of the peripheral
 * clock, divided by the timer 1 prescaler and the interrupt interval.
 * 
 * It should not be called, and should communicate with main code only by using module-level variables.
 */
void __ISR(_TIMER_1_VECTOR, ipl4auto) Timer1Handler(void)
{
    // Clear the interrupt flag.
    IFS0bits.T1IF = 0;
    /***************************************************************************************************
     * Your code goes in between this comment and the following one with asterisks.
     **************************************************************************************************/
    
    //update timerA
    //if timerA has counted down,
        //generate timerA event
        //reset timerA
    
    // Each Timer is Decremented by 1
    TimerC.timeRemaining--;
    TimerB.timeRemaining--;
    TimerA.timeRemaining--;
    
    // For Timer C
    if (TimerC.timeRemaining == FALSE && TimerC.event == 0){
        TimerC.event = TRUE;
        TimerC.timeRemaining = C_Time_Remain; 
    }
    
    // For Timer B
    if (TimerB.timeRemaining == FALSE && TimerB.event == 0){
        TimerB.event = TRUE;
        TimerB.timeRemaining = B_Time_Remain;
    }
    
    // For Timer A
    if (TimerA.timeRemaining == FALSE && TimerA.event == 0){
        TimerA.event = TRUE;
        TimerA.timeRemaining = A_Time_Remain;
    }

    /***************************************************************************************************
     * Your code goes in between this comment and the preceding one with asterisks
     **************************************************************************************************/

}