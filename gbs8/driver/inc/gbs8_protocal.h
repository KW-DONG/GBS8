#ifndef __GBS8_PROTOCAL_H
#define __GBS8_PROTOCAL_H

#include <stdint.h>
#include "gbs8_usart.h"

//serial port protocal for testing

/**
 * standard command 'c'+' '+'num'
 * standard data    'd'+' '+'data'+' '+'e'
 */

#define keyBit0 0
#define keybit1 1
#define keybit2 2
#define keybit3 3
#define keybit4 4
#define keybit5 5
#define keybit6 6
#define keybit7 7

typedef struct 
{
    uint8_t r0:1;
    uint8_t r1:1;
    uint8_t r2:1;
    uint8_t r3:1;
    uint8_t r4:1;
    uint8_t r5:1;
    uint8_t r6:1;
    uint8_t r7:1;
}ctrl_t;

ctrl_t ctrlBits;    //received from master

void GBS_Ctrl_Update(void);

uint8_t GBS_Ctrl_Read(uint8_t i);

/*************************SET_YOUR_MESSAGE*************************************/

#define MESSAGE_0   GBS_Ctrl_Read(&ctrlBits, 0)
#define MESSAGE_1   GBS_Ctrl_Read(&ctrlBits, 1)
#define MESSAGE_2   GBS_Ctrl_Read(&ctrlBits, 2)
#define MESSAGE_3   GBS_Ctrl_Read(&ctrlBits, 3)
#define MESSAGE_4   GBS_Ctrl_Read(&ctrlBits, 4)
#define MESSAGE_5   GBS_Ctrl_Read(&ctrlBits, 5)
#define MESSAGE_6   GBS_Ctrl_Read(&ctrlBits, 6)
#define MESSAGE_7   GBS_Ctrl_Read(&ctrlBits, 7)

#define RECEIVED    "Received"

#define FEEDBACK_0  GBS_USART_Buffer_Write(usartSendBuffer, 0)


/*****************************************************************************/



#endif