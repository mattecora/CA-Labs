#include "state.h"

/* Set the semaphore initial state */
state_t Current_State = STATE_RG;

/* Set the blind flg */
blind_t Blind_State = NO_BLIND;

/* Set the vector of state handlers */
void (*Run_State[4])(void) = {Run_State0, Run_State1, Run_State2, Run_State3};

void Run_State0(void)
{
    if (Current_State == STATE_RFG)
    {
        /* Reset the blinking timer (if coming from STATE_RFG) */
        Timer_Reset(TIMER1);

        /* Reset the main timer (if coming from STATE_RFG) */
        Timer_Reset(TIMER0);
    }
    
    /* Set the current state */
    Current_State = STATE_RG;

    /* Set the semaphore lights */
    LED_Out(CAR_RED | PED_GREEN);

    /* Setup main timer to match on 15s */
    Timer_SetMCR(TIMER0, TIMER_MATCH0, TIMER_IRS);
    Timer_SetMCR(TIMER0, TIMER_MATCH1, TIMER_NOP);
    
    /* Setup blinking timer to match on 1s */
    Timer_SetMCR(TIMER1, TIMER_MATCH0, TIMER_INT | TIMER_RST);
    Timer_SetMCR(TIMER1, TIMER_MATCH1, TIMER_NOP);
    
    /* Start the main timer */
    Timer_Start(TIMER0);
    
    /* Start the blinking timer */
    Timer_Start(TIMER1);
}

void Run_State1(void)
{
    /* Reset the blinking timer */
    Timer_Reset(TIMER1);
    
    /* Set the current state */
    Current_State = STATE_RFG;

    /* Set the semaphore lights */
    LED_Out(CAR_RED);

    /* Setup main timer to match on 5s */
    Timer_SetMCR(TIMER0, TIMER_MATCH0, TIMER_NOP);
    Timer_SetMCR(TIMER0, TIMER_MATCH1, TIMER_IRS);
    
    /* Setup blinking timer to match on 0.5s */
    Timer_SetMCR(TIMER1, TIMER_MATCH0, TIMER_NOP);
    Timer_SetMCR(TIMER1, TIMER_MATCH1, TIMER_INT | TIMER_RST);
    
    /* Start the main timer */
    Timer_Start(TIMER0);

    /* Start the blinking timer */
    Timer_Start(TIMER1);
}

void Run_State2(void)
{
    /* Reset the blinking timer */
    Timer_Reset(TIMER1);
    
    /* Reset the play timer */
    Timer_Reset(TIMER2);
    
    /* Set the current state */
    Current_State = STATE_GR;
    
    /* Reset the blind flag */
    Blind_State = NO_BLIND;

    /* Set the semaphore lights */
    LED_Out(CAR_GREEN | PED_RED);
}

void Run_State3(void)
{
    /* Set the current state */
    Current_State = STATE_YR;

    /* Set the semaphore lights */
    LED_Out(CAR_YELLOW | PED_RED);

    /* Start the main timer */
    Timer_Start(TIMER0);
    
    /* Start the blinking timer */
}
