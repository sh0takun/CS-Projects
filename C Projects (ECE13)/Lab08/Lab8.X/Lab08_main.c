 /*********************************************************************************
 Name: Shota Tonari
 Cruz ID: 1828506
 ECE13
 *********************************************************************************/

// **** Include libraries here ****
// Standard libraries
#include <string.h>
#include <math.h>
#include <stdio.h>

//ECE13 Support Library
#include "UNIXBOARD.h"
#include "Game.h"
#include "Player.h"


    
//**** Define any global or external variables here ****
#define EQUAL =
#define DEQUAL ==
#define NEQUAL !=
#define OR |=
#define LOR ||
#define AND &
#define DAND &&
#define ADD +
#define SUB -
#define MUL *
#define DIV /
#define B 0b0000

// **** Declare any function prototypes here ****

int main()
{
    /******************************** Your custom code goes below here ********************************/
    printf("Welcome to my RPG game!\n");
    int result = GameInit();
    
    if (result == STANDARD_ERROR) {
        FATAL_ERROR();
    }
    char title[GAME_MAX_ROOM_DESC_LENGTH + 1];
    char description[GAME_MAX_ROOM_DESC_LENGTH + 1];
    char inputvariable;
    int C;
    uint8_t exits;
    
    while (1) {
        GameGetCurrentRoomTitle(title);
        printf("\n%s\n", title);
        GameGetCurrentRoomDescription(description);
        printf("\n%s\n", description);
        
        exits = GameGetCurrentRoomExits();
        printf("Possible Exits: ");
        if (exits AND GAME_ROOM_EXIT_EAST_EXISTS) {
            printf("EAST ");
        }
        if (exits AND GAME_ROOM_EXIT_WEST_EXISTS) {
            printf("WEST ");
        }
        if (exits AND GAME_ROOM_EXIT_NORTH_EXISTS) {
            printf("NORTH ");
        }
        if (exits AND GAME_ROOM_EXIT_SOUTH_EXISTS) {
            printf("SOUTH ");
        }
        if (exits == B) {
            printf("Press q to quit.");
        }
        printf("\n");
        
        while(1) {
            printf("\nEnter a direction (n,e,s,w, or q to quit): ");
            inputvariable = getchar();
            if (getchar() != '\n') {
                while (getchar() != '\n');
                printf("ERROR: Invalid Input. Please Try Again.\n");
                continue;
            }
            
            switch (inputvariable) {
                case 'e':
                    C = GameGoEast();
                    if (C DEQUAL STANDARD_ERROR) {
                        printf("East Exit does not exist.\n");
                    }
                    break;
                case 'w':
                    // same as case n
                    C = GameGoWest();
                    if (C DEQUAL STANDARD_ERROR) {
                        printf("West Exit does not exist.\n");
                    }
                    break;
                case 'n':
                    C = GameGoNorth();
                    if (C DEQUAL STANDARD_ERROR) {
                        printf("North Exit does not exist.\n");
                    }
                    break;
                case 's':
                    C = GameGoSouth();
                    if (C DEQUAL STANDARD_ERROR) {
                        printf("South Exit does not exist.\n");
                    }
                    break;
                case 'q':
                    printf("\nYou have quit the game. Thanks for playing!\n");
                    break;
                default:
                    printf("Invalid Entry.\n");
                    break;
            }
            if (inputvariable DEQUAL 'q' || C DEQUAL SUCCESS) {
                break;
            }
        }
        if (inputvariable DEQUAL 'q') {
            exit(SUCCESS);
        }
    }
}


