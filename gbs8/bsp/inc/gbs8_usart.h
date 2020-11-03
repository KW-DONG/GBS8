#ifndef __GBS8_USART_H
#define __GBS8_USART_H

#include <pic16f887.h>
#include <xc.h>
#include <stdint.h>
#include <stdlib.h>

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

typedef struct 
{
    uint8_t cFlag:1;
    uint8_t dFlag:1;
    uint8_t rFlag:1;
}usartFlag_t;

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


usartFlag_t uFlag;

void GBS_Ctrl_Update(void);

uint8_t GBS_Ctrl_Read(uint8_t i);

#define COMMAND_FB  GBS_USART_Write_Char(char* c, uint8_t size)

#define SEND_CHAR(X)    GBS_USART_Write_Char(X, sizeof(X));


void GBS_Feedback();

#endif