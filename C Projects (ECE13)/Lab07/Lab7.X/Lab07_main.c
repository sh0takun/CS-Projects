/*********************************************************************************
 Name: Shota Tonari
 Cruz ID: 1828506
 ECE13
 *********************************************************************************/


// **** Include libraries here ****

// Standard libraries
#include <stdio.h>

//CSE13E Support Library
#include "BOARD.h"
#include "Adc.h"
#include "Ascii.h"
#include "Oled.h"
#include "OledDriver.h"
#include "Buttons.h"
#include "Leds.h"

// Microchip libraries
#include <xc.h>
#include <sys/attribs.h>



// **** Set any macros or preprocessor directives here ****
// Defining operators to visualize easier
#define DIVIDE /
#define MULTIPLY *
#define ADD +
#define SUB -
#define DEQUAL ==
#define EQUAL =
#define NOEQUAL !=
#define LESSTHAN <
#define GREATERTHAN >
#define GREATERTHANE >=
#define OR ||
#define AND &
#define DAND &&
#define FIVE 5
#define FIVE1 5
#define DEGREE 300
#define MIN 60

// Set a macro for resetting the timer, makes the code a little clearer.
#define TIMER_2HZ_RESET() (TMR1 = 0)


// **** Set any local typedefs here ****
typedef enum {
    ALERT, SETUP, SELECTOR_CHANGE_PENDING, COOKING, RESET_PENDING
} OvenState;

typedef enum {
    TIME, TEMP
} Select;

typedef enum {
    TOAST, BAKE, BROIL
} Mode;

typedef struct {
    OvenState state;
    Mode mode;
    Select select;
    uint16_t initialTime;
    uint16_t cookingTime;
    uint16_t temp;
    uint16_t presstime;
    //add more members to this struct
} OvenData;

// **** Declare any datatypes here ****

// **** Define any module-level, global, or external variables here ****
static OvenData ovenData;
static uint16_t TimeFree = 0;
static uint16_t TimerTick = 0;
static uint16_t buttonEvent;
static uint16_t Change_Adc = 0;
static uint16_t blinkTime = 0;
static uint16_t TimeStart = 0;
static uint16_t buttonEvent;
static uint8_t blinkingE = 0;
static uint8_t buttonDown3;
static uint8_t buttonUp3;
static uint8_t buttonDown4;
static uint8_t buttonUp4;
static uint8_t blink = 0;
static uint8_t conblink = 0;


// **** Put any helper functions here ****
void UPDATELED(OvenData ovenData) {
    uint16_t timetotal = ovenData.initialTime;
    uint16_t timenow = ovenData.cookingTime;
    
    // in base 16
    uint16_t unit = (timetotal MULTIPLY 1000 DIVIDE 8); 
    uint16_t LEDnumber = (timenow) MULTIPLY 1000 DIVIDE unit;
    
    // If you have extra time you can define the actual codes for the LEDs.
    if (LEDnumber DEQUAL 7)
        LEDS_SET(0b11111110);
    else if (LEDnumber DEQUAL 6)
        LEDS_SET(0b11111100);
    else if (LEDnumber DEQUAL 5)
        LEDS_SET(0b11111000);
    else if (LEDnumber DEQUAL 4)
        LEDS_SET(0b11110000);
    else if (LEDnumber DEQUAL 3)
        LEDS_SET(0b11100000);
    else if (LEDnumber DEQUAL 2)
        LEDS_SET(0b11000000);
    else if (LEDnumber DEQUAL 1)
        LEDS_SET(0b10000000);
    else if (LEDnumber DEQUAL 0)
        LEDS_SET(0b00000000);
    else
        LEDS_SET(0b11111111);
}
    

/*This function will update your OLED to reflect the state .*/
void updateOvenOLED(OvenData ovenData){
    //update OLED here
    //declare char's
    char tempdata[50];
    char temptime[50];
    char TopOven[50];
    char BottomOven[50];
    char string[150];
    
    // pointers
    char *diffmode;
    
    // 2 lines
    char *OvenLine2 = "|-----|";
    char *OvenLine1 = "|     |";
    
    if ((ovenData.state DEQUAL SETUP) OR (ovenData.state DEQUAL SELECTOR_CHANGE_PENDING) OR (ovenData.state DEQUAL ALERT)) {
        sprintf(BottomOven, "|%s%s%s%s%s|", OVEN_BOTTOM_OFF, OVEN_BOTTOM_OFF, OVEN_BOTTOM_OFF, OVEN_BOTTOM_OFF, OVEN_BOTTOM_OFF);
        sprintf(TopOven, "|%s%s%s%s%s|", OVEN_TOP_OFF, OVEN_TOP_OFF, OVEN_TOP_OFF, OVEN_TOP_OFF, OVEN_TOP_OFF);
        
        if (ovenData.mode DEQUAL BAKE) {
            if (ovenData.select DEQUAL TIME) {
                sprintf(tempdata, " TEMP: %d%sF", ovenData.temp, DEGREE_SYMBOL);
                sprintf(temptime, ">TIME: %d:%02d", ovenData.cookingTime / FIVE / MIN, (ovenData.cookingTime / FIVE) % MIN);
            } 
            else {
                sprintf(tempdata, ">TEMP: %d%sF", ovenData.temp, DEGREE_SYMBOL);
                sprintf(temptime, " TIME: %d:%02d", ovenData.cookingTime / FIVE / MIN, (ovenData.cookingTime / FIVE) % MIN);           
            }
            
        }
        else if (ovenData.mode DEQUAL BROIL) {            
            sprintf(tempdata, " TEMP: 500%sF", DEGREE_SYMBOL);
            sprintf(temptime, " TIME: %d:%02d", ovenData.cookingTime / FIVE / MIN, (ovenData.cookingTime / FIVE) % MIN);
        }
        else {
            sprintf(temptime, " TIME: %d:%02d", ovenData.cookingTime / FIVE / MIN, (ovenData.cookingTime / FIVE) % MIN);
            sprintf(tempdata, " ");
        }
            
    } else if ((ovenData.state DEQUAL COOKING) OR (ovenData.state DEQUAL RESET_PENDING)) {
        
        // SITUATION FOR TOAST
        if (ovenData.mode DEQUAL TOAST) {
            sprintf(TopOven, "|%s%s%s%s%s|", OVEN_TOP_OFF, OVEN_TOP_OFF, OVEN_TOP_OFF, OVEN_TOP_OFF, OVEN_TOP_OFF);
            sprintf(BottomOven, "|%s%s%s%s%s|", OVEN_BOTTOM_ON, OVEN_BOTTOM_ON, OVEN_BOTTOM_ON, OVEN_BOTTOM_ON, OVEN_BOTTOM_ON);
        }
        // SITUATION FOR BAKE
        else if (ovenData.mode DEQUAL BAKE) {
            sprintf(TopOven, "|%s%s%s%s%s|", OVEN_TOP_ON, OVEN_TOP_ON, OVEN_TOP_ON, OVEN_TOP_ON, OVEN_TOP_ON);
            sprintf(BottomOven, "|%s%s%s%s%s|", OVEN_BOTTOM_ON, OVEN_BOTTOM_ON, OVEN_BOTTOM_ON, OVEN_BOTTOM_ON, OVEN_BOTTOM_ON);
        }
        // EVERYTHING ELSE
        else {
            sprintf(TopOven, "|%s%s%s%s%s|", OVEN_TOP_ON, OVEN_TOP_ON, OVEN_TOP_ON, OVEN_TOP_ON, OVEN_TOP_ON);
            sprintf(BottomOven, "|%s%s%s%s%s|", OVEN_BOTTOM_OFF, OVEN_BOTTOM_OFF, OVEN_BOTTOM_OFF, OVEN_BOTTOM_OFF, OVEN_BOTTOM_OFF);
        }
        
        //IF OVEN EQUALS BROIL
        if (ovenData.mode DEQUAL BROIL)
            sprintf(tempdata, " TEMP: 500%sF", DEGREE_SYMBOL);
        else if ((ovenData.mode) DEQUAL (TOAST))
            sprintf(tempdata, " ");
        else
            sprintf(tempdata, " TEMP: %d%sF", ovenData.temp, DEGREE_SYMBOL);
        
        sprintf(temptime, " TIME: %d:%02d", ovenData.cookingTime / FIVE / MIN, (ovenData.cookingTime / FIVE) % MIN);
    }
    
    if (ovenData.mode DEQUAL BAKE)
        diffmode = "MODE: BAKE";
    else if (ovenData.mode DEQUAL TOAST) 
        diffmode = "MODE: TOAST";
    else
        diffmode = "MODE: BROIL";
    
    sprintf(string, "%s %s\n%s %s\n%s %s\n%s", TopOven, diffmode, OvenLine2, temptime, OvenLine1, tempdata, BottomOven);

    OledClear(OLED_COLOR_BLACK);
    OledDrawString(string);
    OledUpdate();
}
    

/*This function will execute your state machine.  
 * It should ONLY run if an event flag has been set.*/
void runOvenSM(void){
    // Print Variables
    printf( "TIME: %d:%02d", ovenData.cookingTime / FIVE / MIN, (ovenData.cookingTime / FIVE) % MIN);
    
    //Declare Variables
    uint16_t value_adc = AdcRead();

    
    //write your SM logic here.
    switch (ovenData.state) {
        // CASE FOR SETUP
        case SETUP:
            if (Change_Adc) {
                if (ovenData.select DEQUAL TEMP) {
                    ovenData.temp EQUAL (value_adc DIVIDE 4) ADD DEGREE;
                }
                else {
                    ovenData.cookingTime EQUAL (value_adc DIVIDE 4) MULTIPLY (FIVE ADD FIVE);
                }
                updateOvenOLED(ovenData);
            }
           
            if (buttonDown3) {
                ovenData.state = SELECTOR_CHANGE_PENDING;
            }
            if (buttonDown4) {
                ovenData.initialTime EQUAL ovenData.cookingTime;
                ovenData.state EQUAL COOKING;
                updateOvenOLED(ovenData);
                LEDS_SET(0b11111111);
            }
            break;
            
        // CASE FOR COOKING    
        case COOKING:
            if (TimerTick) {
                ovenData.cookingTime--;
                if (ovenData.cookingTime > 0) {
                    UPDATELED(ovenData);
                    updateOvenOLED(ovenData);
                }
                else {
                    ovenData.cookingTime EQUAL ovenData.initialTime;
                    LEDS_SET(0b00000000);
                    ovenData.state EQUAL ALERT;
                    updateOvenOLED(ovenData);
                   
                    blinkTime EQUAL 0;
                    blinkingE EQUAL 1;         
                }
            }
            if (buttonDown4)
                ovenData.state = RESET_PENDING;
            break;
            
        // CASE FOR SELECTORCHANGEPENDING    
        case SELECTOR_CHANGE_PENDING:
            if (buttonUp3) {
                ovenData.presstime EQUAL TimeFree SUB TimeStart;
                
                if (ovenData.presstime LESSTHAN FIVE1) {
                    ovenData.mode++;
                    ovenData.mode %= 3;
                }
                else {
                    ovenData.select++;
                    ovenData.select %= 2;    
                }
                updateOvenOLED(ovenData);
            }
            ovenData.state EQUAL SETUP;
            break;
            
        // CASE FOR ALERT    
        case ALERT:
            if (blinkingE DEQUAL blink) {
                if(conblink DEQUAL 0) {
                    OledSetDisplayInverted();
                    conblink EQUAL 1;
                }
                else {
                    OledSetDisplayNormal();
                    conblink EQUAL 0;
                }
            }
            
            if (buttonDown4) {
                ovenData.state EQUAL SETUP;
                OledSetDisplayNormal();
                blinkTime EQUAL 0;
                blinkingE EQUAL 0;
                updateOvenOLED(ovenData);
            }
        // CASE FOR RESETPENDING    
        case RESET_PENDING:
            if (TimerTick) {
                ovenData.cookingTime--;
                if (ovenData.cookingTime GREATERTHAN 0) {
                    UPDATELED(ovenData);
                    updateOvenOLED(ovenData);
                }
                else {
                    ovenData.cookingTime EQUAL ovenData.initialTime;
                    LEDS_SET(0b00000000);
                    ovenData.state EQUAL ALERT;
                    updateOvenOLED(ovenData);
                    
                    blinkTime EQUAL 0;
                    blinkingE EQUAL 1;
                }
            }
            ovenData.presstime EQUAL TimeFree SUB TimeStart;
            if (ovenData.presstime GREATERTHANE FIVE1) {
                ovenData.state EQUAL SETUP;
                LEDS_SET(0b00000000);
                ovenData.cookingTime EQUAL ovenData.initialTime;
                updateOvenOLED(ovenData);
            }
            else if (buttonUp4)
                ovenData.state EQUAL COOKING; 
            break;
            
        // DEFAULT CASE :D    
        default:
            printf("ERROR.\n");
    }
}


int main()
{
    BOARD_Init();

     //initalize timers and timer ISRs:
    // <editor-fold defaultstate="collapsed" desc="TIMER SETUP">
    
    // Configure Timer 2 using PBCLK as input. We configure it using a 1:16 prescalar, so each timer
    // tick is actually at F_PB / 16 Hz, so setting PR2 to F_PB / 16 / 100 yields a .01s timer.

    T2CON = 0; // everything should be off
    T2CONbits.TCKPS = 0b100; // 1:16 prescaler
    PR2 = BOARD_GetPBClock() / 16 / 100; // interrupt at .5s intervals
    T2CONbits.ON = 1; // turn the timer on

    // Set up the timer interrupt with a priority of 4.
    IFS0bits.T2IF = 0; //clear the interrupt flag before configuring
    IPC2bits.T2IP = 4; // priority of  4
    IPC2bits.T2IS = 0; // subpriority of 0 arbitrarily 
    IEC0bits.T2IE = 1; // turn the interrupt on

    // Configure Timer 3 using PBCLK as input. We configure it using a 1:256 prescaler, so each timer
    // tick is actually at F_PB / 256 Hz, so setting PR3 to F_PB / 256 / 5 yields a .2s timer.

    T3CON = 0; // everything should be off
    T3CONbits.TCKPS = 0b111; // 1:256 prescaler
    PR3 = BOARD_GetPBClock() / 256 / 5; // interrupt at .5s intervals
    T3CONbits.ON = 1; // turn the timer on

    // Set up the timer interrupt with a priority of 4.
    IFS0bits.T3IF = 0; //clear the interrupt flag before configuring
    IPC3bits.T3IP = 4; // priority of  4
    IPC3bits.T3IS = 0; // subpriority of 0 arbitrarily 
    IEC0bits.T3IE = 1; // turn the interrupt on;

    // </editor-fold>
   
    printf("Welcome to 1828506's Lab07 (Toaster Oven).  Compiled on %s %s.", __TIME__, __DATE__);

    //initialize state machine (and anything else you need to init) here
    
    // DECLARE EVENTS
    ovenData.state EQUAL SETUP;
    ovenData.mode EQUAL BAKE;
    ovenData.temp EQUAL 350;
    ovenData.cookingTime EQUAL FIVE;
    ovenData.initialTime EQUAL FIVE;
    ovenData.presstime EQUAL 0;
    ovenData.select EQUAL TIME;
    
    // INITIALIZE
    OledInit();
    AdcInit();
    LEDS_INIT();
    ButtonsInit();
    
    while (1){
        // Add main loop code here:
        // check for events
        if (buttonDown3 OR buttonUp3 OR buttonDown4 OR buttonUp4 OR Change_Adc OR (ovenData.state DEQUAL COOKING) OR (ovenData.state DEQUAL RESET_PENDING) OR blink OR ((TimerTick DAND COOKING) OR (ovenData.state DEQUAL RESET_PENDING))) {
            // on event, run runOvenSM()
            runOvenSM();
            
            // clear event flags
            blink EQUAL 0;
            buttonUp3 EQUAL 0;
            buttonDown3 EQUAL 0;
            buttonUp4 EQUAL 0;
            buttonDown4 EQUAL 0;
            Change_Adc EQUAL 0;
            TimerTick EQUAL 0;
        } 
    }
    
    while(1);
}


/*The 5hz timer is used to update the free-running timer and to generate TIMER_TICK events*/
void __ISR(_TIMER_3_VECTOR, ipl4auto) TimerInterrupt5Hz(void)
{
    // Clear the interrupt flag.
    IFS0CLR = 1 << 12;
    
    // Sets TimerTick to True by a numerical 1 value
    TimerTick = 1;
    // Increment TimeFree
    TimeFree++;
}


/*The 100hz timer is used to check for button and ADC events*/
void __ISR(_TIMER_2_VECTOR, ipl4auto) TimerInterrupt100Hz(void)
{
    // Clear the interrupt flag.
    IFS0CLR = 1 << 8;
    
    buttonEvent = ButtonsCheckEvents();
    
    if (ovenData.state NOEQUAL COOKING) {
        if(AdcChanged()) {
            Change_Adc EQUAL 1;
        }
        if (BUTTON_EVENT_3DOWN AND buttonEvent) {
            TimeStart EQUAL TimeFree;
            buttonDown3 EQUAL 1;   
        }
        if (BUTTON_EVENT_3UP AND buttonEvent) {
            buttonUp3 EQUAL 1;
        }
    }
    
    if (BUTTON_EVENT_4DOWN AND buttonEvent) {
        TimeStart EQUAL TimeFree;
        buttonDown4 EQUAL 1;
    }
    if (BUTTON_EVENT_4UP AND buttonEvent) {
        buttonUp4 EQUAL 1;
    }
    
    if (blinkingE DEQUAL 1) {
        blinkTime++;
        if ((blinkTime EQUAL 50) OR (blinkTime EQUAL 0)) {
            blink EQUAL 1;
            blinkTime EQUAL 0;
        }
    }        
    //add event-checking code here
}