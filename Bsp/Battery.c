
#include "Battery.h"
#include "NY3P.h"
#include "timer.h"

/*******************************************************************************************
*函数:ADC_Config
*入参:无
*返回:无
*功能:配置ADC模块以及相应IO管脚
*范例:
*作者:YangGuo
*时间:2014-9-9
*******************************************************************************************/
void ADC_Config(void)
{
  	GPIO_Init( PORT_POWERCheck,Pin_POWERCheck,GPIO_MODE_IN_FL_NO_IT );//ADC1通道0 I/O配置
	ADC1_Init(ADC1_CONVERSIONMODE_SINGLE, 	        /* 单次转换 */
			  ADC1_CHANNEL_1,		/* 通道选择 */
			  ADC1_PRESSEL_FCPU_D2,		//预分频
			  ADC1_EXTTRIG_TIM,		//触发事件
			  DISABLE,			//外部触发状态
			  ADC1_ALIGN_RIGHT,		//数据对齐方式
			  ADC1_SCHMITTTRIG_CHANNEL0,	//选择对应通道的施密特触发器
			  DISABLE);			//指定的施密特触发器状态

	ADC1_Cmd(DISABLE);  /* 除能ADC模块 */
}
/*******************************************************************************************
*函数:bubbleSort
*入参:  arr -- 要排序的数组
*       n   -- 要排序的前n个数组元素个数
*返回: arr排列好的数组
*功能:冒泡排序
*范例:bubbleSort(arr,5);
*作者:ChenTian
*时间:2014-10-11
*******************************************************************************************/
void bubbleSort(uint16_t arr[],uint16_t n)
{
    int i,j,t;
    for(i=0;i<n-1;i++)
    {
        for(j=0;j<n-i-1;j++)
        {
            if(arr[j+1]<arr[j])
            {
                t=arr[j+1];
                arr[j+1]=arr[j];
                arr[j]=t;
            }
        }
    }
}
/*******************************************************************************************
*函数:SystemPowerDetict
*入参:无
*返回:无
*功能:电压检测
*范例:
*作者:YangGuo
*时间:2014-9-10
*******************************************************************************************/
uint16_t GetSystemPower(void)
{
  uint16_t Power[10];
  uint32_t PowerSUM;
  uint8_t i;
  
  TIM1_Delay_Nms(300);
  
  /* 开始读取ADC寄存器值--连续读两次取第二次值有效 */
  ADC1_Cmd(ENABLE);
  for(i=0;i<10;i++)
  {
    ADC1_StartConversion();					//启动转换
    while( RESET == ADC1_GetFlagStatus(ADC1_FLAG_EOC));	        //等待转换完成
    Power[i] = ADC1_GetConversionValue();				//读取转换结果
  }
  
  bubbleSort(Power,10);
  PowerSUM = 0;
  for(i=3;i<7;i++)
  {
    PowerSUM += Power[i];
  }
  PowerSUM = PowerSUM/4;
  
  ADC1_Cmd(DISABLE);
  	
  return ((uint16_t)PowerSUM);
}










