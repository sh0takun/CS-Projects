/*********************************************************************************
 Name: Shota Tonari
 Cruz ID: 1828506
 ECE13
 *********************************************************************************/


// **** Include libraries here ****
// Standard libraries
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//ECE13 Support Library
#include "BOARD.h"

// User libraries
#include "rpn.h"

// Define magic numbers
#define MAX_INPUT_LENGTH 60

int main() {
    BOARD_Init();

    // What follows is starter code.  You will need to modify it!
    
    // Declare Variables
    char rpn_sentence[MAX_INPUT_LENGTH + 2];
    double result;
    int value, i; // store error value and x to use for increment counter
    
    // Welcome message outside of the while loop. Runs every time the file is compiled.
    printf("Welcome to 1828506'S RPN calculator.  Compiled on %s %s\n", __DATE__, __TIME__);
    
    while (1) {
        // Asks the user to input floats. Performs addition, subtraction, division, and multiplication
        printf("Enter floats and + - / * in RPN format:\n");
        
        // Flush function is used to clear out any stream/buffer
        fflush(stdin);
        // retrieves user input using f gets (for reading string values with spaces), reads up to 60 characters + 2.
        fgets(rpn_sentence, sizeof(rpn_sentence), stdin);
        
        // checks if the size of the input from the user is greater than 60 characters, calls MAX_INPUT_LENGTH
        if (strlen (rpn_sentence) > MAX_INPUT_LENGTH && rpn_sentence[MAX_INPUT_LENGTH] != '\0') {
            rpn_sentence[MAX_INPUT_LENGTH] = '\0';
            printf ("ERROR: You entered more than 60 characters!\n");
            for (i = 0; i < MAX_INPUT_LENGTH + 2; i++){
                rpn_sentence[i] = '\0';
            }
            while (getchar() != '\n');
        }
        
        // Call ProcessBackspaces, and call RPN_Evaluate as long as the string is not too long
        // ProcessBackspaces(rpn_sentence); Didn't finish :(
        value = RPN_Evaluate(rpn_sentence, &result);
        
        // Switch case to call for ERRORS
        switch (value) {
            case RPN_ERROR_TOO_MANY_ITEMS_REMAIN:
                printf("ERROR: Invalid RPN calculation: more than one item in the stack.\n"); 
                break;
            case RPN_ERROR_TOO_FEW_ITEMS_REMAIN:
                printf("ERROR: Invalid RPN calculation: less than one item in the stack.\n"); 
                break;
            case RPN_ERROR_INVALID_TOKEN:
                printf("ERROR: Invalid character in RPN string.\n"); 
                break;
            case RPN_ERROR_DIVIDE_BY_ZERO:
                printf("ERROR: Invalid RPN calculation: divide by zero.\n"); 
                break;
            case RPN_ERROR_STACK_UNDERFLOW:
                printf("ERROR: Not enough operands before operator.\n"); 
                break;
            case RPN_ERROR_STACK_OVERFLOW:
                printf("ERROR: Too many operands\n"); 
                break;   
            default:
                printf("result = %f\n", result);
                break;
        }

    }
    while (1);
}