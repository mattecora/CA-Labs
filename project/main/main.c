#include "lpc17xx.h"

#include "../led/led.h"
#include "../button/button.h"
#include "../timer/timer.h"
#include "../rit/rit.h"
#include "../joystick/joystick.h"
#include "../adc/adc.h"
#include "../dac/dac.h"

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
    Timer_Init(TIMER1, TIMER_MATCH0, FREQ_1HZ, TIMER_NOP);
    Timer_Init(TIMER1, TIMER_MATCH1, FREQ_2HZ, TIMER_NOP);
    
    /* Initialize play timer */
    Timer_Init(TIMER2, TIMER_MATCH0, FREQ_440HZ, TIMER_INT | TIMER_RST);
    
    /* Initialize RIT */
    RIT_Init(TIME_50MS);
    
    /* Initialize joystick */
    Joystick_Init();
    
    /* Initialize ADC */
    ADC_Init(ADC_POTM);
    
    /* Initialize DAC */
    DAC_Init();
    
    /* Set interrupt priorities */
    NVIC_SetPriority(TIMER2_IRQn, 0);
    NVIC_SetPriority(EINT0_IRQn, 1);
    NVIC_SetPriority(EINT1_IRQn, 1);
    NVIC_SetPriority(EINT2_IRQn, 1);
    NVIC_SetPriority(TIMER0_IRQn, 2);
    NVIC_SetPriority(TIMER1_IRQn, 2);
    NVIC_SetPriority(RIT_IRQn, 2);
    NVIC_SetPriority(ADC_IRQn, 3);
    
    /* Run the first state function */
    Run_State[Current_State]();

    while (1)
    {
        __ASM("WFI");
    }
}
