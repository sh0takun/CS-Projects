/* 
 * File:   part0.c
 * Author: Shota Tonari (stonari@ucsc.edu)
 *
 * Created on January 4, 2022, 7:27 PM
 */

#include <stdio.h>
#include <stdlib.h>

#include "BOARD.h"

/*
 * 
 */
int main(void)
{
    BOARD_Init();
    printf("Hello World\n");
    
    
    BOARD_End(); // handles cleanup of the system
    while(1); // if embedded we should never exit.
}

