#include <stdlib.h>
#include "gbs8_timer.h"

void GBS_Timer0_Config(uint8_t clockSource, uint8_t sourceEdge, uint8_t assignment, uint8_t ps0, uint8_t ps1, uint8_t ps2)
{
    T0CS = clockSource;
    T0SE = sourceEdge;
    PSA = assignment;
    PS0 = ps0;
    PS1 = ps1;
    PS2 = ps2;
}

void GBS_Timer1_Mode(uint8_t state)
{
    TMR1CS = 0; //use internal clock source

    TMR1ON = state;

    T1OSCEN = 0;

    

}

void GBS_Timer2_Mode(uint8_t mode);