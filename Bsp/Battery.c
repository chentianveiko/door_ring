
#include "Battery.h"
#include "NY3P.h"
#include "timer.h"

/*******************************************************************************************
*����:ADC_Config
*���:��
*����:��
*����:����ADCģ���Լ���ӦIO�ܽ�
*����:
*����:YangGuo
*ʱ��:2014-9-9
*******************************************************************************************/
void ADC_Config(void)
{
  	GPIO_Init( PORT_POWERCheck,Pin_POWERCheck,GPIO_MODE_IN_FL_NO_IT );//ADC1ͨ��0 I/O����
	ADC1_Init(ADC1_CONVERSIONMODE_SINGLE, 	        /* ����ת�� */
			  ADC1_CHANNEL_1,		/* ͨ��ѡ�� */
			  ADC1_PRESSEL_FCPU_D2,		//Ԥ��Ƶ
			  ADC1_EXTTRIG_TIM,		//�����¼�
			  DISABLE,			//�ⲿ����״̬
			  ADC1_ALIGN_RIGHT,		//���ݶ��뷽ʽ
			  ADC1_SCHMITTTRIG_CHANNEL0,	//ѡ���Ӧͨ����ʩ���ش�����
			  DISABLE);			//ָ����ʩ���ش�����״̬

	ADC1_Cmd(DISABLE);  /* ����ADCģ�� */
}
/*******************************************************************************************
*����:bubbleSort
*���:  arr -- Ҫ���������
*       n   -- Ҫ�����ǰn������Ԫ�ظ���
*����: arr���кõ�����
*����:ð������
*����:bubbleSort(arr,5);
*����:ChenTian
*ʱ��:2014-10-11
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
*����:SystemPowerDetict
*���:��
*����:��
*����:��ѹ���
*����:
*����:YangGuo
*ʱ��:2014-9-10
*******************************************************************************************/
uint16_t GetSystemPower(void)
{
  uint16_t Power[10];
  uint32_t PowerSUM;
  uint8_t i;
  
  TIM1_Delay_Nms(300);
  
  /* ��ʼ��ȡADC�Ĵ���ֵ--����������ȡ�ڶ���ֵ��Ч */
  ADC1_Cmd(ENABLE);
  for(i=0;i<10;i++)
  {
    ADC1_StartConversion();					//����ת��
    while( RESET == ADC1_GetFlagStatus(ADC1_FLAG_EOC));	        //�ȴ�ת�����
    Power[i] = ADC1_GetConversionValue();				//��ȡת�����
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










