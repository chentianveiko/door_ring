/*
 *******************************************************************************
 *                                  INCLUDE                                  
 *******************************************************************************
 */
#include "hw_board.h"

static void _hw_board_clock_init(void);
static void _hw_sys_clock_out_config(void);

/*******************************************************************************************
 * @brief    板卡硬件初始化
 */
void hw_board_init(void) {
	_hw_board_clock_init();
	_hw_sys_clock_out_config();
}
/*******************************************************************************************
 * @brief    阻塞式微秒级延时(对应系统时钟频率为:16Mhz)
 * @param    us 延时的微秒数
 */
#pragma optimize=none  /* 任何情况下都不优化这段代码 */
void hw_board_delay_us(uint16_t us) {
	while (us--) {
		asm("nop");
		// 一个asm("nop")函数经过示波器测试代表100ns(系统时钟频率为:16MHz)
		asm("nop");
		asm("nop");
		asm("nop");
	}
}
/*******************************************************************************************
 * @brief    阻塞式毫秒级延时(对应系统时钟为16Mhz)
 * @param    ms 延时的毫秒数
 */
#pragma optimize=none  /* 任何情况下都不优化这段代码 */
void hw_board_delay_ms(uint16_t ms) {
	while (ms--) {
		hw_board_delay_us(1000);
	}
}
/*******************************************************************************************
 * @brief    设置系统的系统时钟频率,该应用中设置为16MHz
 */
static void _hw_board_clock_init(void) {
	CLK_ClockSwitchConfig(CLK_SWITCHMODE_AUTO, CLK_SOURCE_HSI, DISABLE,
			CLK_CURRENTCLOCKSTATE_DISABLE);
	CLK_HSIPrescalerConfig(CLK_PRESCALER_HSIDIV1); //HSI = 16M (1分频)
	while (CLK_GetFlagStatus(CLK_FLAG_HSIRDY) == RESET)
		; /* 等待时钟切换完成并稳定 */
}
/*******************************************************************************************
 * @brief    通过PC4引脚将系统时钟输出
 */
static void _hw_sys_clock_out_config(void) {
#if 1
	/* 系统时钟输出测试 */
	GPIO_Init(GPIOD, (GPIO_Pin_TypeDef) GPIO_PIN_0, GPIO_MODE_OUT_PP_HIGH_FAST);

	CLK_CCOConfig(CLK_OUTPUT_LSI);
	CLK_CCOCmd(ENABLE);
#endif
}

