#include "main.h"
#include "hw_mcu.h"
#include "hw_board.h"
#include "hw_usart.h"
#include "hw_timer.h"

#define APP_SOFT_TIMER   HW_ST_TIMER_2
static void app_usart2_rx_handler(hw_usart_rx_t *s);

void main(void)
{
	disableInterrupts();
	{
		hw_board_init();
	}

	{
		hw_soft_timer_init();
		hw_usart_init();

		hw_usart_set_rx_handler(app_usart2_rx_handler);
	}
	enableInterrupts();
  
	while(1)
	{
		hw_soft_timer_start(APP_SOFT_TIMER,5000);
		while(hw_soft_timer_is_run_out(APP_SOFT_TIMER) != true);
		hw_usart_write("AT+GMR\r\n",sizeof("AT+GMR\r\n"));
	}
}
/*******************************************************************************************
 * @brief    应用层串口数据处理回调函数
 * @param    ch 串口接收到的数据
 * @return   none
 */
static void app_usart2_rx_handler(hw_usart_rx_t *s){
	//hw_usart_write(s->data, s->len);
	s->read_lock = false;
	s->len = 0;
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
