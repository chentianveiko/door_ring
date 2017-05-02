
#ifndef _UART_H
#define _UART_H

#include "stm8s.h"

#define PORT_RS485EN              GPIOD
#define PIN_RS485EN               GPIO_PIN_2

#define RS485EN_RE                (PORT_RS485EN->ODR &= (uint8_t)(~PIN_RS485EN))
#define RS485EN_DE                (PORT_RS485EN->ODR |= (uint8_t)PIN_RS485EN)

void UART_Initializes(void);
void UART_SendByte(uint8_t Data);
void UART_SendString(uint8_t *String, uint8_t Length);
void RS485_Initializes(void);
void RS485_SendString(uint8_t *String, uint8_t Length);


#endif /* _UART_H */

/*** Copyright (C) 2014  Chengdu Finchos Electronics Co., Ltd  ***END OF FILE***/
