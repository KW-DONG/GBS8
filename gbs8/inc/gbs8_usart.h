#ifndef __GBS8_USART_H
#define __GBS8_USART_H

#include <pic16f887.h>
#include <xc.h>
#include <stdint.h>

#define USART_BUFFER_SIZE   8

extern USART_buffer_t usartReceiveBuffer;

extern USART_buffer_t usartSendBuffer;

typedef struct 
{
    uint8_t buffer[USART_BUFFER_SIZE];
    uint8_t head;
    uint8_t tail;
    uint8_t size;
}USART_buffer_t;

uint8_t GBS_USART_Buffer_Read(USART_buffer_t* buffer);

uint8_t GBS_USART_Buffer_Write(USART_buffer_t* buffer, uint8_t value);

void GBS_USART_Init();

void GBS_USART_Receive();

void GBS_USART_Send();

#endif