#include "main.h"
#include "hw_mcu.h"
#include "hw_board.h"
#include "hw_usart.h"
#include "hw_timer.h"
#include "global_variable.h"
#include "esp8266.h"

#define APP_SOFT_TIMER   HW_ST_TIMER_2
static void app_variable_init(void);

void main(void) {
	hw_board_get_mac(door_ring.mac);

	disableInterrupts();
	{
		hw_board_init();
	}

	{
		hw_soft_timer_init();
		hw_usart_init();

		hw_usart_set_rx_handler(esp_usart_rx_handler);
	}
	enableInterrupts();

	esp_init();

	app_variable_init();

	while (1) {
		esp_send(door_ring.mac,sizeof(door_ring.mac));
                hw_board_delay_ms(200);
		esp_send("\r\n",sizeof("\r\n"));

		/*if(door_ring.rf_rx_flag == 1){
			door_ring.rf_rx_flag = false;

			esp_send(door_ring.mac,24);
			esp_send("\r\n",2);
		}*/

		hw_board_delay_ms(200);
	}
}
/*******************************************************************************************
 * @brief    应用层相关变量初始化
 * @param    ch 串口接收到的数据
 * @return   none
 */
static void app_variable_init(void){
	door_ring.rf_rx_flag = false;
}

#ifdef USE_FULL_ASSERT

void assert_failed(u8* file, u32 line) {
	/* Infinite loop */
	while (1) {
	}
}
#endif

/***** Copyright (C)2014 HuangFugui. All Rights Reserved ***** END OF FILE *****/
