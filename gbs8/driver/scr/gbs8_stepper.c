#include "gbs8_stepper.h"
#include "gbs8_timer.h"
#include "gbs8_interrupt.h"

void GBS_Stepper_Init()
{
    GBS_Timer2_Config(ENABLE,T2CKPS1,T2OUTPS1);
}


/**
 * 
 * ^
 * |   0.00001s
 * |   +-+
 * |   | |  
 * ----+ +---------->t
 *       
 */
void TMR_ISR()
{
    //check counter
    if (timerCnts>0)
    {
        timerCnts--;
    }
    else
    {
        if ()
        
        
        
        //check current block
        if (stepperBuffer.buffer[stepperBuffer.head].dec_until>0)
        {
            if (stepperBuffer.buffer[stepperBuffer.head].acc_until>0)
            {
                stepperBuffer.buffer[stepperBuffer.head].acc_until--;
                stepperBuffer.buffer[stepperBuffer.head].dec_after--;
            }
        }

        
        else if (stepperBuffer.buffer[stepperBuffer.head].dec_after>0)
        {
            stepperBuffer.buffer[stepperBuffer.head].dec_after--;

        }
        else if (stepperBuffer.buffer[stepperBuffer.head].dec_until>0)
        {
            stepperBuffer.buffer[stepperBuffer.head].dec_until--;
        }
        else if (stepperBuffer.buffer[(stepperBuffer.head+1)%STEPPER_BUFFER_SIZE].flag == BLOCK_READY)
        {
            //change block
            stepperBuffer.head = (stepperBuffer.head+1)%STEPPER_BUFFER_SIZE;
            stepperBuffer.buffer[stepperBuffer.head].flag = BLOCK_BUSY;


        }
        
    }
    
}