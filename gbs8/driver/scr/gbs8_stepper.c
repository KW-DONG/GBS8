#include "gbs8_stepper.h"
#include "gbs8_timer.h"
#include "gbs8_interrupt.h"

void GBS_Stepper_Init()
{
    GBS_Timer2_Config(ENABLE,T2CKPS1,T2OUTPS1);
}

void TMR_ISR()
{
    //check counter
    if (stepperCnts>0)
    {
        stepperCnts--;
    }
    else
    {
        //check current block
        if (stepperBuffer.buffer[stepperBuffer.head].acc_until>0)
        {
            stepperBuffer.buffer[stepperBuffer.head].acc_until--;
            stepperBuffer.buffer[stepperBuffer.head].dec_after--;
            stepperCnts = 10000/(stepperFreq + MAXIMUM_ACCELERATION);
        }
        else if (stepperBuffer.buffer[stepperBuffer.head].dec_after>0)
        {
            stepperBuffer.buffer[stepperBuffer.head].dec_after--;
            stepperCnts = 10000/(stepperFreq);
        }
        else if (stepperBuffer.buffer[stepperBuffer.head].dec_until>0)
        {
            stepperBuffer.buffer[stepperBuffer.head].dec_until--;
            stepperCnts = 10000/(stepperFreq - MAXIMUM_ACCELERATION);
        }
    }
    
    
    


    //update current block / change blocks


    
}