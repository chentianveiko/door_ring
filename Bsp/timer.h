/**
  **********************************  STM8S  ***********************************
  * @�ļ���     �� timer.c
  * @����       �� Huang Fugui
  * @��汾     �� V2.2.0
  * @�ļ��汾   �� V1.0.1
  * @����       �� 2014��12��22��
  * @ժҪ       �� TIMERͷ�ļ�
  ******************************************************************************/

/* �����ֹ�ݹ���� ----------------------------------------------------------*/
#ifndef _TIMER_H
#define _TIMER_H

/* ������ͷ�ļ� --------------------------------------------------------------*/
#include "stm8s.h"


/* �궨�� --------------------------------------------------------------------*/
/* �滻��ʱ����ʱ�ӿ� */
#define TIMTiming1_Ns             TIM2_Timing_Ns
#define TIMTiming1_Off            TIM2_Timing_Off

#define TIMDelay1_N10us           TIM1_Delay_N10us
#define TIMDelay1_Nms             TIM1_Delay_Nms

/* �������� ------------------------------------------------------------------*/
void TIMER_Initializes(void);
void TIM2_Start(void);
void TIM2_ClearCNT(void);
void TIM2_RUN_OUT_Timer(uint16_t *Nsec,uint16_t *Nsec2);

void TIM1_Delay_N10us(uint16_t Times);
void TIM1_Delay_Nms(uint16_t Times);
void TIM1_Delay_Ns(uint16_t Nsec);


#endif /* _TIMER_BSP_H */

/***** Copyright (C)2014 HuangFugui. All Rights Reserved ***** END OF FILE *****/
