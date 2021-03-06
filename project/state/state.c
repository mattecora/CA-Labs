#include "state.h"

/* Set the semaphore initial state */
state_t Current_State = STATE_RG;

/* Set the blind flag */
blind_t Blind_State = NO_BLIND;

/* Set the maintenance flag */
maint_t Maint_State = NO_MAINT; 

/* Set the vector of state handlers */
void (*Run_State[4])(void) = {Run_State0, Run_State1, Run_State2, Run_State3};

void Run_State0(void)
{
    /* Reset the main timer */
    Timer_Reset(TIMER0);
    
    /* Set the current state */
    Current_State = STATE_RG;

    /* Set the semaphore lights */
    LED_Out(CAR_RED | PED_GREEN);

    /* Setup main timer to match on 15s */
    Timer_SetMatch(TIMER0, TIMER_MATCH0, TIMER_IRS);
    Timer_SetMatch(TIMER0, TIMER_MATCH1, TIMER_NOP);
    
    /* Setup blinking timer to match on 1s */
    Timer_SetMatch(TIMER1, TIMER_MATCH0, TIMER_INT | TIMER_RST);
    Timer_SetMatch(TIMER1, TIMER_MATCH1, TIMER_NOP);
    
    /* Start the main timer */
    Timer_Start(TIMER0);
    
    /* Start the blinking timer */
    Timer_Start(TIMER1);
    
    /* Start the maintenance timer */
    Timer_Start(TIMER3);
}

void Run_State1(void)
{
    /* Reset the main timer */
    Timer_Reset(TIMER0);
    
    /* Reset the blinking timer */
    Timer_Reset(TIMER1);
    
    /* Reset the maintenance timer */
    Timer_Reset(TIMER3);
    
    /* Set the current state */
    Current_State = STATE_RFG;

    /* Set the semaphore lights */
    LED_Out(CAR_RED | PED_GREEN);

    if (Blind_State == BLIND)
    {
        /* Play the first sample */
        DAC_Play();
        
        /* Start the play timer */
        Timer_Start(TIMER2);
    }

    /* Setup main timer to match on 5s */
    Timer_SetMatch(TIMER0, TIMER_MATCH0, TIMER_NOP);
    Timer_SetMatch(TIMER0, TIMER_MATCH1, TIMER_IRS);
    
    /* Setup blinking timer to match on 0.5s */
    Timer_SetMatch(TIMER1, TIMER_MATCH0, TIMER_NOP);
    Timer_SetMatch(TIMER1, TIMER_MATCH1, TIMER_INT | TIMER_RST);
    
    /* Start the main timer */
    Timer_Start(TIMER0);

    /* Start the blinking timer */
    Timer_Start(TIMER1);
}

void Run_State2(void)
{
    /* Reset the main timer */
    Timer_Reset(TIMER0);
    
    /* Reset the blinking timer */
    Timer_Reset(TIMER1);
    
    /* Reset the play timer */
    Timer_Reset(TIMER2);
    
    /* Reset the DAC output */
    DAC_Out(0);
    
    /* Set the current state */
    Current_State = STATE_GR;
    
    /* Reset the blind flag */
    Blind_State = NO_BLIND;

    /* Set the semaphore lights */
    LED_Out(CAR_GREEN | PED_RED);
}

void Run_State3(void)
{
    /* Reset the main timer */
    Timer_Reset(TIMER0);
    
    /* Set the current state */
    Current_State = STATE_YR;

    /* Set the semaphore lights */
    LED_Out(CAR_YELLOW | PED_RED);

    /* Start the main timer */
    Timer_Start(TIMER0);
}

void Run_Maint(void)
{
    /* Reset the main timer */
    Timer_Reset(TIMER0);
    
    /* Reset the blinking timer */
    Timer_Reset(TIMER1);
    
    /* Disable interrupts from buttons */
    NVIC_DisableIRQ(EINT0_IRQn);
    NVIC_DisableIRQ(EINT1_IRQn);
    NVIC_DisableIRQ(EINT2_IRQn);
    
    /* Set maintenance flag */
    Maint_State = MAINT;
    
    /* Set the semaphore lights */
    LED_Out(CAR_YELLOW | PED_RED);
    
    /* Play first sample */
    DAC_Play();
    
    /* Start the play timer */
    Timer_Start(TIMER2);
    
    /* Start the blinking timer */
    Timer_Start(TIMER1);
    
    /* Start ADC conversion */
    ADC_Start();
}

void Run_NoMaint(void)
{   
    /* Stop ADC conversion */
    ADC_Stop();
    
    /* Reset maintenance flag */
    Maint_State = NO_MAINT;
    
    /* Stop playing if not blind */
    if (Blind_State == NO_BLIND)
    {
        /* Stop the play timer */
        Timer_Reset(TIMER2);
        
        /* Reset the DAC output */
        DAC_Out(0);
    }
    
    /* Enable interrupts for buttons */
    NVIC_EnableIRQ(EINT0_IRQn);
    NVIC_EnableIRQ(EINT1_IRQn);
    NVIC_EnableIRQ(EINT2_IRQn);
    
    /* Return to the initial state */
    Run_State[STATE_RG]();
}
