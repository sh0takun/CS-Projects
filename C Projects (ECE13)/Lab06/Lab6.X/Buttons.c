/*********************************************************************************
 Name: Shota Tonari
 Cruz ID: 1828506
 ECE13
 *********************************************************************************/


#include <stdint.h>
#include <genericTypeDefs.h>

#include <stdio.h>
#include <stdlib.h>
#include "BOARD.h"
#include "Buttons.h"

// Declare static ints, variables, and counts

static uint8_t debounce = BUTTONS_DEBOUNCE_PERIOD;
// static uint8_t buttonstates = BUTTON_STATES();
static uint8_t eventnone = BUTTON_EVENT_NONE;
// static uint8_t buttonNone;
static uint8_t debouncenumber = 0;
static uint8_t previous = 0;
static uint8_t event = 0;

// Define AND/OR Operators
#define AND &
#define OR |=


void ButtonsInit(void){
    TRISD |= 0x00E0;
    TRISF |= 0x0002;
    previous = 0;
    debouncenumber = 0;
    
}

uint8_t ButtonsCheckEvents(void) {
    // Decrement debounceperiod
    uint8_t buttonstates = BUTTON_STATES();
    
    event = 0;
    
    debounce--;
    if (!debounce) {
        // Button 4
        if ((previous AND BUTTON_STATE_4) != (buttonstates AND BUTTON_STATE_4)) {
            if (buttonstates AND BUTTON_STATE_4)
                event OR BUTTON_EVENT_4DOWN;
            else
                event OR BUTTON_EVENT_4UP;
        }
        // Button 3
        if ((previous AND BUTTON_STATE_3) != (buttonstates AND BUTTON_STATE_3)) {
            if (buttonstates AND BUTTON_STATE_3)
                event OR BUTTON_EVENT_3DOWN;
            else
                event OR BUTTON_EVENT_3UP;
        }
        // Button 2
        if ((previous AND BUTTON_STATE_2) != (buttonstates AND BUTTON_STATE_2)) {
            if (buttonstates AND BUTTON_STATE_2)
                event OR BUTTON_EVENT_2DOWN;
            else
                event OR BUTTON_EVENT_2UP;
        }
        // Button 1
        if ((previous AND BUTTON_STATE_1) != (buttonstates AND BUTTON_STATE_1)) {
            if (buttonstates AND BUTTON_STATE_1)
                event OR BUTTON_EVENT_1DOWN;
            else
                event OR BUTTON_EVENT_1UP;
        }
        // Set Previous status to current button status
        previous = buttonstates;
        // Reset debounce value
        debouncenumber = BUTTONS_DEBOUNCE_PERIOD;
        if (event != 0)
            return event;
    }        
    // Return Button_Event_None
    return eventnone;
}