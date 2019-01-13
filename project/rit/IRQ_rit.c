#include "rit.h"

void RIT_IRQHandler(void)
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
    
    /* Clear interrupt flag */
    LPC_RIT->RICTRL |= 0x1;
}
