#include "state.h"

/* Set the semaphore initial state */
state_t current_state = STATE_RG;

/* Set the vector of state handlers */
void (*Run_State[4])(void) = {Run_State0, Run_State1, Run_State2, Run_State3};

void Run_State0(void)
{
    if (current_state == STATE_RFG)
    {
        /* Stop the RIT (if coming from STATE_RFG) */
        RIT_Disable();
        RIT_Reset();

        /* Reset the other timer (if coming from STATE_RFG) */
        Timer_Reset(TIMER1);
    }
    
    /* Set the current state */
    current_state = STATE_RG;

    /* Set the semaphore lights */
    LED_Out(CAR_RED | PED_GREEN);

    /* Start the 15s timer */
    Timer_Start(TIMER0);
}

void Run_State1(void)
{
    /* Set the current state */
    current_state = STATE_RFG;

    /* Set the semaphore lights */
    LED_Out(CAR_RED | PED_GREEN);

    /* Start the 5s timer */
    Timer_Start(TIMER1);

    /* Start blinking via RIT */
    RIT_Enable();
}

void Run_State2(void)
{
    /* Stop blinking via RIT */
    RIT_Disable();
    RIT_Reset();

    /* Set the current state */
    current_state = STATE_GR;

    /* Set the semaphore lights */
    LED_Out(CAR_GREEN | PED_RED);
}

void Run_State3(void)
{
    /* Set the current state */
    current_state = STATE_YR;

    /* Set the semaphore lights */
    LED_Out(CAR_YELLOW | PED_RED);

    /* Start the 5s timer */
    Timer_Reset(TIMER1);
    Timer_Start(TIMER1);
}
