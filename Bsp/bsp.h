/**
  **********************************  STM8S  ***********************************
  * @文件名     ： bsp.h
  * @作者       ： Huang Fugui
  * @库版本     ： V2.2.0
  * @文件版本   ： V1.0.1
  * @日期       ： 2014年12月17日
  * @摘要       ： 板级支持包头文件
  ******************************************************************************/

/* 定义防止递归包含 ----------------------------------------------------------*/
#ifndef _BSP_H
#define _BSP_H

/* 包含的头文件 --------------------------------------------------------------*/
#include "stm8s.h"


/* 宏定义 --------------------------------------------------------------------*/
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


/* 函数申明 ------------------------------------------------------------------*/
void CLK_Configuration(void);
void GPIO_Basic_Configuration(void);
void Interrupt_Configuration(void);
void BSP_Initializes(void);


#endif /* _BSP_H */

/***** Copyright (C)2014 HuangFugui. All Rights Reserved ***** END OF FILE *****/
