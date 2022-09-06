/*********************************************************************************
 Name: Shota Tonari
 Cruz ID: 1828506
 ECE13
 *********************************************************************************/

// Standard libraries
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

// ECE13 Support Libraries
#include "Agent.h"
#include "BattleBoats.h"

#define DEQUAL ==

int main() {    
    printf("Test:\n");    
    
    int count = 0;
    
    AgentSetState(AGENT_STATE_START);
    if(AgentGetState() DEQUAL AGENT_STATE_START) count++;
    AgentSetState(AGENT_STATE_CHALLENGING);
    if(AgentGetState() DEQUAL AGENT_STATE_CHALLENGING) count++;
    AgentSetState(AGENT_STATE_ACCEPTING);
    if(AgentGetState() DEQUAL AGENT_STATE_ACCEPTING) count++;
    AgentSetState(AGENT_STATE_ATTACKING);
    if(AgentGetState() DEQUAL AGENT_STATE_ATTACKING) count++;
    AgentSetState(AGENT_STATE_DEFENDING);
    if(AgentGetState() DEQUAL AGENT_STATE_DEFENDING) count++;
    AgentSetState(AGENT_STATE_WAITING_TO_SEND);
    if(AgentGetState() DEQUAL AGENT_STATE_WAITING_TO_SEND) count++;
    AgentSetState(AGENT_STATE_END_SCREEN);
    if(AgentGetState() DEQUAL AGENT_STATE_END_SCREEN) count++;
    if(count DEQUAL 7) printf("SUCCESS\n");
  
    printf("Testing AgentInIt:\n");
    AgentInit();
    if(AgentGetState() == AGENT_STATE_START) printf("SUCCESS\n");    
    
    
    printf("Testing AgentRun:\n");
    count = 0;
    BB_Event event;
    event.type = BB_EVENT_START_BUTTON;
    event.param0 = 0;
    event.param1 = 0;
    event.param2 = 0;
    AgentRun(event);    
    if(AgentGetState() DEQUAL AGENT_STATE_CHALLENGING) count++;        
    if(count DEQUAL 1) 
        printf("\n TEST HAS BEEN COMPLETED. \n");    
    
    while(1);    
}