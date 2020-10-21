#ifndef __GBS8_STEPPER_H
#define __GBS8_STEPPER_H
#include "stdint.h"
#include <stdint.h>
#include "gbs8_gpio.h"

/****************************CONFIGURATION***********************************/

#define STEPPER_BUFFER_SIZE 5   //number of trapezoidal curves in the buffer

#define MAXIMUM_SPEED           3000    //use rpm
#define MAXIMUM_ACCELERATION    1000    //rpm^2
#define JERK_SPEED              20      //rpm, speed difference that does not need an acceleration
#define RESOLUTION      200     //steps per rotation, default rotate angle is 1.8 degree

#define STEPPER_A   1
#define STEPPER_B   0
#define STEPPER_C   0
#define STEPPER_D   0
#define STEPPER_E   0

#if STEPPER_A 

#elif STEPPER_B


#endif









#define P_DIR_W(X)  POUT_1(X)
#define P_DIR_R     POUT_1_R  
#define P_STEP_W(X) POUT_2(X)
#define P_STEP_R    POUT_2_R

#define TMR 2                   //timer selected


/*****************************************************************************/

/**
 * 
 * ^
 * |
 * |           +---------+
 * |          /|         |
 * |         / |         |
 * |        /  |         |
 * |f_jerk +   |         |
 * |       |   |         |
 * +-------+---+---------+------->
 *        t0   t1        t2
 * 
 * f_jerk is the minimal frequency that depends on the counter variable
 * 
 */


#define MAXIMUM_FREQ    MAXIMUM_SPEED*RESOLUTION/60 //Hz
#define JERK_FREQ       JERK_FREQ*RESOLUTION/60     //Hz

#if (TMR==0)
#define TMR_ISR T0I_ISR
#elif (TMR==1)
#define TMR_ISR T1I_ISR
#elif (TMR==2)
#define TMR_ISR T2I_ISR
#define STEPPER_ON  GBS_Timer2_Config(ENABLE,T2CKPS1,T2OUTPS1)
#define STEPPER_OFF GBS_Timer2_Config(DISABLE,T2CKPS1,T2OUTPS1)
#endif

/*********************************TYPES*************************************/

#define BLOCK_BUSY  0
#define BLOCK_FREE  1
#define BLOCK_READY 2

#define CLOCKWISE       0
#define ANTICLOCKWISE   1

typedef uint8_t dir_t;          //direction

typedef float accRm_t;          //rotations per minute per minute
typedef float speedRm_t;        //rotations per minute
typedef float rotate_t;         //rotations

typedef uint64_t accSec_t;      //steps per second per second
typedef uint64_t speedSec_t;    //steps per second
typedef uint64_t steps_t;       //steps

typedef uint64_t accCnt_t;      //Counts increasement per step
typedef uint64_t cnt_t;         //Counts per step

typedef struct
{
    dir_t dir;

    steps_t acc_until;     
    steps_t dec_after;
    steps_t dec_until;
    
    accCnt_t acc;
    accCnt_t dec;

    uint8_t  flag;
}trapblock_t;

typedef struct 
{
    trapblock_t buffer[STEPPER_BUFFER_SIZE];
    uint8_t head;
    uint8_t tail;
    uint8_t size;
}stepperBuffer_t;

typedef struct 
{
    uint8_t state;          //ON or OFF
    uint8_t dir;            //stepper direction
    uint64_t cnts;          //used for iteration
    uint64_t cntsLast;      //represents current frequency
}stepper_t;

/*******************************Declaration***************************************/

/**
 * @brief stepper motor initialization
 */
void GBS_Stepper_Init();

/**
 * @brief trapezoidal curve planner
 * @param stepperX stepper motor id
 * @param direction clockwise or anticlockwise
 * @param rotation  rotation number (float)
 * @param maximumSpeed maximum rotation speed (rpm)
 * @param acceleration
 * @param deceleration
 */
uint8_t GBS_Stepper_Planner(stepper_t stepperX, dir_t direction, rotate_t rotation, speedRm_t maximumSpeed, accRm_t acceleration, accRm_t deceleration);

/**
 * @brief stepper execution
 * @param stepperX stepper motor id
 * @note only called by ISR
 */
void GBS_Stepper_Exe(stepper_t stepperX);
/************************GLOBAL_VARIABLES************************************/

stepperBuffer_t stepperBuffer;

uint64_t timerCnts;

#define PORT_FLAG_UP    0
#define PORT_FLAG_FALL  1
uint8_t  portFlag = 0;

/*****************************ALGORITHMN****************************************/

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
 * p1 - delay period for the base speed steps
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

#define JERK_DELAY(f)   10000/f
#define LEIBRAMP_CAL(X) LR_p*(1+X*LR_q+SQ(X*LR_q))








#endif