#include "gbs8_relay.h"

void GBS_Relay1_Init()
{
    GBS_Relay1_Set();
}

void GBS_Relay1_Set()
{
    TRISEbits.TRISE2 = 1;//input
    PORTEbits.RE2 = 0;
}

void GBS_Relay1_Reset()
{
    TRISEbits.TRISE2 = 0;//output
    PORTEbits.RE2 = 1;
}

void GBS_Relay2_Init()
{
    GBS_Relay2_Set();
}

void GBS_Relay2_Set()
{
    TRISEbits.TRISE1 = 1;//input
    PORTEbits.RE1 = 0;
}

void GBS_Relay2_Reset()
{
    TRISEbits.TRISE1 = 0;//input
    PORTEbits.RE1 = 1;
}

