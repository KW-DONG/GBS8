#include "gbs8_stepper.h"
#include "gbs8_timer.h"
#include "gbs8_interrupt.h"

void GBS_Stepper_Init()
{
    GBS_Timer2_Config(ENABLE,T2CKPS1,T2OUTPS1);
    P_DIR_W(ON);
    P_STEP_W(ON);
    timerCntsLast = -1; //2^64 - 1
    timerCnts = 0;
    stepperDir = 0;
}

/**
 * 
 * ^
 * |   0.00001s
 * ----+ +---------->t
 * |   | |
 * |   +-+     
 */
void TMR_ISR()
{
    if (timerCnts>0)        //check counter
    {
        timerCnts--;
    }
    else if (timerCnts==0)  //port trigger &steps count
    {
        if (P_STEP_R == OFF)
        {
            P_STEP_W(ON);
            timerCnts = 1;
        }
        else 
        {
            P_STEP_W(OFF);
            if (stepperBuffer.buffer[stepperBuffer.head].dec_until>0)
            {
                if (stepperBuffer.buffer[stepperBuffer.head].acc_until>0)
                {
                    if (P_STEP_R == ON)
                    {
                        P_STEP_W(OFF);
                        stepperBuffer.buffer[stepperBuffer.head].acc_until--;
                        stepperBuffer.buffer[stepperBuffer.head].dec_after--;

                    }
                }
                else if (stepperBuffer.buffer[stepperBuffer.head].dec_after>0)
                {
                    stepperBuffer.buffer[stepperBuffer.head].dec_after--;

                }
            }   

            //timerCnts = LEIBRAMP_CAL(stepperBuffer.buffer[stepperBuffer.head].dir);

        }

    }else if (stepperBuffer.buffer[stepperBuffer.head].dec_until==0)    //change block
    {
        if (stepperBuffer.buffer[(stepperBuffer.head+1)%STEPPER_BUFFER_SIZE].flag == BLOCK_READY)
        {
            stepperBuffer.head = (stepperBuffer.head+1)%STEPPER_BUFFER_SIZE;
            stepperBuffer.buffer[stepperBuffer.head].flag = BLOCK_BUSY;

        }
    }
    
}