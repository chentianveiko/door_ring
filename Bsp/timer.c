/**
  **********************************  STM8S  ***********************************
  * @�ļ���     �� timer.c
  * @����       �� Huang Fugui
  * @��汾     �� V2.2.0
  * @�ļ��汾   �� V1.0.1
  * @����       �� 2014��12��22��
  * @ժҪ       �� TIMERԴ�ļ�
  ******************************************************************************/
/*----------------------------------------------------------------------------
  �汾����˵��:
  2012-10-14 V1.0.0:ԭ��
  2014-12-22 V1.0.1:�޸Ŀ�(����V2.2.0)���淶�Ű桢����
  ----------------------------------------------------------------------------*/
/* ������ͷ�ļ� --------------------------------------------------------------*/
#include "timer.h"
#include "global_variable.h"


/************************************************
�������� �� TIMER_Initializes
��    �� �� ��ʱ����ʼ��
��    �� �� ��
�� �� ֵ �� ��
��    �� �� Huang Fugui
*************************************************/
void TIMER_Initializes(void)
{
  TIM2_TimeBaseInit(TIM2_PRESCALER_4096, 3906);  //TIM2��ʱ1�� (16M �� 4096 * 3096)
  TIM2_OC1Init(TIM2_OCMODE_TIMING, TIM2_OUTPUTSTATE_DISABLE, 0, TIM2_OCPOLARITY_HIGH);
  TIM2->IER |= (uint8_t)TIM2_IT_CC1;
                                             
  TIM1_TimeBaseInit(15, TIM1_COUNTERMODE_UP, 9, 0);//TIM1��ʱ10us (16 * 10 = 160)
  TIM1_OC1Init(TIM1_OCMODE_TIMING, TIM1_OUTPUTSTATE_DISABLE, TIM1_OUTPUTNSTATE_DISABLE,
               0, TIM1_OCPOLARITY_HIGH, TIM1_OCNPOLARITY_HIGH, TIM1_OCIDLESTATE_SET,
               TIM1_OCNIDLESTATE_SET);
}
/************************************************
�������� �� TIM2_Start
��    �� �� ������ʱ��2
��    �� �� ��
�� �� ֵ �� ��
��    �� �� Veiko
*************************************************/
void TIM2_Start(void)
{
  TIM2->CR1 |= (uint8_t)TIM2_CR1_CEN;            //������ʱ��2
}
/************************************************
�������� �� TIM2_RUN_OUT_Timer
��    �� �� ʹ�ö�ʱ��2��Ϊ��ʱ��ʱ��,��ʱ��2��ʱ��
            ��Ϊ1s��ÿ�ν����жϺ󶼻ὫTIM2_OVER_Flag
            ��ΪTRUE�����øú����ͻ�ִ��Nsec��1������
            ��Ȼǰ����Nsecָ��ı���ֵΪ����0��ֵ
ע������ �� ���ڵ��øú���ǰ�򿪶�ʱ��2�ļ�������
��    �� �� Nsec -- ָ��ʱ��ʱ������ָ��
�� �� ֵ �� ��
��    �� �� Veiko
*************************************************/
void TIM2_RUN_OUT_Timer(uint16_t *Nsec,uint16_t *Nsec2)
{
  if(TIM2_OVER_Flag == TRUE)
  {
    TIM2_OVER_Flag = FALSE;
    if(Nsec != 0)
    {
      if((*Nsec) > 0)
      {
        *Nsec = (*Nsec)-1;
      }
    }
   
     if(Nsec2 != 0)
     {
        if((*Nsec2) > 0)
        {
          *Nsec2 = (*Nsec2)-1;
        }
     }
  }
}

/************************************************
�������� �� TIM2_ClearCNT
��    �� �� ��ն�ʱ���ļ�����
��    �� �� ��
�� �� ֵ �� ��
��    �� �� Veiko
*************************************************/
void TIM2_ClearCNT(void)
{
  TIM2_SetCounter(0);  /* ���CNT�Ĵ��� */
  TIM2_OVER_Flag = FALSE;
}

/************************************************
�������� �� TIM1_Delay_N10us
��    �� �� ��ʱ����ʱN��10us
��    �� �� Times --- Nֵ
�� �� ֵ �� ��
��    �� �� Huang Fugui
*************************************************/
void TIM1_Delay_N10us(uint16_t Times)
{
  TIM1->CR1 |= (uint8_t)TIM1_CR1_CEN;            //������ʱ��
  while(Times--)
  {
    while((TIM1->SR1 & TIM1_SR1_CC1IF) == RESET);//�ȴ�10us��ʱ��
    TIM1->SR1 &= ~TIM1_SR1_CC1IF;                //�����־
  }
  TIM1->CR1 &= (uint8_t)(~TIM1_CR1_CEN);         //�رն�ʱ��
}

/************************************************
�������� �� TIM1_Delay_Nms
��    �� �� ��ʱ����ʱNms
��    �� �� Times --- Nֵ
�� �� ֵ �� ��
��    �� �� Huang Fugui
*************************************************/
void TIM1_Delay_Nms(uint16_t Times)
{
  while(Times--)
  {
    TIM1_Delay_N10us(100);
  }
}
/************************************************
�������� �� TIM1_Delay_Ns
��    �� �� ��ʱ����ʱNs
��    �� �� Nsec --- Nֵ
�� �� ֵ �� ��
��    �� �� Veiko
*************************************************/
void TIM1_Delay_Ns(uint16_t Nsec)
{
  while(Nsec--)
  {
    TIM1_Delay_Nms(1000);
  }
}


/***** Copyright (C)2014 HuangFugui. All Rights Reserved ***** END OF FILE *****/
