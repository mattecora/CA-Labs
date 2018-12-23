#ifndef     __STATE_H
#define     __STATE_H

#include    "../led/led.h"
#include    "../timer/timer.h"
#include    "../rit/rit.h"

typedef     enum state      state_t;                    // Definition of state_t type

enum        state           {STATE_RG, STATE_RFG, STATE_GR, STATE_YR};

extern      state_t         current_state;              // Current semaphore state
extern      void            (*Run_State[4])(void);      // Vector of state handlers

void        Run_State0      (void);                     // State handler for STATE_RG
void        Run_State1      (void);                     // State handler for STATE_RFG
void        Run_State2      (void);                     // State handler for STATE_GR
void        Run_State3      (void);                     // State handler for STATE_YR

#endif
