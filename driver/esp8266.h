
#ifndef __esp8266_h
#define __esp8266_h

#include "hw_board.h"
#include "hw_usart.h"
#include "global_variable.h"

#define ESP_SOFT_TIMER   HW_ST_TIMER_3
#define ESP_WIFI_SSID_DEF  "CHT_LXPP"
#define ESP_WIFI_PWD_DEF   "13709009914"
#define ESP_SER_DEF        "\"chentianveiko.qicp.io\",15455"

#define esp_uart_send(data,len) hw_usart_write_len(data,len)

void esp_init(void);
void esp_send(uint8_t *p,uint8_t len);
void esp_usart_rx_handler(hw_usart_rx_t *s);

#endif
