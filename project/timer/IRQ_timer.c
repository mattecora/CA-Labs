#include "timer.h"

void TIMER0_IRQHandler(void)
{
    /* Switch to the next state */
    Run_State[(Current_State + 1) % (STATE_YR + 1)]();

    /* Clear interrupt flags */
    LPC_TIM0->IR = 7;
}

void TIMER1_IRQHandler(void)
{
    static uint8_t playing = 0;
    
    /* If in flashing green state, toggle LED state */
    if (Current_State == STATE_RFG)
    {
        if (LED_Value == (CAR_RED | PED_GREEN))
        {
            /* Turn off if on */
            LED_Out(CAR_RED);
        }
        else if (LED_Value == CAR_RED)
        {
            /* Turn on if off */
            LED_Out(CAR_RED | PED_GREEN);
        }
    }
    
    /* If in blind mode, start/stop sound */
    if (Blind_State == BLIND)
    {
        if (playing)
        {
            /* Play first sample */
            DAC_Play();
            
            /* Start the play timer */
            Timer_Start(TIMER2);
            
            playing = 0;
        }
        else
        {
            /* Stop the play timer */
            Timer_Reset(TIMER2);
            
            /* Reset the DAC output */
            DAC_Out(0);
            
            playing = 1;
        }
    }

    /* Clear interrupt flags */
    LPC_TIM1->IR = 7;
}

void TIMER2_IRQHandler(void)
{
    /* Play next sample */
    DAC_Play();
    
    /* Clear interrupt flags */
    LPC_TIM2->IR = 7;
}

void TIMER3_IRQHandler(void)
{
    /* Clear interrupt flags */
    LPC_TIM3->IR = 7;
}
