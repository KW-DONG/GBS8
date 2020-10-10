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

void GBS_Timer1_Config(uint8_t state, uint8_t gateEn, uint8_t gateDir, uint8_t ckPS)
{
    T1CONbits.TMR1CS = 0;   //use internal clock source
    T1CONbits.T1OSCEN = 0;  //LP oscillator is off  
    T1CONbits.TMR1ON = state;
    T1CONbits.TMR1GE = gateEn;
    T1CONbits.T1GINV = gateDir;
    T1CONbits.T1CKPS = ckPS;
    
}

void GBS_Timer2_Config(uint8_t state, uint8_t ckPS, uint8_t outPS)
{
    TMR2ON = state;
    T2CONbits.T2CKPS = ckPS;
    T2CONbits.TOUTPS = outPS;
}

void GBS_PWM_Config(uint8_t channel, uint8_t period, uint8_t dutyCycle)
{
    PR2 = period*_XTAL_FREQ/(4*T2CONbits.T2CKPS) - 1;
    CCP1CONbits.CCP1M = channel;
    
    
    PWM1CONbits.PDC;
    PWM1CONbits.PRSEN;
}

void GBS_ECCP_Config(uint8_t mode1, uint8_t mode2)
{
    CCP1CONbits.CCP1M = mode1;
    CCP2CONbits.CCP2M = mode2;
}