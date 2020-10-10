#ifndef __GBS8_TIMER_H
#define __GBS8_TIMER_H

#include <pic16f887.h>
#include <xc.h>
#include <stdint.h>

/************************************************PORTS*************************************************************/



/*******************************************************************************************************************/



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

/****************************************************TMR0***************************************************************************/

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

/**
 * Frequency to Prescale
 * TMR0 input freq = Fosc/4/Prescale = 11059200/(4*PR)
 * where PR can be 2^(X+1), and X is from 0 to 7
 * 
 */
enum TIM0_FREQ
{
    TIM0_1382400HZ = 0b000,
    TIM0_691200HZ,
    TIM0_345600HZ,
    TIM0_172800HZ,
    TIM0_86400HZ,
    TIM0_43200HZ,
    TIM0_21600HZ,
    TIM0_10800HZ
};

enum WDT_FREQ
{
    WDT_2764800HZ = 0b000,
    WDT_1382400HZ,
    WDT_691200HZ,
    WDT_345600HZ,
    WDT_172800HZ,
    WDT_86400HZ,
    WDT_43200HZ,
    WDT_21600HZ
};

/**
 * @brief Timer0 configuration
 * @param clockSource   timer0 can be either timer or counter
 * @param sourceEdge    high to low or low to high
 * @param assignment    Timer or watchdog
 * @param frequency     use TIM0_FREQ or WDT_FREQ
 * 
 * @note        BIT VALUE   TMR0 RATE   WDTRATE
 *            -----------+------------+-----------
 *              3-bits   |  1:2^(B+1) |  1:2^(B)  
 */
void GBS_Timer0_Config(uint8_t clockSoure, uint8_t sourceEdge, uint8_t assignment, uint8_t frequency);


/****************************************************TMR1*************************************************************************/

enum
{
    T1CKPS1,
    T1CKPS2,
    T1CKPS4,
    T1CKPS8
};

//capture / compare

/**
 * @brief Timer1 configuration
 * @param state     can be enable or disable
 * @param gateEN    enable or disable timer gate function
 * @param gateDir   active high or active low
 * @param ckPS       2-bits prescaler
 *                     1:2^B
 * @note Internal clock source is selected
 *
 */
void GBS_Timer1_Config(uint8_t state, uint8_t gateEn, uint8_t gateDir, uint8_t ckPS);

/****************************************************TMR2*************************************************************************/

enum
{
    T2CKPS1,
    T2CKPS4,
    T2CKPS16
};

enum
{
    T2OUTPS1,
    T2OUTPS2,
    T2OUTPS3,
    T2OUTPS4,
    T2OUTPS5,
    T2OUTPS6,
    T2OUTPS7,
    T2OUTPS8,
    T2OUTPS9,
    T2OUTPS10,
    T2OUTPS11,
    T2OUTPS12,
    T2OUTPS13,
    T2OUTPS14,
    T2OUTPS15,
    T2OUTPS16
};

/**
 * @brief Timer2 configuration
 * @param state can be enable or disable
 * @param ckPS   2 bits prescale
 *                  1:4^B
 * 
 * @param outPS   4 bits postscale
 *                  1:B
 * 
 */
void GBS_Timer2_Config(uint8_t state, uint8_t ckPS, uint8_t outPS);

/***********************************PWM_PORTS***********************************************/

enum
{
    PWM_DISABLE,
    PWM_ENABLE
};

#define PWM_10_CFG(X)   STRA = X
#define PWM_3_CFG(X)    STRB = X
#define PWM_2_CFG(X)    STRC = X
#define PWM_1_CFG(X)    STRD = X

/**
 * @brief PWM generator configuration
 * @param pr2   a value that compares timer2
 * @note  PWM period = [(PR2)+1]*4*Tosc*(TMR2 Prescale value)
 *         Tosc = 1/Fosc 
 * 
 *          Then TMR2 is equal to PR2, the following three events occour on the next increment cycle
 *          1. TMR2 is cleared
 *          2. The CCPx pin is set
 *          3. The PWM duty cycle is latched from CCPRxL into CCPRxH
 * 
 *          Pulse Width = (CCPRxL:CCPxCON<5:4>) * Tosc * (TMR2 Prescale Value)
 *          Duty Cycle Ratio = (CCPRxL:CCPxCON<5:4>) / (4(PR2 + 1))
 * 
 *          PWM Resolution = log[4(PR2+1)] / log(2) bits
 * 
 * PWM Signal Generation: Once the PWM is configured and Timer2 is enabled, TMR2 starts incrementing depending on the prescalar. 
 * Once the TMR2 value is equal to dutyCycle(CCPR1L+CCP1CON<5:4>) the PWM pin will be pulled LOW. 
 * The timer still continues to increment till it matches with the period PR2. 
 * After which the PWM pin will be pulled HIGH and TMR2 is reset for next cycle.
 * 
 * @note please config ECCP Register before using the PWM function
 */
void GBS_PWM_Config(uint8_t channel, uint8_t period, uint8_t dutyCycle);

/*************************************************ECCP*****************************************************************************/

#define ECCP_OFF        0b0000      //Capture/Compare/PWM off (resets ECCP module)
#define ECCP_CMP_TOG    0b0010      //Compare mode, toggle output on match (CCP1IF is set)
#define ECCP_CAP_F      0b0100      //Capture mode, every falling edge
#define ECCP_CAP_R      0b0101      //Capture mode, every rising edge
#define ECCP_CAP_4F     0b0110      //Capture mode, every 4th rising edge
#define ECCP_CAP_16F    0b0111      //Capture mode, every 16th rising edge
#define ECCP_CMP_SET    0b1000      //Compare mode, set output on match (CCPXIF is set)
#define ECCP_CMP_CLR    0b1001      //Compare mode, clear output on match (CCPXIF is set)
#define ECCP_CMP_IT     0b1010      //Compare mode, generate software interrupt pn match (CCPXIF is set, CCPX pin is unaffected)
#define ECCP_CMP_TRIG   0b1011      //Compare mode, trigger special event (CCPXIF is set; CCP1 resets TMR1 or TMR2)
#define ECCP_PWM_1      0b1100      //P1A, P1C active-high; P1B, P1D active-high
#define ECCP_PWM_2      0b1101      //P1A, P1C active-high; P1B, P1D active-low
#define ECCP_PWM_3      0b1110      //P1A, P1C active-low; P1B, P1D active-high
#define ECCP_PWM_4      0b1111      //P1A, P1C active-low; P1B, P1D active-low


/**
 * @brief Enhanced Capture/Compare/PWM
 * @param mode1     CCP1 mode
 * @param mode2     CCP2 mode
 * 
 * 
 */
void GBS_ECCP_Config(uint8_t mode1, uint8_t mode2);


#endif