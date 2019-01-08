/*--------------------------------------------------------------------------*/
/*          Timer library for LPC1768/LandTiger board                       */
/*--------------------------------------------------------------------------*/

#ifndef     __TIMER_H
#define     __TIMER_H

#include    "LPC17xx.h"

#include    "../state/state.h"

/*--------- Timer index defines --------------------------------------------*/

#define     TIMER0          0
#define     TIMER1          1
#define     TIMER2          2
#define     TIMER3          3

/*--------- Match registers defines ----------------------------------------*/

#define     TIMER_MATCH0    0
#define     TIMER_MATCH1    1
#define     TIMER_MATCH2    2
#define     TIMER_MATCH3    3

/*--------- Timer behavior defines -----------------------------------------*/

#define     TIMER_NOP       0
#define     TIMER_INT       1
#define     TIMER_RST       2
#define     TIMER_STP       4
#define     TIMER_IRS       7

/*--------- Timer interval defines -----------------------------------------*/

#define     DEBUG                                   /* Delete for real vals */

#ifdef      DEBUG

#define     TIME_5SEC       0x00BEBC20              /* Divided by 10        */
#define     TIME_15SEC      3 * TIME_5SEC           /* Divided by 10        */
#define     FREQ_2HZ        0x001312D0              /* Divided by 10        */

#else

#define     TIME_5SEC       0x07735940              /* True value           */
#define     TIME_15SEC      3 * TIME_5SEC           /* True value           */
#define     FREQ_2HZ        0x00BEBC20              /* True value           */

#endif

/*--------- lib_timer.c ----------------------------------------------------*/

void        Timer_Init(uint8_t timer_num,
                       uint8_t match_reg,
                       uint32_t timer_interval,
                       uint8_t timer_behavior);     /* Initialize a timer   */
void        Timer_SetMR(uint8_t timer_num,
                        uint8_t match_reg,
                        uint32_t timer_interval);   /* Set a timer MR       */
void        Timer_SetMCR(uint8_t timer_num,
                         uint8_t match_reg,
                         uint8_t timer_behavior);   /* Set a timer MCR      */
void        Timer_Start(uint8_t timer_num);         /* Start a timer        */
void        Timer_Stop(uint8_t timer_num);          /* Stop a timer         */
void        Timer_Reset(uint8_t timer_num);         /* Reset a timer        */

/*--------- IRQ_timer.c ----------------------------------------------------*/

void        TIMER0_IRQHandler(void);                /* Handler for timer 0  */
void        TIMER1_IRQHandler(void);                /* Handler for timer 1  */
void        TIMER2_IRQHandler(void);                /* Handler for timer 2  */
void        TIMER3_IRQHandler(void);                /* Handler for timer 3  */

#endif
