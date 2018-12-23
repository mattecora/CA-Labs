#ifndef     __RIT_H
#define     __RIT_H

#include    "LPC17xx.h"

#include    "../led/led.h"

#define     TIME_2HZ            0x00BEBC20

//          lib_rit.c
void        RIT_Init            (unsigned int rit_interval);    // RIT initialization
void        RIT_Enable          (void);                         // Enable RIT
void        RIT_Disable         (void);                         // Disable RIT
void        RIT_Reset           (void);                         // Reset RIT count

//          IRQ_rit.c
void        RIT_IRQHandler      (void);                         // Handler for RIT

#endif
