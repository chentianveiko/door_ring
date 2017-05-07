#ifndef __HW_USART_H__
#define __HW_USART_H__

#include "hw_mcu.h"
#include "stdbool.h"

#define USART_RX_BUFF_MAX    128


typedef struct{
	bool  read_lock;                    /* 只有为false时才能往数据区写数据 */
	uint16_t len;                       /* 记录接收的数据长度 */
	uint8_t  data[USART_RX_BUFF_MAX];   /* 存储接收到的数据 */
}hw_usart_rx_t;

typedef void (* hw_usart_rx_handler_t)(hw_usart_rx_t *s);

void hw_usart_init(void);
void hw_usart_write(uint8_t *data);
void hw_usart_write_len(uint8_t *data, uint16_t length);
void hw_usart_set_rx_handler(hw_usart_rx_handler_t handler);
void usr_print(const char *fmt, ...);


#endif
