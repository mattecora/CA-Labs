#include "lpc17xx.h"

#include "../led/led.h"
#include "../button/button.h"
#include "../timer/timer.h"
#include "../rit/rit.h"

#include "../state/state.h"

int main(void)
{
    /* SystemInit() already called by startup_LPC17xx.s */

    /* Initialize LEDs as off */
    LED_Init(LED_NONE);

    /* Initialize all buttons */
    Button_Init(BUTTON_ALL);

    /* Initialize timer 0 (15 seconds timer) */
    Timer_Init(TIMER0, TIMER_MATCH0, TIME_15SEC, TIMER_IRS);

    /* Initialize timer 1 (5 seconds timer) */
    Timer_Init(TIMER1, TIMER_MATCH0, TIME_5SEC, TIMER_IRS);

    /* Initialize RIT */
    RIT_Init(FREQ_2HZ);

    /* Run the first state function */
    Run_State[current_state]();

    while (1)
    {
        __ASM("WFI");
    }
}
