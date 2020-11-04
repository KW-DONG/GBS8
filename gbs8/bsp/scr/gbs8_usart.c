#include "gbs8_usart.h"
#include "gbs8_interrupt.h"
#include "gbs8_config.h"
#include <stdlib.h>


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
    //SPBRG = _XTAL_FREQ / baudRate / 16 - 1;
    SPBRG = 71;

    //set RX input
    TRISCbits.TRISC7 = 1;

    //set TX output
    TRISCbits.TRISC6 = 0;

    //enable serial ports
    TXSTAbits.TXEN = 1;
    RCSTAbits.CREN = 1;
    RCSTAbits.SPEN = 1;
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

void GBS_USART_Send(void)
{
    //PIE1bits.TXIE = 1;
    while (usartSendBuffer.size>0)
    {
        TXREG = GBS_USART_Buffer_Read(&usartSendBuffer);
        while (TXSTAbits.TRMT==0);
    }
}

void GBS_USART_Receive(void)
{
    GBS_USART_Buffer_Write(&usartReceiveBuffer, RCREG);
}

void USART_TX_ISR()
{

}

void USART_RX_ISR()
{    
    if (uFlag.dFlag)
    {
        if (RCREG == ' ')
        {
            uFlag.dFlag = 0;
            uFlag.rFlag = 1;
            
            //received
            ctrlBits.s0 = 1;

            while (TXSTAbits.TRMT==0);
        }
        else    GBS_USART_Receive();
    }
    else if (RCREG == 'C')
    {
        if (uFlag.dFlag != 1)   uFlag.cFlag = 1;
    }
    else if (RCREG == 'D')
    {
        if (uFlag.cFlag != 1)   uFlag.dFlag = 1;
    }
    else if (uFlag.cFlag == 1)
    {
        switch (RCREG)
        {
        case '0':
            ctrlBits.r0 = 1;
            break;
        case '1':
            ctrlBits.r1 = 1;
            break;
        case '2':
            ctrlBits.r2 = 1;
            break;
        case '3':
            ctrlBits.r3 = 1;
            break;
        case '4':
            ctrlBits.r4 = 1;
            break;
        case '5':
            ctrlBits.r5 = 1;
            break;
        case '6':
            ctrlBits.r6 = 1;
            break;
        case '7':
            ctrlBits.r7 = 1;
            break;
        }
        uFlag.cFlag = 0;
        //recieved
        ctrlBits.s1 = 1;
    }
}


void GBS_USART_Write_Char(char* c, uint8_t size)
{
    if (size < (USART_BUFFER_SIZE-2))
    {
        for (uint8_t i = 0; i<(size-1); i++)
        {
            //while (usartSendBuffer.size==USART_BUFFER_SIZE)
            GBS_USART_Buffer_Write(&usartSendBuffer, c[i]);
        }
        GBS_USART_Buffer_Write(&usartSendBuffer, 13);
        GBS_USART_Buffer_Write(&usartSendBuffer, 10);
    }
}

void GBS_Message_Update()
{
    if (ctrlBits.s0)
    {
        ctrlBits.s0 = 0;
        GBS_USART_Write_Char(SEND_0, sizeof(SEND_0));
        GBS_USART_Send();
    }
    if (ctrlBits.s1)
    {
        ctrlBits.s0 = 0;
        GBS_USART_Write_Char(SEND_0, sizeof(SEND_0));
        GBS_USART_Send();
    }
    if (ctrlBits.s2)
    {
        ctrlBits.s0 = 0;
        GBS_USART_Write_Char(SEND_0, sizeof(SEND_0));
        GBS_USART_Send();
    }
    if (ctrlBits.s3)
    {
        ctrlBits.s0 = 0;
        GBS_USART_Write_Char(SEND_0, sizeof(SEND_0));
        GBS_USART_Send();
    }
    if (ctrlBits.s4)
    {
        ctrlBits.s0 = 0;
        GBS_USART_Write_Char(SEND_0, sizeof(SEND_0));
        GBS_USART_Send();
    }
    if (ctrlBits.s5)
    {
        ctrlBits.s0 = 0;
        GBS_USART_Write_Char(SEND_0, sizeof(SEND_0));
        GBS_USART_Send();
    }
    if (ctrlBits.s6)
    {
        ctrlBits.s0 = 0;
        GBS_USART_Write_Char(SEND_0, sizeof(SEND_0));
        GBS_USART_Send();
    }
    if (ctrlBits.s7)
    {
        ctrlBits.s0 = 0;
        GBS_USART_Write_Char(SEND_0, sizeof(SEND_0));
        GBS_USART_Send();
    }

}