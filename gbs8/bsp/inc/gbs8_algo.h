#ifndef __GBS8_ALGO_H
#define __GBS8_ALGO_H

#include <stdint.h>


/**
 *  @brief binary reader
 *  @param dec demical
 *  @param num number
 */
uint8_t Read_Binary(uint8_t dec, uint8_t num);


uint16_t Register_Joint(uint8_t regH, uint8_t regL);

/**
 *  @brief 10-bits register decoupler
 *  @param regH 8-bits register
 *  @param regL 2-bits register
 *  @param reg  10-bits register
 */
void Reg10_Decouple(uint8_t* regH, uint8_t* regL, uint16_t reg);

#endif