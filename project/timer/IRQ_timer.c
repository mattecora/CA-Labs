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
    /* Maintenance state */
    if (Maint_State == MAINT)
    {
        /* Toggle LEDs state */
        if (LED_Value == (CAR_YELLOW | PED_RED))
        {
            /* Turn off if on */
            LED_Out(LED_NONE);
            
            /* Stop the play timer */
            Timer_Reset(TIMER2);
            
            /* Reset the DAC output */
            DAC_Out(0);
        }
        else if (LED_Value == LED_NONE)
        {
            /* Turn on if off */
            LED_Out(CAR_YELLOW | PED_RED);
            
            /* Play first sample */
            DAC_Play();
            
            /* Start the play timer */
            Timer_Start(TIMER2);
        }
    }
    
    /* Green state */
    else if (Current_State == STATE_RG && Blind_State == BLIND)
    {
        /* Check whether the play timer is running */
        if (LPC_TIM2->TCR != 1)
        {
            /* Play first sample */
            DAC_Play();
            
            /* Start the play timer */
            Timer_Start(TIMER2);
        }
        else
        {
            /* Stop the play timer */
            Timer_Reset(TIMER2);
            
            /* Reset the DAC output */
            DAC_Out(0);
        }
    }
    
    /* Flashing green state */
    else if (Current_State == STATE_RFG)
    {
        if (LED_Value == (CAR_RED | PED_GREEN))
        {
            /* Turn off the LED if on */
            LED_Out(CAR_RED);
            
            if (Blind_State == BLIND)
            {
                /* Stop the play timer */
                Timer_Reset(TIMER2);
                
                /* Reset the DAC output */
                DAC_Out(0);
            }
        }
        else if (LED_Value == CAR_RED)
        {
            /* Turn on if off */
            LED_Out(CAR_RED | PED_GREEN);
            
            if (Blind_State == BLIND)
            {
                /* Play first sample */
                DAC_Play();
                
                /* Start the play timer */
                Timer_Start(TIMER2);
            }
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
    uint8_t joy_val;
    
    /* Poll joystick value */
    joy_val = Joystick_Get();
    
    if (Maint_State == NO_MAINT && joy_val == JOY_RIGHT)
    {
        /* Enter maintenance mode */
        Run_Maint();
    }
    
    if (Maint_State == MAINT)
    {
        if (joy_val == JOY_LEFT)
        {
            /* Exit maintenance mode */
            Run_NoMaint();
        }
        else
        {
            /* Read next ADC value */
            ADC_Start();
        }
    }
    
    /* Clear interrupt flags */
    LPC_TIM3->IR = 7;
}
