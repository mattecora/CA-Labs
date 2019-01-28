#include "LPC17xx.h"

#include "../joystick/joystick.h"
#include "../led/led.h"
#include "../rit/rit.h"
#include "../timer/timer.h"

int main(void)
{
    /* Setup LEDs */
    LED_Init(LED_NONE);
    
    /* Setup timer 0 */
    Timer_Init(TIMER0, TIMER_MATCH0, TIME_1SEC * 7 / 10, TIMER_INT | TIMER_RST);
    
    /* Setup timer 1 */
    Timer_Init(TIMER1, TIMER_MATCH0, TIME_1SEC * 120, TIMER_RST);
    
    /* Setup RIT */
    RIT_Init(TIME_50MS);
    
    /* Setup joystick */
    Joystick_Init();
    
    /* Start timer 1 */
    Timer_Start(TIMER1);
    
    /* Start RIT */
    RIT_Enable();
    
    while (1)
    {
        __ASM("WFI");
    }
}
