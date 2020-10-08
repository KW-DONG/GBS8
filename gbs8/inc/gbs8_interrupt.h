#ifndef __GBS8_INTERRUPT_H
#define __GBS8_INTERRUPT_H

#include <pic16f887.h>
#include <xc.h>
#include <stdint.h>

#define EXTI_FLG    INTCONbits.INTF
#define CN_FLG      INTCONbits.RBIF


//Interrupt Service Routine
//There is no vectored interrupt controller (VIC) used in PIC16F887
//So ignore the interrupt vector

//write your ISR in the following functions
void EXTI_ISR();

void CNIT_ISR();

/**
 * @brief config external interrupts
 * @arg state: enable or disable
 * @arg mode: rising or falling
 * @note only PIN_9 available
 */
void GBS_EXTI_Config(uint8_t mode);

/**
 * @brief config change notification interrupts
 * @note PORTB
 */
void GBS_CNIT_Config(uint8_t mode);

void GBS_Interrupt_Init();

void GBS_Interrupt_Disable();


#endif