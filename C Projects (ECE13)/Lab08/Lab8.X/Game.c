 /*********************************************************************************
 Name: Shota Tonari
 Cruz ID: 1828506
 ECE13
 *********************************************************************************/

// Standard Libraries
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

// ECE13 Libraries
#include "Game.h"
#include "Player.h"
#include "UNIXBOARD.h"

// Definitions
#define EQUAL =
#define DEQUAL ==
#define NEQUAL !=
#define OR |=
#define AND &
#define DAND &&
#define ADD +
#define SUB -
#define MUL *
#define DIV /
#define FOUR 4

// Structs
struct room {
    char description[GAME_MAX_ROOM_DESC_LENGTH + 1];
    char title[GAME_MAX_ROOM_TITLE_LENGTH + 1];
    uint8_t south;
    uint8_t north;
    uint8_t west;
    uint8_t east;
} roomI;

static uint8_t room;
static FILE *gamefile;
static char fileName[25];

/**
 * These function transitions between rooms. Each call should return SUCCESS if the current room has
 * an exit in the correct direction and the new room was able to be loaded, and STANDARD_ERROR
 * otherwise.
 * @return SUCCESS if the room CAN be navigated to and changing the current room to that new room
 *         succeeded.
 */

int Open(uint8_t room);
int Open(uint8_t room){
    sprintf(fileName, "RoomFiles/room%d.txt", room);
    gamefile = fopen(fileName,"r"); 
    if(gamefile DEQUAL NULL) {
        return STANDARD_ERROR;
    }
    
    fseek(gamefile, 3, SEEK_SET);
    uint8_t titles = fgetc(gamefile);
    fread(roomI.title, titles, 1, gamefile);
    roomI.title[titles]='\0';
    
    // While Loop
    while(1){
        int x;
        uint8_t length = fgetc(gamefile);      
        uint8_t variable = 0;
        for(x = 0; x < length; x++){
            if(FindInInventory(fgetc(gamefile))){
                variable++;
            }
        }
        
        if(variable != length) {
            uint8_t desc = fgetc(gamefile);
            fseek(gamefile, desc, SEEK_CUR);
            uint8_t item = fgetc(gamefile);
            fseek(gamefile, item + FOUR, SEEK_CUR);
            continue;
        }
        uint8_t desc = fgetc(gamefile);
        fread(roomI.description, desc, 1, gamefile);
        roomI.description[desc]='\0';
        uint8_t varlength = fgetc(gamefile);
        
        for(x = 0; x < varlength; x++){
            if(!AddToInventory(fgetc(gamefile))){
                return STANDARD_ERROR;
            }
        }
        // Call fgetc for N, E, S, W 
        roomI.north=fgetc(gamefile);
        roomI.east=fgetc(gamefile);
        roomI.south=fgetc(gamefile);
        roomI.west=fgetc(gamefile);
        
        // Call fclose gamefile
        fclose(gamefile);
        // Return Success
        return SUCCESS;
        break;
    // Otherwise return STANDARD_ERROR
    }
    return STANDARD_ERROR;
}



int GameGoNorth(void) {
    if (roomI.north) {
        Open(roomI.north);
        return SUCCESS;
    }
    return STANDARD_ERROR;
}

/**
 * @see GameGoNorth
 */
int GameGoEast(void){
    if (roomI.east) {
        Open(roomI.east);
        return SUCCESS;
    }
    return STANDARD_ERROR;
}

/**
 * @see GameGoNorth
 */
int GameGoSouth(void){
    if (roomI.south) {
        Open(roomI.south);
        return SUCCESS;
    }
    return STANDARD_ERROR;
}

/**
 * @see GameGoNorth
 */
int GameGoWest(void){
    if (roomI.west) {
        Open(roomI.west);
        return SUCCESS;
    }
    return STANDARD_ERROR;
}

/**
 * This function sets up anything that needs to happen at the start of the game. This is just
 * setting the current room to STARTING_ROOM and loading it. It should return SUCCESS if it succeeds
 * and STANDARD_ERROR if it doesn't.
 * @return SUCCESS or STANDARD_ERROR
 */
int GameInit(void){
    uint8_t PASS EQUAL Open(STARTING_ROOM);
    if (PASS DEQUAL SUCCESS) {
        return SUCCESS;
    } else {
        return STANDARD_ERROR;
    }
}
/**
 * Copies the current room title as a NULL-terminated string into the provided character array.
 * Only a NULL-character is copied if there was an error so that the resultant output string
 * length is 0.
 * @param title A character array to copy the room title into. Should be GAME_MAX_ROOM_TITLE_LENGTH+1
 *             in length in order to allow for all possible titles to be copied into it.
 * @return The length of the string stored into `title`. Note that the actual number of chars
 *         written into `title` will be this value + 1 to account for the NULL terminating
 *         character.
 */
int GameGetCurrentRoomTitle(char *title){
    strcpy(title, roomI.title);
    return strlen(title);
}

/**
 * GetCurrentRoomDescription() copies the description of the current room into the argument desc as
 * a C-style string with a NULL-terminating character. The room description is guaranteed to be less
 * -than-or-equal to GAME_MAX_ROOM_DESC_LENGTH characters, so the provided argument must be at least
 * GAME_MAX_ROOM_DESC_LENGTH + 1 characters long. Only a NULL-character is copied if there was an
 * error so that the resultant output string length is 0.
 * @param desc A character array to copy the room description into.
 * @return The length of the string stored into `desc`. Note that the actual number of chars
 *          written into `desc` will be this value + 1 to account for the NULL terminating
 *          character.
 */
int GameGetCurrentRoomDescription(char *desc){
    strcpy(desc, roomI.description);
    return strlen(desc);
}

/**
 * This function returns the exits from the current room in the lowest-four bits of the returned
 * uint8 in the order of NORTH, EAST, SOUTH, and WEST such that NORTH is in the MSB and WEST is in
 * the LSB. A bit value of 1 corresponds to there being a valid exit in that direction and a bit
 * value of 0 corresponds to there being no exit in that direction. The GameRoomExitFlags enum
 * provides bit-flags for checking the return value.
 *
 * @see GameRoomExitFlags
 *
 * @return a 4-bit bitfield signifying which exits are available to this room.
 */

uint8_t GameGetCurrentRoomExits(void) {
    uint8_t CurrentRoomExit EQUAL 0b0000;
    if (roomI.east) {
        CurrentRoomExit OR GAME_ROOM_EXIT_EAST_EXISTS; 
    }
    if (roomI.west) {
        CurrentRoomExit OR GAME_ROOM_EXIT_WEST_EXISTS;
    }
    if (roomI.north) {
        CurrentRoomExit OR GAME_ROOM_EXIT_NORTH_EXISTS;
    }
    if (roomI.south) {
        CurrentRoomExit OR GAME_ROOM_EXIT_SOUTH_EXISTS;
    }
    return CurrentRoomExit;
}