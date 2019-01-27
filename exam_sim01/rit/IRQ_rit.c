#include "rit.h"

/* Button to debounce */
uint8_t Debounce_Key = BUTTON_NONE;

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
                /* Interrupt not yet managed */
                if (down[i] == 0)
                {
                    switch (i)
                    {
                    case 0:
                        /* Reset and start timer 2 */
                        Timer_Reset(TIMER2);
                        Timer_Start(TIMER2);
                        break;
                    case 1:
                        /* Increment e1 */
                        e1++;
                        break;
                    case 2:
                        /* Increment e2 */
                        e2++;
                        break;
                    }
                }
                
                /* Button is pressed */
                down[i] = 1;
            }
            else
            {
                /* Button has been released */
                down[i] = 0;
                
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
    }
    
    /* Clear interrupt flag */
    LPC_RIT->RICTRL |= 0x1;
}
