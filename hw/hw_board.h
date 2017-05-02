#ifndef __HW_BOARD_H__
#define __HW_BOARD_H__

#include "hw_mcu.h"

void hw_board_init(void);

void hw_board_delay_us(uint16_t us);
void hw_board_delay_ms(uint16_t ms);

#endif

