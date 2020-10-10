#ifndef __GBS8_INTERRUPT_H
#define __GBS8_INTERRUPT_H

#include <pic16f887.h>
#include <xc.h>
#include <stdint.h>

#define INT_ENABLE  1
#define INT_DISABLE 0

#define EXTI_FLG    INTCONbits.INTF //INT External Interrupt Flag bit
#define CN_FLG      INTCONbits.RBIF //PORTB Change Interrupt Flag bit
#define TIM0_FLG    INTCONbits.T0IF //TIMER0 Overflow Interrupt Flag bit


//Interrupt Service Routine
//There is no vectored interrupt controller (VIC) used in PIC16F887
//So ignore the interrupt vector

/*******************************************ISR*******************************************************/
void EXTI_ISR();

void CNIT_ISR();

void T0I_ISR();

void T1I_ISR();

void T2I_ISR();

void ADC_ISR();

void EUSART_ISR();

void MSSP_ISR();



/******************************************CONFIG*****************************************************/

/**
 * @brief config external interrupts
 * @arg mode: rising or falling
 * @note only PIN_9 available
 */
void GBS_EXTI_Config(uint8_t mode);

/**
 * @brief config change notification interrupts
 * @note PORTB
 */
void GBS_CNIT_Config(uint8_t mode);

/**
 * @brief config timer0 overflow interrupt
 * @note  please config the corresponding timer first
 */
void GBS_T0I_Config(uint8_t mode);

/**
 * @brief config timer1 overflow interrupt
 * @note  please config the corresponding timer first
 */
void GBS_T1I_Config(uint8_t mode);

/**************************************GLOBAL****************************************************/

/**
 * @brief Initialize all the interrupts
 */
void GBS_Interrupt_Init();

/**
 * @brief Enable global interrupts
 */
void GBS_Interrupt_Enable();

/**
 * @brief Disable global interrupts
 */
void GBS_Interrupt_Disable();


#endif