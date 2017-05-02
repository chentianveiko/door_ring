/**
  **********************************  STM8S  ***********************************
  * @�ļ���     �� uart.c
  * @����       �� Huang Fugui
  * @��汾     �� V2.2.0
  * @�ļ��汾   �� V1.0.1
  * @����       �� 2014��12��17��
  * @ժҪ       �� UART�ײ�Դ�ļ�
  ******************************************************************************/
/*----------------------------------------------------------------------------
  �汾����˵��:
  2014-10-14 V1.0.0:���ڱ�׼��V2.1.0
  2014-12-17 V1.0.1:���ڱ�׼��V2.2.0���淶�Ű�
  ----------------------------------------------------------------------------*/
/* ������ͷ�ļ� --------------------------------------------------------------*/
#include "uart.h"
#include "timer.h"
#include "global_variable.h"

void UART_Initializes(void)
{
  UART1_Init((uint32_t)9600, UART1_WORDLENGTH_8D, UART1_STOPBITS_1, UART1_PARITY_NO,
                UART1_SYNCMODE_CLOCK_DISABLE, UART1_MODE_TXRX_ENABLE);

  UART1_Cmd(ENABLE); 

  UART1_ITConfig(UART1_IT_RXNE, ENABLE);
}
void UART_SendByte(uint8_t Data)
{
  while((UART1->SR & (uint8_t)UART1_FLAG_TXE) == (uint8_t)0x00);
  UART1->DR = Data;
}
void UART_SendString(uint8_t *String, uint8_t Length)
{
  while(Length--)
  {
    UART_SendByte(*String);
    String++;
  }
}
void RS485_Initializes(void)
{
  UART_Initializes();
  GPIO_Init(PORT_RS485EN, (GPIO_Pin_TypeDef)PIN_RS485EN, GPIO_MODE_OUT_PP_HIGH_FAST);
  RS485EN_RE;
}

void RS485_SendString(uint8_t *String, uint8_t Length)
{
  UART1->CR2 &= (uint8_t)(~0x20);              

  RS485EN_DE;
  TIMDelay1_N10us(2);                           

  while(Length--)
  {
    UART_SendByte(*String);
    String++;
  }

  TIMDelay1_N10us(100);                          
  RS485EN_RE;
  TIMDelay1_N10us(10);                        

  UART1->CR2 |= (uint8_t)0x20;          
  TIMDelay1_N10us(2);
  gRx_CMDAvailable = FLAG_N_VALID;
}



/*** Copyright (C) 2014  Chengdu Finchos Electronics Co., Ltd  ***END OF FILE***/
