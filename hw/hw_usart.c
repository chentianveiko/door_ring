#include "hw_usart.h"
#include "stm8s.h"

hw_usart_rx_handler_t hw_usart_rx_handler_app = (hw_usart_rx_handler_t)0;


/*******************************************************************************************
 * @brief    初始化硬件串口1
 * @param    none
 * @return   none
 */
void hw_usart_init(void){
	UART2_Init((uint32_t)115200, UART2_WORDLENGTH_8D, UART2_STOPBITS_1, UART2_PARITY_NO,UART2_SYNCMODE_CLOCK_DISABLE, UART2_MODE_TXRX_ENABLE);
    UART2_ITConfig(UART2_IT_RXNE_OR, ENABLE);
    UART2_Cmd(ENABLE);
}
/*******************************************************************************************
 * @brief    使用硬件串口发送数据
 * @param    data 数据指针
 * @param    length 要发送的数据长度(字节)
 * @return   none
 */
void hw_usart_write(uint8_t *data, uint16_t length){
	uint16_t i = 0;

	while(length--){
		while((UART2->SR & (uint8_t)UART2_FLAG_TXE) == (uint8_t)0x00);
		UART2->DR = data[i++];
	}
}
/*******************************************************************************************
 * @brief    设置串口数据接收回调函数
 * @param    handler 回调函数指针
 * @return   none
 */
void hw_usart_set_rx_handler(hw_usart_rx_handler_t handler){
	hw_usart_rx_handler_app = handler;
}
/*******************************************************************************************
 * @brief    串口中断处理函数
 * @return   none
 */
INTERRUPT_HANDLER(UART2_RX_IRQHandler, 21)
{
  uint8_t ch;
  if(UART2_GetITStatus(UART2_IT_RXNE)!=RESET)
  {
    ch =  UART2_ReceiveData8();

    if(0 != hw_usart_rx_handler_app){
    	hw_usart_rx_handler_app(ch);
    }
  }
}

