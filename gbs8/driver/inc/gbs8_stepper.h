#ifndef __GBS8_STEPPER_H
#define __GBS8_STEPPER_H
#include "stdint.h"
#include <stdint.h>
#include "gbs8_gpio.h"

/****************************CONFIGURATION***********************************/

#define STEPPER_BUFFER_SIZE 5   //number of trapezoidal curves in the buffer

#define MAXIMUM_SPEED           3000    //use rpm
#define MAXIMUM_ACCELERATION    1000    //rpm^2
#define RESOLUTION      200     //steps per rotation, default rotate angle is 1.8 degree

#define P_DIR_W(X)  POUT_1(X)
#define P_DIR_R       
#define P_STP_W(X)  POUT_2(X)

#define TMR 2                   //timer selected

/*****************************************************************************/

#define MAXIMUM_FREQ    MAXIMUM_SPEED*RESOLUTION/60 //Hz

#if (TMR==0)
#define TMR_ISR T0I_ISR
#elif (TMR==1)
#define TMR_ISR T1I_ISR
#elif (TMR==2)
#define TMR_ISR T2I_ISR
#endif

/*********************************TYPES*************************************/

#define BLOCK_BUSY  0
#define BLOCK_FREE  1
#define BLOCK_READY 2


typedef struct
{
    uint8_t dir;
    uint32_t freq_in;
    uint64_t acc_until;
    uint64_t dec_after;
    uint64_t dec_until;
    uint32_t max_freq;
    uint8_t  flag;
}trapblock_t;

typedef struct 
{
    trapblock_t buffer[STEPPER_BUFFER_SIZE];
    uint8_t head;
    uint8_t tail;
    uint8_t size;
}stepperBuffer_t;

void GBS_Stepper_Init();

/**
 * @brief write stepper buffer
 * 
 */
void GBS_Stepper_Buffer_Writer(uint32_t freq, uint32_t steps);

void GBS_Stepper_Executor();

/**
 * @brief update stepper directly
 * @param freq stepper frequency
 * @param en   enable or diable
 */
void GBS_Stepper_Config(uint32_t freq, uint8_t en);

/************************GLOBAL_VARIABLES************************************/
stepperBuffer_t stepperBuffer;

//used for timer delay
//each count causes 0.0001s
uint64_t timerCnts = 0;

uint64_t timerCntsLast = 0;

uint8_t  stepperDir = 0;

uint8_t  portState = 0;

uint8_t  portStateLast = 0;

/****************************************************************************/

#define STEPPER_ACC     1
#define STEPPER_CST     0
#define STEPPER_DEC     -1

/**The LeibRamp Algorithmn
 * 
 * The given parameters are:
 * v0 - base speed (steps per second)
 * v - slew speed
 * a - acceleration (steps per second per second)
 * F - timer frequency
 * 
 * and calculated parameters are:
 * S - acceleration/deceleration distance
 *          S = (v^2 - v0^2) / (2a)
 * p1 - delay period for the slew speed steps
 *          p1 = F / (v0^2 + 2a)^0.5
 * ps - delay period for the slew speed steps
 *          ps = F / v
 * R - constant multiplier
 *          R = a / F^2
 * 
 * p - the variable delay period
 *          p = p*(1 + m*p*p)
 * 
 * where 
 * m = -R during acceleration phase
 * m = 0 between acceleration and deceleration phases
 * m = R during deceleration phase
 * 
 * with better precision
 * p = p * (1 + q + q^2)
 * where
 * q = m*p*p
 * 
 */
#define LR_p    timerCntsLast*MAXIMUM_FREQ
#define LR_R    MAXIMUM_FREQ*SQ(LR_p)
#define LR_q    LR_R*SQ(LR_p)

#define LEIBRAMP_CAL(X) LR_p*(1+X*LR_q+SQ(X*LR_q))

#endif