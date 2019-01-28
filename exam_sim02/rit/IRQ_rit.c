#include "rit.h"

/* Global variables definition */
int n, v[N];

void RIT_IRQHandler(void)
{
    int joy_val, of_res;
    static int down = 0;
    
    /* Poll joystick value */
    joy_val = Joystick_Get();
    
    /* Check if joystick is pressed up */
    if (joy_val == JOY_UP)
    {
        /* Pressure not yet managed */
        if (down == 0)
        {
            /* Set TC value in v[n] and increment */
            v[n++] = LPC_TIM1->TC;
            
            if (n == N)
            {
                /* Call overflow() */
                of_res = overflow(v, N);
                
                /* Update LEDs */
                switch (of_res)
                {
                case 0:
                    /* Turn on LED 10 */
                    LED_Out((LED_Value & 0xF8) | 0x2);
                    break;
                case 1:
                    /* Turn on LED 9 */
                    LED_Out((LED_Value & 0xF8) | 0x4);
                    break;
                case 2:
                    LED_Out((LED_Value & 0xF8) | 0x1);
                    break;
                }
                
                /* Reset n */
                n = 0;
            }
        }
        
        /* Increment down */
        down++;
    }
    else
    {
        /* Stop timer 0 */
        Timer_Reset(TIMER0);
        
        /* Turn off LED 4 */
        LED_Off(7);
        
        /* Reset down */
        down = 0;
    }
    
    /* Check if the joystick has been pulled for 3 sec (60 * 50 ms) */
    if (down == 60)
    {
        /* Turn on LED 4 */
        LED_On(7);
        
        /* Start timer 0 */
        Timer_Start(TIMER0);
    }
    
    /* Clear interrupt flag */
    LPC_RIT->RICTRL |= 0x1;
}
