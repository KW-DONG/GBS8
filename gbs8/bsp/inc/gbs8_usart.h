#ifndef __GBS8_USART_H
#define __GBS8_USART_H

#include <pic16f887.h>
#include <xc.h>
#include <stdint.h>


/*****************************USART***********************************************/

#define USART_BUFFER_SIZE   16

typedef struct 
{
    uint8_t buffer[USART_BUFFER_SIZE];
    uint8_t head;
    uint8_t tail;
    uint8_t size;
}USART_buffer_t;

typedef char command_t;  

USART_buffer_t usartReceiveBuffer;

USART_buffer_t usartSendBuffer;

uint8_t GBS_USART_Buffer_Read(USART_buffer_t* buffer);

void GBS_USART_Buffer_Write(USART_buffer_t* buffer, uint8_t value);

/**
 * @brief init usart and set baudrate
 * @param baudRate
 */
void GBS_USART_Init(uint16_t baudRate);

void GBS_USART_Receive(void);

/**
 * @brief usart send buffer function
 * @param buffer
 * @note this function will be called by isr until the buffer is once cleared
 */
void GBS_USART_Send(void);

void GBS_USART_Write_Char(char* c, uint8_t size);

/**********************************PROTOCAL******************************************/
/**
 * standard command 'C'+'num'
 * standard data    'D'+'data'+' '
 * please do not send space as data or command
 */

#define SEND_0  "DReceive"
#define SEND_1  "CReceive"
#define SEND_2  "NULL"
#define SEND_3  "NULL"
#define SEND_4  "NULL"
#define SEND_5  "NULL"
#define SEND_6  "NULL"
#define SEND_7  "NULL"

typedef struct 
{
    uint8_t cFlag:1;
    uint8_t dFlag:1;
    uint8_t rFlag:1;
}usartFlag_t;

typedef struct 
{
    //receive bits
    uint8_t r0:1;
    uint8_t r1:1;
    uint8_t r2:1;
    uint8_t r3:1;
    uint8_t r4:1;
    uint8_t r5:1;
    uint8_t r6:1;
    uint8_t r7:1;

    //send bits
    uint8_t s0:1;
    uint8_t s1:1;
    uint8_t s2:1;
    uint8_t s3:1;
    uint8_t s4:1;
    uint8_t s5:1;
    uint8_t s6:1;
    uint8_t s7:1;
}ctrl_t;

ctrl_t ctrlBits;    //received from master

usartFlag_t uFlag;

/**
 * @note call it in your main function
 */
void GBS_Message_Update();

#endif