
#ifndef __hw_timer_h
#define __hw_timer_h

#include "hw_board.h"
#include "stdbool.h"

typedef enum{
	HW_ST_TIMER_1 = 0x00,
	HW_ST_TIMER_2 = 0x01,
	HW_ST_TIMER_3 = 0x02,
	HW_ST_TIMER_4 = 0x03,
	HW_ST_TIMER_5 = 0x04,
	HW_ST_TIMER_E,
}hw_st_timer_t;

typedef void (* hw_soft_timer_handler_t)(void);

typedef struct{
	bool en;         // 使能标志,为true时表示该定时器正在运行
	uint32_t cnt;    // 计数器
	hw_soft_timer_handler_t handler;   // 溢出回调函数
}_hw_st_timer_t;



#define HW_SOFT_TIMER_NUM     (sizeof(hw_soft_timer_list) / sizeof(_hw_st_timer_t))

void hw_soft_timer_init(void);
bool hw_soft_timer_is_run_out(hw_st_timer_t timer);
void hw_soft_timer_stop(hw_st_timer_t timer);
uint32_t hw_soft_timer_get_cnt(hw_st_timer_t timer);
void hw_soft_timer_start(hw_st_timer_t timer,uint32_t cnt);
void hw_soft_timer_set_handler(hw_st_timer_t timer,hw_soft_timer_handler_t handler);


#endif

