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

enum TIM_EN
{
    DISABLE,
    ENABLE
};

enum TIM1_DIR
{
    LOW,
    HIGH
};

/**
 * @brief Timer0 configuration
 * @param clockSource   timer0 can be either timer or counter
 * @param sourceEdge    high to low or low to high
 * @param assignment    Timer or watchdog
 * @param prX           3-bits prescaler from 0 to 7
 * 
 * @note        BIT VALUE   TMR0 RATE   WDTRATE
 *            -----------+------------+-----------
 *              3-bits   |  1:2^(B+1) |  1:2^(B)
 *           
 */
void GBS_Timer0_Config(uint8_t clockSoure, uint8_t sourceEdge, uint8_t assignment, uint8_t pr0, uint8_t pr1, uint8_t pr2);

/**
 * @brief Timer1 configuration
 * @param state     can be enable or disable
 * @param gateEN    enable or disable timer gate function
 * @param gateDir   active high or active low
 * @param prX       2-bits prescaler
 *                     1:2^B
 * @note Internal clock source is selected
 *
 */
void GBS_Timer1_Config(uint8_t state, uint8_t gateEn, uint8_t gateDir, uint8_t pr0, uint8_t pr1);

/**
 * @brief Timer2 configuration
 * @param state can be enable or disable
 * @param prX   2 bits prescale
 *                  1:2^B
 * 
 * @param poX   4 bits postscale
 *                  1:B
 * 
 */
void GBS_Timer2_Config(uint8_t state, uint8_t pr0, uint8_t pr1, uint8_t po0, uint8_t po1, uint8_t po2, uint8_t po3);

#endif