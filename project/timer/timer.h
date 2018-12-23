#ifndef     __TIMER_H
#define     __TIMER_H

#include    "LPC17xx.h"

#include    "../state/state.h"

#define     INT_ON_MATCH        1
#define     RST_ON_MATCH        2
#define     STP_ON_MATCH        4
#define     IRS_ON_MATCH        INT_ON_MATCH | RST_ON_MATCH | STP_ON_MATCH

#define     TIME_5SEC           0x07735940

//          lib_timer.c
void        Timer_Init          (unsigned char timer_num,
                                    unsigned int timer_interval,
                                    unsigned char timer_behavior);  // Timer initialization
void        Timer_Start         (unsigned char timer_num);          // Start timer
void        Timer_Stop          (unsigned char timer_num);          // Stop timer
void        Timer_Reset         (unsigned char timer_num);          // Reset timer

//          IRQ_timer.c
void        TIMER0_IRQHandler   (void);                             // Handler for timer 0
void        TIMER1_IRQHandler   (void);                             // Handler for timer 1

#endif
