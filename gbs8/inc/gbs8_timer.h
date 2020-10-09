#ifndef __GBS8_TIMER_H
#define __GBS8_TIMER_H

#include <pic16f887.h>
#include <xc.h>
#include <stdint.h>


enum TIM0_CS    //TMR0 Clock Source Select bit
{
    //when used as a timer, the Timer0 module will increment every instruction cycle (without prescaler)
    TIMER_MODE,

    //when used as a counter, the Timer0 module will increment on every rising or falling edge of the T0CKI pin
    COUNTER_MODE
};

enum TIM0_SE    //TMR0 Source Edge Select bit
{
    L2H,        //Increment on low-to-high transition on T0CKI Pin
    H2L         //Increment on high-to-low transition on T0CKI Pin
};

enum TIM0_PSA
{
    TIMER,
    WDT
};

enum TIM1_EN
{
    DISABLE,
    ENABLE
};

/**
 * @brief Timer0 configuration
 * @param clockSource   timer0 can be either timer or counter
 * @param sourceEdge    high to low or low to high
 * @param assignment    Timer or watchdog
 * @param ps0           3-bits prescaler from 0 to 7
 * @param ps1
 * @param ps2 
 */
void GBS_Timer0_Config(uint8_t clockSoure, uint8_t sourceEdge, uint8_t assignment, uint8_t ps0, uint8_t ps1, uint8_t ps2);

/**
 * @brief Timer1 configuration
 * @param state can be enable or disable
 * 
 * @note Internal clock source is selected
 */
void GBS_Timer1_Config(uint8_t state);

//timer 2
void GBS_Timer2_Config(uint8_t clockSource);

#endif