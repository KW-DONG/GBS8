#include "gbs8_stepper.h"
#include "gbs8_timer.h"
#include "gbs8_interrupt.h"

void GBS_Stepper_Init()
{
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
 * Trapezoidal curve calculation
 * 
 * The given parameters are:
 * v_i: entry speed
 * a_i: acceleration
 * v_m: maximum speed
 * v_o: leave speed
 * a_o: deceleration
 * s_t: totoal distance
 * 
 * determine:
 * v_a: actual maximum speed
 * 
 * Assume the curve meets situation 1
 * s_t = (v_i + v_a) * t_i / 2 + (v_o + v_a) * t_o / 2 -------- 1
 * t_o = a_o * t_i / (a_i) -------------------------------------2
 * v_i + a_i * t_i = v_o + a_o * t_o ---------------------------3
 * 
 * then t_i can be determined with equation 2 and 3
 * t_i = (v_o - v_i) * a_i / (a_i^2 - a_o^2)
 * 
 * 
 * Situation 1:
 * 
 * ^
 * |
 * |
 * |      + less than maximum speed
 * |     /|\
 * |    / | \
 * |   +  |  +
 * |   |  |  |
 * +---+--+--+--------------------->t
 *     0 t_i t_i+t_o
 * 
 * 
 * 
 * Situation 2:
 * 
 * ^
 * |     +---------------+ maximum speed
 * |    /|               |\
 * |   + |               | +   
 * |   | |               | |
 * +---+-+---------------+-+------>t
 *    0  t_i       t_i+t_m
 *                        t_i+t_m+t_o
 */

uint8_t GBS_Stepper_Planner(sBuffer_t* sBufferX, dir_t dir, rotate_t rotation, speedRm_t v_i, speedRm_t v_m, speedRm_t v_o, accRm_t a_i, accRm_t a_o)
{
    steps_t s_i = 0;
    steps_t s_m = 0;
    steps_t s_o = 0;
 
    //allocate steps
        //calculate time
    float t_i = (v_o - v_i) * a_i / (SQ(a_i) - SQ(a_o));

    float v_a = v_i + a_i * t_i;

    steps_t totalSteps = (steps_t)(rotation*(float)RESOLUTION);

    if (v_a<=v_m)   //situation 1
    {
        s_i = totalSteps * s_o * a_i / a_o;
        s_o = totalSteps - s_i;
    }
    else            //situation 2
    {
        float t_o = a_o * t_i / a_i;

        float t_m = (2*rotation - (v_i + v_m) * t_i - (v_o + v_m) * t_o) / v_m;

        float totaltime = t_i + t_m + t_o;

        s_i = totalSteps * (steps_t)(t_i / totaltime);

        s_o = totalSteps * (steps_t)(t_o / totaltime);

        s_m = totalSteps - s_i - s_o;
    }
    
    //write buffer
    if (sBufferX->buffer[sBufferX->head].flag==BLOCK_FREE)
    {
        sBufferX->buffer[sBufferX->head].dir = dir;
        sBufferX->buffer[sBufferX->head].acc = RESOLUTION*DELAY_CNT*(accCnt_t)(a_i / 60.0);
        sBufferX->buffer[sBufferX->head].dec = RESOLUTION*DELAY_CNT*(accCnt_t)(a_o / 60.0);
        sBufferX->buffer[sBufferX->head].acc_until = s_i;
        sBufferX->buffer[sBufferX->head].dec_after = s_i + s_m;
        sBufferX->buffer[sBufferX->head].dec_until = totalSteps;
        sBufferX->buffer[sBufferX->head].flag = BLOCK_READY;
        sBufferX->head = (sBufferX->head + 1) % STEPPER_BUFFER_SIZE;
        return 0;
    }
    else
    {
        return 1;
    }
}
void GBS_Stepper_Exe(stepper_t* stepperX, sBuffer_t* sBufferX)
{
    if (stepperX->cnts>0)
    {
        stepperX->cnts--;
    }
    else
    {
        if (stepperX->pinState==OFF)
        {
            stepperX->pinState = ON;
            stepperX->cnts = 1;
        }
        else
        {
            //check block
            if (sBufferX->buffer[sBufferX->tail].dec_until>=0)
            {
                if (sBufferX->buffer[sBufferX->tail].acc_until>=0)
                {

                }
                else if (sBufferX->buffer[sBufferX->tail].dec_after>=0)
                {

                }
                else
                {
                    
                }
                stepperX->pinState = OFF;
                stepperX->cntsLast = LEIBRAMP_CAL(1,stepperX->cntsLast);
            }
            else if (sBufferX->buffer[(sBufferX->tail+1)%STEPPER_BUFFER_SIZE].flag==BLOCK_READY)
            {
                
            }
            
        }
    }  
}

void GBS_Stepper_Update()
{

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

#if (STEPPER_A)


#endif

#if (STEPPER_B)


#endif

#if (STEPPER_C)


#endif

#if (STEPPER_D)


#endif

#if (STEPPER_E)


#endif

}