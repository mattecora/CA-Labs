#include "rit.h"

uint8_t Pressed_Button;

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
    if ((LPC_GPIO2->FIOPIN & (1 << (10 + Pressed_Button))) == 0)
    {
        if (down == 0)
        {
            /* Button pressed */
            down = 1;
        }
    }
    else
    {
        /* Button not pressed */
        down = 0;
            
        /* Handle request */
        Handle_Req();
        
        /* Disable the RIT */
        RIT_Disable();
        
        /* Stop playing */
        if (Pressed_Button == 0)
        {
            /* Reset the play timer */
            Timer_Reset(TIMER2);
            
            /* Reset the DAC output */
            DAC_Out(0);
        }
        
        /* Restart timers */
        Timer_Start(TIMER0);
        Timer_Start(TIMER1);
        
        /* Switch back to interrupt mode */
        LPC_PINCON->PINSEL4 |= 1 << (20 + 2*Pressed_Button);
    }
    
    /* Clear interrupt flag */
    LPC_RIT->RICTRL |= 0x1;
}
