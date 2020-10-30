#include "gbs8_usart.h"
#include "gbs8_interrupt.h"
#include "gbs8_config.h"


void GBS_USART_Init(uint16_t baudRate)
{
    //enable interrupts
    PIE1bits.TXIE = 0;
    PIE1bits.RCIE = 1;
    
    TXSTAbits.TX9 = 0;

    //use asynchronous mode
    TXSTAbits.SYNC = 0;
    RCSTAbits.RX9 = 0;
    BAUDCTLbits.BRG16 = 0;

    //send break character bit
    TXSTAbits.SENDB = 0;

    //high boud rate select
    TXSTAbits.BRGH = 1;

    //set baud rate
    SPBRG = _XTAL_FREQ / baudRate / 16 - 1;

    //set RX input
    TRISCbits.TRISC7 = 1;

    //set TX output
    TRISCbits.TRISC6 = 0;

    //enable serial ports
    TXSTAbits.TXEN = 1;
    RCSTAbits.CREN = 1;
}

void GBS_USART_Buffer_Write(USART_buffer_t* buffer, uint8_t value)
{
    buffer->buffer[buffer->tail] = value;
    buffer->tail = (buffer->tail + 1)%USART_BUFFER_SIZE;
    if (buffer->size<USART_BUFFER_SIZE) buffer->size++;
}

uint8_t GBS_USART_Buffer_Read(USART_buffer_t* buffer)
{
    uint8_t result;
    if (buffer->size>0)
    {
        result = buffer->buffer[buffer->head];
        buffer->head = (buffer->head + 1)%USART_BUFFER_SIZE;
        buffer->size--;
        return result;
    }
}

void GBS_USART_Send(USART_buffer_t* buffer)
{
    PIE1bits.TXIE = 1;
    if (usartSendBuffer.size>0)
    {
        TXREG = GBS_USART_Buffer_Read(buffer);
        while (TXSTAbits.TRMT==0);
    }
}

void GBS_USART_Receive(USART_buffer_t* buffer)
{
    GBS_USART_Buffer_Write(buffer, RCREG);
}

void USART_TX_ISR()
{
    if ()
    GBS_USART_Send(&usartSendBuffer);
    PIE1bits.TXIE = 0;
}

void USART_RX_ISR()
{
    GBS_USART_Receive(&usartReceiveBuffer);
}