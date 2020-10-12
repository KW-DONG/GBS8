#include "gbs8_usart.h"
#include "gbs8_interrupt.h"

void GBS_USART_Init()
{
    //enable interrupts
    PIE1bits.TXIE = 1;
    PIE1bits.RCIE = 1;

    //enable serial ports
    TXSTAbits.TXEN = 1;
    RCSTAbits.CREN = 1;

}



uint8_t GBS_USART_Buffer_Write(USART_buffer_t* buffer, uint8_t value)
{
    if (buffer->size<USART_BUFFER_SIZE)
    {
        buffer->buffer[buffer->tail] = value;
        buffer->size++;
        buffer->tail = (buffer->tail + 1)%USART_BUFFER_SIZE;
        
    }
}

uint8_t GBS_USART_Buffer_Read(USART_buffer_t* buffer)
{
    uint8_t result;
    if (buffer->size>0)
    {
        result =  buffer->buffer[buffer->head];
        buffer->head = (buffer->head + 1)%USART_BUFFER_SIZE;
        buffer->size--;
        return result;
    }
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

void USART_TX_ISR()
{
    GBS_USART_Send(&usartSendBuffer);
}

void USART_RX_ISR()
{
    GBS_USART_Receive(&usartReceiveBuffer);
}