/*********************************************************************************
 Name: Shota Tonari
 Cruz ID: 1828506
 ECE13
 *********************************************************************************/

// Standard libraries
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "Agent.h"
#include "Field.h"
#include "Oled.h"
#include "Negotiation.h"
#include "BattleBoats.h"

static BB_Event battleboatEvent;

// Initialize different message states
int main() {
    char* MessageState[] = {
        "MESSAGE_REV",
        "MESSAGE_SHO",
        "MESSAGE_NONE",
        "MESSAGE_CHA",
        "MESSAGE_ACC",
        "MESSAGE_RES",
        "MESSAGE_ERROR"
    };
    
    char* states[] = {
        "AGENT_STATE_START",
        "AGENT_STATE_ATTACKING",
        "AGENT_STATE_DEFENDING",
        "AGENT_STATE_CHALLENGING",
        "AGENT_STATE_ACCEPTING",
        "AGENT_STATE_END_SCREEN",
        "AGENT_STATE_WAITING_TO_SEND",
        "AGENT_STATE_SETUP_BOATS"
    };
    
    // Initiate BOARD
    BOARD_Init();
    OledInit();
    AgentInit();

    printf("START AGENT TEST\n");


    printf("Testing Start State\n");
    Message message;
    AgentState currentState = AgentGetState();
    printf("Expect State: AGENT_STATE_START\nTest result: %s\n", states[currentState]);

    printf("Testing Set State\n");
    AgentSetState(AGENT_STATE_DEFENDING);
    currentState = AgentGetState();
    printf("Expected: AGENT_STATE_DEFENDING\nTest result: %s\n", states[currentState]);

    printf("Test Cheat\n");
    AgentSetState(AGENT_STATE_START);
    battleboatEvent.type = BB_EVENT_CHA_RECEIVED;
    battleboatEvent.param0 = 12345;
    message = AgentRun(battleboatEvent);
    currentState = AgentGetState();
    printf("Expected: AGENT_STATE_ACCEPTING\nTest result: %s\n", states[currentState]);
    printf("Message.type = MESSAGE_ACC\n Test result: %s\n", MessageState[message.type]);
    battleboatEvent.type = BB_EVENT_REV_RECEIVED;
    battleboatEvent.param0 = 61;
    message = AgentRun(battleboatEvent);
    currentState = AgentGetState();
    printf("Expected: AGENT_STATE_END_SCREEN\nTest result: %s\n", states[currentState]);
    AgentInit();
    currentState = AgentGetState();
    printf("Expected: AGENT_STATE_START\nTest result: %s\n", states[currentState]);
    
    printf("Test Challenging\n");
    AgentSetState(AGENT_STATE_START);
    battleboatEvent.type = BB_EVENT_START_BUTTON;
    message = AgentRun(battleboatEvent);
    currentState = AgentGetState();
    printf("Expected: AGENT_STATE_CHALLENGING\nTest result: %s\n", states[currentState]);
    printf("Message.type = MESSAGE_CHA\nTest result: %s\n", MessageState[message.type]);

    printf("Testing Win Condition\n");
    AgentSetState(AGENT_STATE_ATTACKING);
    battleboatEvent.param2 = RESULT_SMALL_BOAT_SUNK;
    message = AgentRun(battleboatEvent);
    AgentSetState(AGENT_STATE_ATTACKING);
    battleboatEvent.param2 = RESULT_MEDIUM_BOAT_SUNK;
    message = AgentRun(battleboatEvent);
    AgentSetState(AGENT_STATE_ATTACKING);
    battleboatEvent.param2 = RESULT_LARGE_BOAT_SUNK;
    message = AgentRun(battleboatEvent);
    currentState = AgentGetState();
    printf("Expected: AGENT_STATE_END_SCREEN\nTest result: %s\n", states[currentState]);

    printf("Testing Attack to Defending State\n");
    battleboatEvent.type = BB_EVENT_RES_RECEIVED;
    AgentSetState(AGENT_STATE_ATTACKING);
    battleboatEvent.param2 = RESULT_HUGE_BOAT_SUNK;
    message = AgentRun(battleboatEvent);
    currentState = AgentGetState();
    printf("Expected: AGENT_STATE_DEFENDING\nTest result: %s\n", states[currentState]);
    

    printf("Test Defending Waiting to State Condition\n");
    AgentInit();
    AgentSetState(AGENT_STATE_DEFENDING);
    battleboatEvent.type = BB_EVENT_SHO_RECEIVED;
    battleboatEvent.param2 = RESULT_LARGE_BOAT_SUNK;
    message = AgentRun(battleboatEvent);
    currentState = AgentGetState();
    printf("Expected AGENT_STATE_WAITING_TO_SEND\nTest result: %s\n", states[currentState]);

    while (1);
}
