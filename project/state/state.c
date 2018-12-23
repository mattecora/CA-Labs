#include "state.h"

state_t current_state = STATE_RG;

void (*Run_State[4])(void) = {Run_State0, Run_State1, Run_State2, Run_State3};

void Run_State0(void) {
    // Set the current state
    current_state = STATE_RG;
    
    // Set the semaphore lights
    LED_Out(CAR_RED | PED_GREEN);
    
    // Start a 15s timer
    Timer_Init(0, 3*TIME_5SEC, IRS_ON_MATCH);
    Timer_Start(0);
}

void Run_State1(void) {
    // Set the current state
    current_state = STATE_RFG;
    
    // Set the semaphore lights
    LED_Out(CAR_RED | PED_GREEN);
    
    // Start blinking via RIT
    RIT_Enable();
    
    // Start a 5s timer
    Timer_Init(0, TIME_5SEC, IRS_ON_MATCH);
    Timer_Start(0);
}

void Run_State2(void) {
    // Set the current state
    current_state = STATE_GR;
    
    // Set the semaphore lights
    LED_Out(CAR_GREEN | PED_RED);
    
    // Disable blinking via RIT
    RIT_Disable();
    
    // Stop the timer
    Timer_Stop(0);
}

void Run_State3(void) {
    // Set the current state
    current_state = STATE_YR;
    
    // Set the semaphore lights
    LED_Out(CAR_YELLOW | PED_RED);
    
    // Start a 5s timer
    Timer_Init(0, TIME_5SEC, IRS_ON_MATCH);
    Timer_Start(0);
}
