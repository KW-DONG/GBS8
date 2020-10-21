#include "gbs8_stepper.h"
#include "gbs8_timer.h"
#include "gbs8_interrupt.h"

void GBS_Stepper_Init()
{
    
    P_DIR_W(ON);
    P_STEP_W(ON);
    timerCntsLast = -1; //2^64 - 1
    timerCnts = 0;
    stepperDir = 0;

#if (TMR==0)

#elif (TMR==1)

#elif (TMR==2)
    GBS_Timer2_Config(ENABLE,T2CKPS1,T2OUTPS1);
#endif


#if (STEPPER_A)
    A_DIR_W(ON);
    stepperA.state = OFF;
    stepperA.cntsLast = 0;
    stepperA.cnts = 0;
#endif
#if (STEPPER_B)
    B_DIR_W(ON);
    stepperB.state = OFF;
    stepperB.cntsLast = 0;
    stepperB.cnts = 0;
#endif
#if (STEPPER_C)
    C_DIR_W(ON);
    stepperC.state = OFF;
    stepperC.cntsLast = 0;
    stepperC.cnts = 0;
#endif
#if (STEPPER_D)
    D_DIR_W(ON);
    stepperD.state = OFF;
    stepperD.cntsLast = 0;
    stepperD.cnts = 0;
#endif
#if (STEPPER_E)
    E_DIR_W(ON);
    stepperE.state = OFF;
    stepperE.cntsLast = 0;
    stepperE.cnts = 0;
#endif

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
            timerCnts = 1;  //set time delay 0.00001s
        }
        else 
        { 
            if (stepperBuffer.buffer[stepperBuffer.head].dec_until>0)   //the block has not been executed
            {
                P_STEP_W(OFF);
                if (stepperBuffer.buffer[stepperBuffer.head].acc_until>0)   //accceleration
                {
                    stepperBuffer.buffer[stepperBuffer.head].acc_until--;
                    stepperBuffer.buffer[stepperBuffer.head].dec_after--;
                    timerCnts = LEIBRAMP_CAL(1);
                }
                else if (stepperBuffer.buffer[stepperBuffer.head].dec_after>0)  //base speed
                {
                    stepperBuffer.buffer[stepperBuffer.head].dec_after--;
                    timerCnts = LEIBRAMP_CAL(0);
                }
                else    //deceleration
                {
                    stepperBuffer.buffer[stepperBuffer.head].dec_until--;
                    timerCnts = LEIBRAMP_CAL(-1);
                }
            }
            else        //change block
            {
                if (stepperBuffer.buffer[(stepperBuffer.head+1)%STEPPER_BUFFER_SIZE].flag == BLOCK_READY)
                {
                    stepperBuffer.head = (stepperBuffer.head+1)%STEPPER_BUFFER_SIZE;
                    stepperBuffer.buffer[stepperBuffer.head].flag = BLOCK_BUSY;
                    

                }
            }
            

            //timerCnts = LEIBRAMP_CAL(stepperBuffer.buffer[stepperBuffer.head].dir);
        }
    }
}