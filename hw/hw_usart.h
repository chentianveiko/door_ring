#ifndef __HW_USART_H__
#define __HW_USART_H__

#include "hw_mcu.h"

typedef void (* hw_usart_rx_handler_t)(uint8_t ch);

void hw_usart_init(void);
void hw_usart_write(uint8_t *data, uint16_t length);
void hw_usart_set_rx_handler(hw_usart_rx_handler_t handler);


#endif
