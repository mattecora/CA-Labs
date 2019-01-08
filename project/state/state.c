#include "state.h"

/* Set the semaphore initial state */
state_t current_state = STATE_RG;

/* Set the vector of state handlers */
void (*Run_State[4])(void) = {Run_State0, Run_State1, Run_State2, Run_State3};

void Run_State0(void)
{
    if (current_state == STATE_RFG)
    {
        /* Reset the blinking timer (if coming from STATE_RFG) */
        Timer_Reset(TIMER1);

        /* Reset the main timer (if coming from STATE_RFG) */
        Timer_Reset(TIMER0);
    }
    
    /* Set the current state */
    current_state = STATE_RG;

    /* Set the semaphore lights */
    LED_Out(CAR_RED | PED_GREEN);

    /* Match on 15s */
    Timer_SetMCR(TIMER0, TIMER_MATCH0, TIMER_IRS);
    Timer_SetMCR(TIMER0, TIMER_MATCH1, TIMER_NOP);
    
    /* Start the main timer */
    Timer_Start(TIMER0);
}

void Run_State1(void)
{
    /* Set the current state */
    current_state = STATE_RFG;

    /* Set the semaphore lights */
    LED_Out(CAR_RED | PED_GREEN);

    /* Match on 5s */
    Timer_SetMCR(TIMER0, TIMER_MATCH0, TIMER_NOP);
    Timer_SetMCR(TIMER0, TIMER_MATCH1, TIMER_IRS);
    
    /* Start the main timer */
    Timer_Start(TIMER0);

    /* Start the blinking timer */
    Timer_Start(TIMER1);
}

void Run_State2(void)
{
    /* Reset the blinking timer */
    Timer_Reset(TIMER1);
    
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

    /* Start the main timer */
    Timer_Reset(TIMER0);
    Timer_Start(TIMER0);
}
