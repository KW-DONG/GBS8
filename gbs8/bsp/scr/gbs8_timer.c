#include <stdlib.h>
#include "gbs8_timer.h"
#include "gbs8_config.h"
#include "gbs8_algo.h"

/**
 *  f_out = fclk / (4*Prescaler*(256-TMR0)*Count)
 */
void GBS_Timer0_Config(uint8_t prescaler, uint8_t timer0)
{
    T0CS = TIMER0;
#if (TIMER0==0)
    PSA = 0;
#endif

#if (TIMER0==1)
    T0SE = TIMER0_SOURCE_EDGE;
#endif

#if (TIMR0==2)
    PSA = 1;
#endif
    OPTION_REGbits.PS = prescaler;
    TMR0 = timer0;       //reset timer0
}

/**
 *  f_out = fclk / (4*Prescaler*(65536 - TMR1)*Count)
 */
void GBS_Timer1_Config(uint8_t state, uint8_t gateEn, uint8_t gateDir, uint8_t frequency)
{
    T1CONbits.TMR1CS = 0;   //use internal clock source
    T1CONbits.T1OSCEN = 0;  //LP oscillator is off  
    T1CONbits.TMR1ON = state;
    T1CONbits.TMR1GE = gateEn;
    T1CONbits.T1GINV = gateDir;
    T1CONbits.T1CKPS = frequency;
    
    //reset timer 1
    TMR1H = 0b0000;
    TMR1L = 0b0000;
}

/**
 *  f_out = fclk / (4*Prescaler*(PR2-TMR2)*Postscaler*Count)
 */
void GBS_Timer2_Config(uint8_t state, uint8_t ckPS, uint8_t outPS)
{
    TMR2ON = state;
    T2CONbits.T2CKPS = ckPS;
    T2CONbits.TOUTPS = outPS;
}

void GBS_PWM_Config(uint8_t channel, uint8_t dutyCycle)
{
    PR2 = 256*_XTAL_FREQ/(4*T2CONbits.T2CKPS) - 1;
    CCP1CONbits.CCP1M = 0b1100;
    CCP1CONbits.P1M = channel;

    //CCPRxL:CCPxCON
    //10-bits PWM pulse width

    uint8_t regH = 0, regL = 0;

    uint16_t ccprxl_ccpxcon = dutyCycle * 4 * (PR2 + 1) / 10;

    Reg10_Decouple(&regH, &regL, ccprxl_ccpxcon);

    CCPR1L = regH;
    CCP1CONbits.DC1B = regL;
    
}
