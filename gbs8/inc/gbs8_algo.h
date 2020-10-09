#ifndef __GBS8_ALGO_H
#define __GBS8_ALGO_H

#include <stdint.h>

/**
 *  @brief 3-bit demical to binary convertion
 *  @param dec demical number
 *  @return 0b
 *  @note 000 to 111
 */
uint8_t Demical_2_Binary(uint8_t dec);

/**
 *  @brief binary reader
 *  @param dec demical number
 *  @param len length
 *  @param num number
 */
uint8_t Read_Binary(uint8_t dec, uint8_t len, uint8_t num);

#endif