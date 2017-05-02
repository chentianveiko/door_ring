/*
 *******************************************************************************
 *                                  INCLUDE                                  
 *******************************************************************************
 */
#include "hw_board.h"
#include <stdlib.h>
#include <string.h>

static void _hw_board_clock_init(void);

/*******************************************************************************************
 * @brief    板卡硬件初始化
 */
void hw_board_init(void)
{
   _hw_board_clock_init();
}
/*******************************************************************************************
 * @brief    阻塞式微秒级延时(对应系统时钟频率为:16Mhz)
 * @param    us 延时的微秒数
 */
//#pragma optimize=no_optimization
void hw_board_delay_us(uint16_t us){
	while(us--){
		asm("nop"); // 一个asm("nop")函数经过示波器测试代表100ns(系统时钟频率为:16MHz)
		asm("nop");
		asm("nop");
		asm("nop");
	}
}
/*******************************************************************************************
 * @brief    阻塞式毫秒级延时(对应系统时钟为16Mhz)
 * @param    ms 延时的毫秒数
 */
//#pragma optimize=no_optimization
void hw_board_delay_ms(uint16_t ms){
	while(ms--){
		hw_board_delay_us(1000);
	}
}
/*******************************************************************************************
 * @brief    设置系统的系统时钟频率,该应用中设置为16MHz
 */
static void _hw_board_clock_init(void)
{
	CLK_HSIPrescalerConfig(CLK_PRESCALER_HSIDIV1);  // 16Mhz
}

