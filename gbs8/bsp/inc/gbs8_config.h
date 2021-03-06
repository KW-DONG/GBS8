#ifndef __GBS8_CONFIG_H
#define __GBS8_CONFIG_H

#define _XTAL_FREQ 11059200     //11MHz

// CONFIG1
#pragma config FOSC = HS        // Oscillator Selection bits (XT oscillator: Crystal/resonator on RA6/OSC2/CLKOUT and RA7/OSC1/CLKIN)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled and can be enabled by SWDTEN bit of the WDTCON register)
#pragma config PWRTE = OFF       // Power-up Timer Enable bit (PWRT enabled)
#pragma config MCLRE = ON      // RE3/MCLR pin function select bit (RE3/MCLR pin function is digital input, MCLR internally tied to VDD)
#pragma config CP = OFF         // Code Protection bit (Program memory code protection is disabled)
#pragma config CPD = OFF        // Data Code Protection bit (Data memory code protection is disabled)
#pragma config BOREN = OFF      // Brown Out Reset Selection bits (BOR disabled)
#pragma config IESO = OFF       // Internal External Switchover bit (Internal/External Switchover mode is disabled)
#pragma config FCMEN = OFF      // Fail-Safe Clock Monitor Enabled bit (Fail-Safe Clock Monitor is disabled)
#pragma config LVP = OFF        // Low Voltage Programming Enable bit (RB3 pin has digital I/O, HV on MCLR must be used for programming)

// CONFIG2
#pragma config BOR4V = BOR21V   // Brown-out Reset Selection bit (Brown-out Reset set to 4.0V)
#pragma config WRT = OFF        // Flash Program Memory Self Write Enable bits (Write protection off)

// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.

// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.

/******************************************************INTERRUPTS**************************************************************/

//INT external interrupt
#define EXTI_EN     0

//1 rising, 2 falling
#define EXTI_MD     0   

//CN change notification interrupt
#define CNIT_EN     0

//TMR0 overflow interrupt
#define T0I_EN      0

//TMR1 overflow interrupt
#define T1I_EN      0

//TMR2 overflow interrupt
#define T2I_EN      0

//USART interrupt
#define USART_EN    1

/****************************************************TIMER********************************************************************/

/**
 * set TIMER0:
 *  0 as timer mode
 *  1 as counter mode
 *  2 as watchdog timer
 */
#define TIMER0       0

/**
 * set TIMER0_SOURCE_EDGE
 *  0 as Increment on low-to-high transition on T0CKI Pin
 *  1 as Increment on high-to-low transition on T0CKI Pin
 */
#if (TIMER0==2)
#define TIMER0_SOURCE_EDGE  0
#endif

/**
 * set TIMER1_GATE:
 * 0 as diable
 * 1 as enable
 */
#define TIMER1_GATE 0

#if (TIMER1_GATE==1)
#define TIMER1_GATE_DIR 0
#endif

#define TIMER2          0

/***********************************************USER****************************************/

#define USE_FSM         1

#if (USE_FSM)
#define BUTTON_START1   NULL
#define BUTTON_START2   NULL
#define BUTTON_STOP     NULL
#define BUTTON_LOCK     NULL

#define LED_START1(X)   NULL
#define LED_START2(X)   NULL
#define LED_STOP(X)     NULL
#define LED_LOCK(X)     NULL

#define TASK_NUM        10

#endif

#define USE_PROTOCAL    1


#endif