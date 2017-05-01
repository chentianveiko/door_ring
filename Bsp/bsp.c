/**
  **********************************  STM8S  ***********************************
  * @文件名     ： bsp.c
  * @作者       ： Huang Fugui
  * @库版本     ： V2.2.0
  * @文件版本   ： V1.0.1
  * @日期       ： 2014年12月17日
  * @摘要       ： 板级支持包源文件
  ******************************************************************************/
/*----------------------------------------------------------------------------
  版本更新说明:
  2014-10-14 V1.0.0:基于标准库V2.1.0
  2014-12-17 V1.0.1:基于标准库V2.2.0、规范排版
  ----------------------------------------------------------------------------*/
/* 包含的头文件 --------------------------------------------------------------*/
#include "bsp.h"


/************************************************
函数名称 ： CLK_Configuration
功    能 ： 时钟配置
参    数 ： 无
返 回 值 ： 无
作    者 ： Huang Fugui
修    改 :  Veiko
*************************************************/
void CLK_Configuration(void)
{
  CLK_HSIPrescalerConfig(CLK_PRESCALER_HSIDIV1); //HSI = 16M (1分频)
  while(CLK_GetFlagStatus(CLK_FLAG_HSIRDY) == RESET);  /* 等待时钟切换完成并稳定 */
}

/************************************************
函数名称 ： GPIO_Basic_Configuration
功    能 ： 基本IO引脚配置
参    数 ： 无
返 回 值 ： 无
作    者 ： Huang Fugui
*************************************************/
void GPIO_Basic_Configuration(void)
{
nop();
#if 0
  /* 系统时钟输出测试 */
//  GPIO_Init(GPIOC, (GPIO_Pin_TypeDef)GPIO_PIN_4, GPIO_MODE_OUT_PP_HIGH_FAST);
//  CLK_CCOCmd(ENABLE);
#endif
}

/************************************************
函数名称 ： Interrupt_Configuration
功    能 ： 中断配置
参    数 ： 无
返 回 值 ： 无
作    者 ： Huang Fugui
*************************************************/
void Interrupt_Configuration(void)
{
  enableInterrupts();
}

/************************************************
函数名称 ： BSP_Initializes
功    能 ： 板级支持包初始化
参    数 ： 无
返 回 值 ： 无
作    者 ： Huang Fugui
*************************************************/
void BSP_Initializes(void)
{
  CLK_Configuration();    /* 配置时钟 */
  GPIO_Basic_Configuration();
}


/***** Copyright (C)2014 HuangFugui. All Rights Reserved ***** END OF FILE *****/
