/**
  **********************************  STM8S  ***********************************
  * @文件名     ： timer.c
  * @作者       ： Huang Fugui
  * @库版本     ： V2.2.0
  * @文件版本   ： V1.0.1
  * @日期       ： 2014年12月22日
  * @摘要       ： TIMER头文件
  ******************************************************************************/

/* 定义防止递归包含 ----------------------------------------------------------*/
#ifndef _TIMER_H
#define _TIMER_H

/* 包含的头文件 --------------------------------------------------------------*/
#include "stm8s.h"


/* 宏定义 --------------------------------------------------------------------*/
/* 替换定时、延时接口 */
#define TIMTiming1_Ns             TIM2_Timing_Ns
#define TIMTiming1_Off            TIM2_Timing_Off

#define TIMDelay1_N10us           TIM1_Delay_N10us
#define TIMDelay1_Nms             TIM1_Delay_Nms

/* 函数申明 ------------------------------------------------------------------*/
void TIMER_Initializes(void);
void TIM2_Start(void);
void TIM2_ClearCNT(void);
void TIM2_RUN_OUT_Timer(uint16_t *Nsec,uint16_t *Nsec2);

void TIM1_Delay_N10us(uint16_t Times);
void TIM1_Delay_Nms(uint16_t Times);
void TIM1_Delay_Ns(uint16_t Nsec);


#endif /* _TIMER_BSP_H */

/***** Copyright (C)2014 HuangFugui. All Rights Reserved ***** END OF FILE *****/
