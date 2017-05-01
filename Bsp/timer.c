/**
  **********************************  STM8S  ***********************************
  * @文件名     ： timer.c
  * @作者       ： Huang Fugui
  * @库版本     ： V2.2.0
  * @文件版本   ： V1.0.1
  * @日期       ： 2014年12月22日
  * @摘要       ： TIMER源文件
  ******************************************************************************/
/*----------------------------------------------------------------------------
  版本更新说明:
  2012-10-14 V1.0.0:原版
  2014-12-22 V1.0.1:修改库(基于V2.2.0)、规范排版、命名
  ----------------------------------------------------------------------------*/
/* 包含的头文件 --------------------------------------------------------------*/
#include "timer.h"
#include "global_variable.h"


/************************************************
函数名称 ： TIMER_Initializes
功    能 ： 定时器初始化
参    数 ： 无
返 回 值 ： 无
作    者 ： Huang Fugui
*************************************************/
void TIMER_Initializes(void)
{
  TIM2_TimeBaseInit(TIM2_PRESCALER_4096, 3906);  //TIM2定时1秒 (16M ≈ 4096 * 3096)
  TIM2_OC1Init(TIM2_OCMODE_TIMING, TIM2_OUTPUTSTATE_DISABLE, 0, TIM2_OCPOLARITY_HIGH);
  TIM2->IER |= (uint8_t)TIM2_IT_CC1;
                                             
  TIM1_TimeBaseInit(15, TIM1_COUNTERMODE_UP, 9, 0);//TIM1延时10us (16 * 10 = 160)
  TIM1_OC1Init(TIM1_OCMODE_TIMING, TIM1_OUTPUTSTATE_DISABLE, TIM1_OUTPUTNSTATE_DISABLE,
               0, TIM1_OCPOLARITY_HIGH, TIM1_OCNPOLARITY_HIGH, TIM1_OCIDLESTATE_SET,
               TIM1_OCNIDLESTATE_SET);
}
/************************************************
函数名称 ： TIM2_Start
功    能 ： 启动定时器2
参    数 ： 无
返 回 值 ： 无
作    者 ： Veiko
*************************************************/
void TIM2_Start(void)
{
  TIM2->CR1 |= (uint8_t)TIM2_CR1_CEN;            //启动定时器2
}
/************************************************
函数名称 ： TIM2_RUN_OUT_Timer
功    能 ： 使用定时器2作为超时定时器,定时器2定时周
            期为1s，每次进入中断后都会将TIM2_OVER_Flag
            置为TRUE，调用该函数就会执行Nsec减1操作，
            当然前提是Nsec指向的变量值为大于0的值
注意事项 ： 请在调用该函数前打开定时器2的计数功能
参    数 ： Nsec -- 指向超时定时变量的指针
返 回 值 ： 无
作    者 ： Veiko
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
函数名称 ： TIM2_ClearCNT
功    能 ： 清空定时器的计数器
参    数 ： 无
返 回 值 ： 无
作    者 ： Veiko
*************************************************/
void TIM2_ClearCNT(void)
{
  TIM2_SetCounter(0);  /* 清空CNT寄存器 */
  TIM2_OVER_Flag = FALSE;
}

/************************************************
函数名称 ： TIM1_Delay_N10us
功    能 ： 定时器延时N个10us
参    数 ： Times --- N值
返 回 值 ： 无
作    者 ： Huang Fugui
*************************************************/
void TIM1_Delay_N10us(uint16_t Times)
{
  TIM1->CR1 |= (uint8_t)TIM1_CR1_CEN;            //启动定时器
  while(Times--)
  {
    while((TIM1->SR1 & TIM1_SR1_CC1IF) == RESET);//等待10us延时到
    TIM1->SR1 &= ~TIM1_SR1_CC1IF;                //清除标志
  }
  TIM1->CR1 &= (uint8_t)(~TIM1_CR1_CEN);         //关闭定时器
}

/************************************************
函数名称 ： TIM1_Delay_Nms
功    能 ： 定时器延时Nms
参    数 ： Times --- N值
返 回 值 ： 无
作    者 ： Huang Fugui
*************************************************/
void TIM1_Delay_Nms(uint16_t Times)
{
  while(Times--)
  {
    TIM1_Delay_N10us(100);
  }
}
/************************************************
函数名称 ： TIM1_Delay_Ns
功    能 ： 定时器延时Ns
参    数 ： Nsec --- N值
返 回 值 ： 无
作    者 ： Veiko
*************************************************/
void TIM1_Delay_Ns(uint16_t Nsec)
{
  while(Nsec--)
  {
    TIM1_Delay_Nms(1000);
  }
}


/***** Copyright (C)2014 HuangFugui. All Rights Reserved ***** END OF FILE *****/
