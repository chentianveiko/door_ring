#include "main.h"
#include "hw_mcu.h"
#include "hw_board.h"
#include "hw_usart.h"

static void app_usart2_rx_handler(uint8_t ch);

void main(void)
{
	{
		hw_board_init();
	}

	{
		hw_usart_init();

		hw_usart_set_rx_handler(app_usart2_rx_handler);
	}
        
        enableInterrupts(); 
  
	while(1)
	{
          GPIO_WriteHigh(GPIOD, GPIO_PIN_0);
          hw_board_delay_ms(50);
          GPIO_WriteLow(GPIOD, GPIO_PIN_0);
          hw_board_delay_ms(50);
		//hw_usart_write("test \r\n",sizeof("test \r\n"));
	}
}
/*******************************************************************************************
 * @brief    应用层串口数据处理回调函数
 * @param    ch 串口接收到的数据
 * @return   none
 */
static void app_usart2_rx_handler(uint8_t ch){
	hw_usart_write(&ch, 1);
}

#ifdef USE_FULL_ASSERT

void assert_failed(u8* file, u32 line)
{
  /* Infinite loop */
  while (1)
  {
  }
}
#endif


/***** Copyright (C)2014 HuangFugui. All Rights Reserved ***** END OF FILE *****/
