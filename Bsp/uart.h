/**
  **********************************  STM8S  ***********************************
  * @文件名     ： uart.h
  * @作者       ： Huang Fugui
  * @库版本     ： V2.2.0
  * @文件版本   ： V1.0.1
  * @日期       ： 2014年12月17日
  * @摘要       ： UART底层头文件
  ******************************************************************************/

/* 定义防止递归包含 ----------------------------------------------------------*/
#ifndef _UART_H
#define _UART_H

/* 包含的头文件 --------------------------------------------------------------*/
#include "stm8s.h"


/* 宏定义 --------------------------------------------------------------------*/
#define PORT_RS485EN              GPIOD
#define PIN_RS485EN               GPIO_PIN_2

                                                           //ES485接收使能
#define RS485EN_RE                (PORT_RS485EN->ODR &= (uint8_t)(~PIN_RS485EN))
                                                           //ES485发送使能
#define RS485EN_DE                (PORT_RS485EN->ODR |= (uint8_t)PIN_RS485EN)

/* 函数申明 ------------------------------------------------------------------*/
void UART_Initializes(void);
void UART_SendByte(uint8_t Data);
void UART_SendString(uint8_t *String, uint8_t Length);
void RS485_Initializes(void);
void RS485_SendString(uint8_t *String, uint8_t Length);


#endif /* _UART_H */

/*** Copyright (C) 2014  Chengdu Finchos Electronics Co., Ltd  ***END OF FILE***/
