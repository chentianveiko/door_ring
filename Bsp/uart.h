/**
  **********************************  STM8S  ***********************************
  * @�ļ���     �� uart.h
  * @����       �� Huang Fugui
  * @��汾     �� V2.2.0
  * @�ļ��汾   �� V1.0.1
  * @����       �� 2014��12��17��
  * @ժҪ       �� UART�ײ�ͷ�ļ�
  ******************************************************************************/

/* �����ֹ�ݹ���� ----------------------------------------------------------*/
#ifndef _UART_H
#define _UART_H

/* ������ͷ�ļ� --------------------------------------------------------------*/
#include "stm8s.h"


/* �궨�� --------------------------------------------------------------------*/
#define PORT_RS485EN              GPIOD
#define PIN_RS485EN               GPIO_PIN_2

                                                           //ES485����ʹ��
#define RS485EN_RE                (PORT_RS485EN->ODR &= (uint8_t)(~PIN_RS485EN))
                                                           //ES485����ʹ��
#define RS485EN_DE                (PORT_RS485EN->ODR |= (uint8_t)PIN_RS485EN)

/* �������� ------------------------------------------------------------------*/
void UART_Initializes(void);
void UART_SendByte(uint8_t Data);
void UART_SendString(uint8_t *String, uint8_t Length);
void RS485_Initializes(void);
void RS485_SendString(uint8_t *String, uint8_t Length);


#endif /* _UART_H */

/*** Copyright (C) 2014  Chengdu Finchos Electronics Co., Ltd  ***END OF FILE***/
