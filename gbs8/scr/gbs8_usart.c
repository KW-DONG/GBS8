#include "gbs8_usart.h"

void GBS_USART_Init()
{
    //enable interrupts
    PIE1bits.TXIE = 1;
    PIE1bits.RCIE = 1;

    //enable serial ports
    TXSTAbits.TXEN = 1;
    RCSTAbits.CREN = 1;


}

void GBS_USART_Send(USART_buffer_t* buffer)
{
    if (buffer->size>0)
    {
        TXREG = buffer->buffer[buffer->head];
        buffer->head = (buffer->head + 1)%USART_BUFFER_SIZE;
        buffer->size--;
    }
    
    
}

void GBS_USART_Receive(USART_buffer_t* buffer)
{
    buffer->buffer[buffer->tail] = RCREG;
    buffer->tail = (buffer->tail + 1)%USART_BUFFER_SIZE;
    if (buffer->size<USART_BUFFER_SIZE) buffer->size++;
}