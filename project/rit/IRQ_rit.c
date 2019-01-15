#include "rit.h"

/* Button to debounce */
uint8_t Debounce_Key;

void Handle_Req(void)
{
    switch (Current_State)
    {
    case STATE_RG:
        /* Reset the main timer */
        Timer_Reset(TIMER0);
    
        /* Start the main timer */
        Timer_Start(TIMER0);
        break;

    case STATE_RFG:
        /* Reset the blink timer */
        Timer_Reset(TIMER1);
    
        /* Reset the main timer */
        Timer_Reset(TIMER0);
    
        /* Switch to the previous state */
        Run_State[STATE_RG]();
        break;

    case STATE_GR:
        /* Start the main timer */
        Timer_Start(TIMER0);
        break;

    case STATE_YR:
        /* Nop */
        break;
    }
}

void RIT_IRQHandler(void)
{
    static int down = 0;
    
    /* Check button status */
    if ((LPC_GPIO2->FIOPIN & (Debounce_Key << 10)) == 0)
    {
        /* Button is pressed */
        down = 1;
    }
    else
    {
        /* Button has been released */
        if (down == 1)
        {
            /* Handle pedestrian request */
            Handle_Req();
            
            /* Stop playing */
            if (Debounce_Key == BUTTON_INT0)
            {
                /* Reset the play timer */
                Timer_Reset(TIMER2);
                
                /* Reset the DAC output */
                DAC_Out(0);
            }
        }
        
        /* Button is not pressed */
        down = 0;
        
        /* Disable and reset the RIT */
        RIT_Disable();
        RIT_Reset();
        
        /* Restart the main timer */
        Timer_Start(TIMER0);
        
        /* Restart the blinking timer */
        Timer_Start(TIMER1);
        
        /* Restart the maintenance timer */
        if (Current_State == STATE_RG)
            Timer_Start(TIMER3);
        
        /* Switch back to interrupt mode */
        LPC_PINCON->PINSEL4 |= ((Debounce_Key & BUTTON_INT0) | 
                           ((Debounce_Key & BUTTON_KEY1) << 1) | 
                           ((Debounce_Key & BUTTON_KEY2) << 2)) << 20;
    }
    
    /* Clear interrupt flag */
    LPC_RIT->RICTRL |= 0x1;
}
