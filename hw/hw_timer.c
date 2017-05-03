
#include "hw_timer.h"

_hw_st_timer_t hw_soft_timer_list[]={
		{
				.en = false,
				.cnt = 0,
				.handler = (hw_soft_timer_handler_t)0,
		},
		{
				.en = false,
				.cnt = 0,
				.handler = (hw_soft_timer_handler_t)0,
		},
		{
				.en = false,
				.cnt = 0,
				.handler = (hw_soft_timer_handler_t)0,
		},
		{
				.en = false,
				.cnt = 0,
				.handler = (hw_soft_timer_handler_t)0,
		},
		{
				.en = false,
				.cnt = 0,
				.handler = (hw_soft_timer_handler_t)0,
		}
};

static void _hw_timer_init(void);
static void _hw_soft_timer_machine(void);

/*******************************************************************************************
 * @brief    初始化软件定时器依赖的硬件外设及涉及的相关变量
 * @param    none
 * @return   none
 */
void hw_soft_timer_init(void){
	uint8_t i = 0;

	for(i = 0; i < HW_SOFT_TIMER_NUM; i++){
		hw_soft_timer_list[i].en = false;
		hw_soft_timer_list[i].cnt = 0;
	}

	_hw_timer_init();
}
/*******************************************************************************************
 * @brief    判断软件定时器是否溢出
 * @param    timer 判断目标定时器
 * @return   true 溢出    false 未溢出
 */
bool hw_soft_timer_is_run_out(hw_st_timer_t timer){
	if(HW_ST_TIMER_E > timer){
		if(hw_soft_timer_list[timer].cnt == 0){
			return true;
		}
	}

	return false;
}
/*******************************************************************************************
 * @brief    停止一个软件定时器
 * @param    timer 目标定时器
 * @return   none
 */
void hw_soft_timer_stop(hw_st_timer_t timer){
	if(HW_ST_TIMER_E > timer){
		hw_soft_timer_list[timer].en = false;
	}
}
/*******************************************************************************************
 * @brief    获取软件定时器的计数器值
 * @param    timer 目标软件定时器
 * @return   计数器值
 */
uint32_t hw_soft_timer_get_cnt(hw_st_timer_t timer){
	if(HW_ST_TIMER_E > timer){
		return hw_soft_timer_list[timer].cnt;
	}else{
		return 0;
	}
}
/*******************************************************************************************
 * @brief    使用指定参数启动定时器
 * @param    timer 目标定时器
 * @param    cnt 启动时的计数值(定时器为向下计数),当该值为0时,定时器不修改cnt直接启动,单位 /ms
 * @return   none
 */
void hw_soft_timer_start(hw_st_timer_t timer,uint32_t cnt){
	TIM4_ITConfig(TIM4_IT_UPDATE, DISABLE);
	if(HW_ST_TIMER_E > timer){
		if(hw_soft_timer_list[timer].en == true){
			hw_soft_timer_list[timer].en = false;
		}

		if(cnt != 0){
			hw_soft_timer_list[timer].cnt = cnt;
		}

		hw_soft_timer_list[timer].en = true;
	}
	TIM4_ITConfig(TIM4_IT_UPDATE, ENABLE);
}
/*******************************************************************************************
 * @brief    设置软件定时器的回调函数
 * @param    timer 目标定时器
 * @param    handler 回调函数指针
 * @return   none
 */
void hw_soft_timer_set_handler(hw_st_timer_t timer,hw_soft_timer_handler_t handler){
	if(HW_ST_TIMER_E > timer){
		hw_soft_timer_list[timer].handler = handler;
	}
}
/*******************************************************************************************
 * @brief    初始化相关的硬件定时器
 * @param    none
 * @return   none
 */
static void _hw_timer_init(void){
	  TIM4_TimeBaseInit(TIM4_PRESCALER_128, 249);  // Time base configuration  /2ms
	  TIM4_SetAutoreload(249);
	  TIM4_ARRPreloadConfig(ENABLE);
	  TIM4_ClearFlag(TIM4_FLAG_UPDATE);            // Clear TIM4 update flag
	  TIM4_ITConfig(TIM4_IT_UPDATE, ENABLE);       // Enable update interrupt
	  TIM4_Cmd(ENABLE);                            // Enable TIM4
}
/*******************************************************************************************
 * @brief    软件定时器状态机,每次递减计数值为2,因为软件定时器的单位是ms,而驱动其工作的硬件外设中断周期是10ms
 * @param    none
 * @return   none
 */
static void _hw_soft_timer_machine(void){
	uint8_t i;
	bool if_callback;

	for(i = 0; i < HW_SOFT_TIMER_NUM; i++){
		if(hw_soft_timer_list[i].en == true){
			if_callback = true;
			if(hw_soft_timer_list[i].cnt >= 2){
				hw_soft_timer_list[i].cnt = hw_soft_timer_list[i].cnt - 2;
			}else if(hw_soft_timer_list[i].cnt > 0){
				hw_soft_timer_list[i].cnt = 0;
			}else{
				if_callback = false;
			}

			// 溢出回调
			if((hw_soft_timer_list[i].cnt == 0) && (if_callback == true) && (hw_soft_timer_list[i].handler != (hw_soft_timer_handler_t)0)){
				hw_soft_timer_list[i].handler();
			}
		}
	}
}
/*******************************************************************************************
 * @brief    硬件定时器4中断服务函数
 * @param    none
 * @return   none
 */
INTERRUPT_HANDLER(TIM4_UPD_OVF_IRQHandler, 23)
{
	_hw_soft_timer_machine();
	TIM4_ClearITPendingBit(TIM4_IT_UPDATE);  // Cleat Interrupt Pending bit
}

