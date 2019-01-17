#include "rit.h"

/* Button to debounce */
uint8_t Debounce_Key = BUTTON_NONE;

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
    static int down[3] = {0};
    int i;
    
    for (i = 0; i < 3; i++)
    {
        /* Check if the key should be debounced */
        if (Debounce_Key & (1 << i))
        {
            /* Check button status */
            if ((LPC_GPIO2->FIOPIN & (1 << (10 + i))) == 0)
            {
                if (down[i] == 0)
                {
                    /* Handle pedestrian request */
                    Handle_Req();
                }
                
                /* Button is pressed */
                down[i] = 1;
            }
            else
            {
                /* Button has been released */
                down[i] = 0;
                
                /* Stop playing if blind */
                if (i == 0)
                {            
                    /* Reset the play timer */
                    Timer_Reset(TIMER2);
                    
                    /* Reset the DAC output */
                    DAC_Out(0);
                    
                    /* Reset the blinking timer */
                    Timer_Reset(TIMER1);
                    
                    /* Start the blinking timer */
                    Timer_Start(TIMER1);
                }
                
                /* Remove from the debounce keys */
                Debounce_Key &= ~(1 << i);
                
                /* Switch back to interrupt mode */
                LPC_PINCON->PINSEL4 |= 1 << (20 + 2*i);
            }
        }
    }
    
    /* Check if there are still buttons to debounce */
    if (Debounce_Key == 0)
    {
        /* Disable and reset the RIT */
        RIT_Disable();
        RIT_Reset();
        
        /* Restart the maintenance timer */
        if (Current_State == STATE_RG)
            Timer_Start(TIMER3);
    }
    
    /* Clear interrupt flag */
    LPC_RIT->RICTRL |= 0x1;
}
