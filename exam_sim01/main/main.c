#include "../button/button.h"
#include "../led/led.h"
#include "../rit/rit.h"
#include "../timer/timer.h"

int main(void)
{
    /* Initialize buttons */
    Button_Init(BUTTON_ALL);
    
    /* Initialize LEDs */
    LED_Init(LED_NONE);
    
    /* Initialize RIT */
    RIT_Init(TIME_50MS);
    
    /* Initialize timer 2 */
    Timer_Init(TIMER2, TIMER_MATCH0, TIME_PER, TIMER_IRS);
    
    /* Set interrupt priorities */
    NVIC_SetPriority(TIMER2_IRQn, 1);
    NVIC_SetPriority(EINT0_IRQn, 2);
    NVIC_SetPriority(EINT1_IRQn, 3);
    NVIC_SetPriority(EINT2_IRQn, 4);
    
    while (1)
    {
        __ASM("WFI");
    }
}
