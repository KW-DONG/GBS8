#include <stdlib.h>
#include "gbs8_timer.h"
#include "gbs8_config.h"
#include "gbs8_algo.h"

void GBS_Timer0_Config(uint8_t clockSource, uint8_t sourceEdge, uint8_t assignment, uint8_t frequency)
{
    T0CS = clockSource;
    T0SE = sourceEdge;
    PSA = assignment;
    OPTION_REGbits.PS = frequency;
    TMR0 = 0;       //reset timer0
}

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
