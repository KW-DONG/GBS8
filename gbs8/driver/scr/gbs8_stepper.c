#include "gbs8_stepper.h"
#include "gbs8_timer.h"
#include "gbs8_interrupt.h"

void GBS_Stepper_Init()
{
    GBS_Timer2_Config(ENABLE,T2CKPS1,T2OUTPS1);
}

void TMR_ISR()
{
    
}