#ifndef __GBS8_USART_H
#define __GBS8_USART_H

#include <pic16f887.h>
#include <xc.h>
#include <stdint.h>

#define USART_BUFFER_SIZE   128

typedef struct 
{
    uint8_t buffer[USART_BUFFER_SIZE];
    uint8_t head;
    uint8_t tail;
    uint8_t size;
}USART_buffer_t;

extern USART_buffer_t usartReceiveBuffer;

extern USART_buffer_t usartSendBuffer;

uint8_t GBS_USART_Buffer_Read(USART_buffer_t* buffer);

void GBS_USART_Buffer_Write(USART_buffer_t* buffer, uint8_t value[]);

void GBS_USART_Init(uint16_t baudRate);

void GBS_USART_Receive(USART_buffer_t* buffer);

/**
 * @brief usart send buffer function
 * @param buffer
 * @note this function will be called by isr until the buffer is once cleared
 */
void GBS_USART_Send(USART_buffer_t* buffer);

/**
 * @brief usart send bits function
 * @param bits
 * @note this function has a higher priority
 */
void GBS_USART_Send_Bits(uint8_t bits);

#endif