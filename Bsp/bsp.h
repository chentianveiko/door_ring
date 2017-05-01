/**
  **********************************  STM8S  ***********************************
  * @�ļ���     �� bsp.h
  * @����       �� Huang Fugui
  * @��汾     �� V2.2.0
  * @�ļ��汾   �� V1.0.1
  * @����       �� 2014��12��17��
  * @ժҪ       �� �弶֧�ְ�ͷ�ļ�
  ******************************************************************************/

/* �����ֹ�ݹ���� ----------------------------------------------------------*/
#ifndef _BSP_H
#define _BSP_H

/* ������ͷ�ļ� --------------------------------------------------------------*/
#include "stm8s.h"


/* �궨�� --------------------------------------------------------------------*/
#define PORT_LED_RED              GPIOD
#define PORT_LED_GREEN            GPIOA

#define PIN_LED_RED               GPIO_PIN_4
#define PIN_LED_GREEN             GPIO_PIN_3

/* LED */
#define LED_RED_ON                (PORT_LED_RED->ODR |= (uint8_t)PIN_LED_RED)
#define LED_RED_OFF               (PORT_LED_RED->ODR &= (uint8_t)(~PIN_LED_RED))
#define LED_RED_TOGGLE            (PORT_LED_RED->ODR ^= (uint8_t)PIN_LED_RED)

#define LED_GREEN_ON              (PORT_LED_GREEN->ODR |= (uint8_t)PIN_LED_GREEN)
#define LED_GREEN_OFF             (PORT_LED_GREEN->ODR &= (uint8_t)(~PIN_LED_GREEN))
#define LED_GREEN_TOGGLE          (PORT_LED_GREEN->ODR ^= (uint8_t)PIN_LED_GREEN)


/* �������� ------------------------------------------------------------------*/
void CLK_Configuration(void);
void GPIO_Basic_Configuration(void);
void Interrupt_Configuration(void);
void BSP_Initializes(void);


#endif /* _BSP_H */

/***** Copyright (C)2014 HuangFugui. All Rights Reserved ***** END OF FILE *****/
