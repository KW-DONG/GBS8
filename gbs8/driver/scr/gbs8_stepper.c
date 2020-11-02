#include "gbs8_stepper.h"
#include "gbs8_timer.h"
#include "gbs8_interrupt.h"
#include "gbs8_relay.h"
#include "gbs8_usart.h"

void GBS_Stepper_Init()
{
#if (TMR==0)

#elif (TMR==1)
    GBS_Timer1_Config(TIM_ENABLE,TIM1_PS1,0);
#elif (TMR==2)
    GBS_Timer2_Config(TIM_ENABLE,T2CKPS1,T2OUTPS1,0);
#endif

#if (STEPPER_A)
    A_DIR_W(P_ON);
    stepperA.state = STEPPER_OFF;
    stepperA.cntsLast = 0;
    stepperA.cnts = 0;
    GBS_Stepper_Buffer_Init(&sBufferA);

#endif
#if (STEPPER_B)
    B_DIR_W(P_ON);
    stepperB.state = STEPPER_OFF;
    stepperB.cntsLast = 0;
    stepperB.cnts = 0;
    GBS_Stepper_Buffer_Init(&sBufferB);
#endif
#if (STEPPER_C)
    C_DIR_W(P_ON);
    stepperC.state = STEPPER_OFF;
    stepperC.cntsLast = 0;
    stepperC.cnts = 0;
    GBS_Stepper_Buffer_Init(&sBufferC);
#endif
#if (STEPPER_D)
    D_DIR_W(P_ON);
    stepperD.state = STEPPER_OFF;
    stepperD.cntsLast = 0;
    stepperD.cnts = 0;
    GBS_Stepper_Buffer_Init(&sBufferD);
#endif
#if (STEPPER_E)
    E_DIR_W(P_ON);
    stepperE.state = STEPPER_OFF;
    stepperE.cntsLast = 0;
    stepperE.cnts = 0;
    GBS_Stepper_Buffer_Init(&sBufferE);
#endif

}

void GBS_Stepper_Buffer_Init(sBuffer_t* sBufferX)
{
    for (uint8_t i = 0; i < STEPPER_BUFFER_SIZE; i++)
    {
        sBufferX->buffer[i].flag = BLOCK_FREE;
    }
}

void GBS_Stepper_Config(stepper_t* stepperX, uint8_t state)
{
    stepperX->pinState = P_ON;
    if (state==STEPPER_ON)  stepperX->state = STEPPER_ON;
    else            stepperX->state = STEPPER_OFF;
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
    cnt_t v_m_c = 0;
 
    //allocate steps
        //calculate time
    float t_i = (v_o - v_i) * a_i / (SQ(a_i) - SQ(a_o));

    float v_a = v_i + a_i * t_i; //v_actual

    steps_t totalSteps = (steps_t)(rotation*(float)RESOLUTION);

    if (v_a<=v_m)   //situation 1
    {
        s_i = totalSteps * s_o * a_i / a_o;
        s_o = totalSteps - s_i;
        v_m_c = RESOLUTION*TIMER_FREQ*(accCnt_t)(v_a / 60.0);
    }
    else            //situation 2
    {
        float t_o = a_o * t_i / a_i;

        float t_m = (2*rotation - (v_i + v_m) * t_i - (v_o + v_m) * t_o) / v_m;

        float totaltime = t_i + t_m + t_o;

        s_i = totalSteps * (steps_t)(t_i / totaltime);

        s_o = totalSteps * (steps_t)(t_o / totaltime);

        s_m = totalSteps - s_i - s_o;

        v_m_c = RESOLUTION*TIMER_FREQ*(accCnt_t)(v_m / 60.0);
    }
    
    //write buffer
    if (sBufferX->buffer[sBufferX->tail].flag==BLOCK_FREE)
    {
        sBufferX->buffer[sBufferX->tail].dir = dir;
        sBufferX->buffer[sBufferX->tail].acc = RESOLUTION*TIMER_FREQ*(accCnt_t)(a_i / 60.0);
        sBufferX->buffer[sBufferX->tail].dec = RESOLUTION*TIMER_FREQ*(accCnt_t)(a_o / 60.0);
        sBufferX->buffer[sBufferX->tail].acc_until = s_i;
        sBufferX->buffer[sBufferX->tail].dec_after = s_i + s_m;
        sBufferX->buffer[sBufferX->tail].dec_until = totalSteps;
        sBufferX->buffer[sBufferX->tail].maxSpeed = RESOLUTION*TIMER_FREQ*(accCnt_t)(v_m / 60.0);
        sBufferX->buffer[sBufferX->tail].flag = BLOCK_READY;

        sBufferX->head = (sBufferX->head + 1) % STEPPER_BUFFER_SIZE;
        return 0;
    }
    else
    {
        return 1;
    }
}

/**
 * 
 * ^
 * |     <-> 1 timer tick
 * |-----+ +---------+ +----
 * |     | |         | |
 * |     +-+         +-+
 * |     <-----------> cntsLast
 * 
 * test mode 1: startup
 * test mode 2: change block
 * test mode 3: shut down
 * 
 * the FIRST_STEP_CAL must be called only when the stepper starts up
 * otherwise use NEXT_STEP_CAL
 * the stepper must stop if the block buffer is empty
 * 
 */
void GBS_Stepper_Exe(stepper_t* stepperX, sBuffer_t* sBufferX)
{
    if (stepperX->pinState==P_OFF)
    {
        stepperX->pinState = P_ON;
        stepperX->cnts--;
#if TEST
    
#endif
        
    }
    else
    {
        if (stepperX->cnts>0)   stepperX->cnts--;
        else
        {
            //the block is empty and the stepper is ON
            if (sBufferX->buffer[sBufferX->head].acc_until+sBufferX->buffer[sBufferX->head].dec_after+sBufferX->buffer[sBufferX->head].dec_until==0)
            {
                //change block or stop the stepper
                if (sBufferX->buffer[(sBufferX->head+1)%STEPPER_BUFFER_SIZE].flag==BLOCK_READY)
                {
                    sBufferX->head = (sBufferX->head+1)%STEPPER_BUFFER_SIZE;
                    sBufferX->buffer[sBufferX->head].flag = BLOCK_EXE;
                    if (stepperX->state==STEPPER_OFF)
                    {
                        stepperX->cntsLast = FIRST_STEP_CAL(sBufferX->buffer[sBufferX->head].maxSpeed,sBufferX->buffer[sBufferX->head].acc);
                        stepperX->state = STEPPER_ON;
                    }  
                }
                else
                {
                    stepperX->state = STEPPER_OFF;
                }
            }

            //execute buffer
            if (sBufferX->buffer[sBufferX->head].flag == BLOCK_EXE)
            {
                if (sBufferX->buffer[sBufferX->head].acc_until>=0)  //acceleration
                {
                    stepperX->pinState = P_OFF;
                    stepperX->cntsLast = NEXT_STEP_CAL(1,stepperX->cntsLast,sBufferX->buffer[sBufferX->head].acc);
                    
                    sBufferX->buffer[sBufferX->head].acc_until--;
                    sBufferX->buffer[sBufferX->head].dec_after--;
                }
                else if (sBufferX->buffer[sBufferX->head].dec_after>=0) //base speed
                {
                    stepperX->pinState = P_OFF;
                    sBufferX->buffer[sBufferX->head].dec_after--;
                }
                else    //deceleration
                {
                    stepperX->pinState = P_OFF;
                    stepperX->cntsLast = NEXT_STEP_CAL(-1,stepperX->cntsLast,sBufferX->buffer[sBufferX->head].acc);
                }
                stepperX->cnts = stepperX->cntsLast;
            }
        }
    }    
}

void GBS_Stepper_Update(void)
{
#if (STEPPER_A)
    if (stepperA.state == STEPPER_OFF)
    {
        A_STEP_W(P_ON);
    }
    else
    {
        A_DIR_W(stepperA.dir);
        A_STEP_W(stepperA.pinState); 
    }
#endif

#if (STEPPER_B)
    if (stepperB.state == STEPPER_OFF)
    {
        B_STEP_W(P_ON);
    }
    else
    {
        B_DIR_W(stepperB.dir);
        B_STEP_W(stepperB.pinState); 
    } 
#endif

#if (STEPPER_C)
    if (stepperC.state == STEPPER_OFF)
    {
        C_STEP_W(P_ON);
    }
    else
    {
        C_DIR_W(stepperC.dir);
        C_STEP_W(stepperC.pinState); 
    }
#endif

#if (STEPPER_D)
    if (stepperD.state == STEPPER_OFF)
    {
        D_STEP_W(P_ON);
    }
    else
    {
        D_DIR_W(stepperD.dir);
        D_STEP_W(stepperD.pinState); 
    } 
#endif

#if (STEPPER_E)
    if (stepperE.state == STEPPER_OFF)
    {
        E_STEP_W(P_ON);
    }
    else
    {
        E_DIR_W(stepperE.dir);
        E_STEP_W(stepperE.pinState); 
    } 
#endif

}

void TMR_ISR()
//void TMR_ISR()
{

    //if (GBS_RELAY1_R==NC)   GBS_RELAY1_SET(NO);
    //else                    GBS_RELAY1_SET(NC);

#if (STEPPER_A)
    if (stepperA.lock==STEPPER_OFF) GBS_Stepper_Exe(&stepperA, &sBufferA);
#endif

#if (STEPPER_B)
    if (stepperB.lock==STEPPER_OFF) GBS_Stepper_Exe(&stepperB, &sBufferB);
#endif

#if (STEPPER_C)
    if (stepperC.lock==STEPPER_OFF) GBS_Stepper_Exe(&stepperC, &sBufferC);
#endif

#if (STEPPER_D)
    if (stepperD.lock==STEPPER_OFF) GBS_Stepper_Exe(&stepperD, &sBufferD);
#endif

#if (STEPPER_E)
    if (stepperE.lock==STEPPER_OFF) GBS_Stepper_Exe(&stepperE, &sBufferE);
#endif

    GBS_Stepper_Update();
}