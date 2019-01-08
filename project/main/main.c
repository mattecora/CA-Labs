#include "lpc17xx.h"

#include "../led/led.h"
#include "../button/button.h"
#include "../timer/timer.h"

#include "../state/state.h"

int main(void)
{
    /* SystemInit() already called by startup_LPC17xx.s */

    /* Initialize LEDs as off */
    LED_Init(LED_NONE);

    /* Initialize all buttons */
    Button_Init(BUTTON_ALL);

    /* Initialize main timer */
    Timer_Init(TIMER0, TIMER_MATCH0, TIME_15SEC, TIMER_NOP);
    Timer_Init(TIMER0, TIMER_MATCH1, TIME_5SEC, TIMER_NOP);

    /* Initialize blinking timer */
    Timer_Init(TIMER1, TIMER_MATCH0, FREQ_2HZ, TIMER_INT | TIMER_RST);
    
    /* Run the first state function */
    Run_State[current_state]();

    while (1)
    {
        __ASM("WFI");
    }
}
