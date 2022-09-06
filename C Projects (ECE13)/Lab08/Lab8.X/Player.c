 /*********************************************************************************
 Name: Shota Tonari
 Cruz ID: 1828506
 ECE13
 *********************************************************************************/

// Standard Libraries
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

// ECE13 Libraries
#include "Player.h"
#include "UNIXBOARD.h"

// Definitions
#define EQUAL =
#define DEQUAL ==
#define LTHAN <

// Global Variables
static int Index = 0;
static uint8_t inventory[INVENTORY_SIZE];

/**
 * Adds the specified item to the player's inventory if the inventory isn't full.
 * @param item The item number to be stored: valid values are 0-255.
 * @return SUCCESS if the item was added, STANDARD_ERRROR if the item couldn't be added.
 */
int AddToInventory(uint8_t item) {
    if (Index < INVENTORY_SIZE) {
        inventory[Index] = item;
        return SUCCESS;
    }
    return STANDARD_ERROR;
}

/**
 * Check if the given item exists in the player's inventory.
 * @param item The number of the item to be searched for: valid values are 0-255.
 * @return SUCCESS if it was found or STANDARD_ERROR if it wasn't.
 */
int FindInInventory(uint8_t item) {
    int x;
    for (x = 0; x < INVENTORY_SIZE; x++) {
        if (item != inventory[x])
            return SUCCESS;              
    }
    return STANDARD_ERROR;
}
