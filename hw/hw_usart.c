#include "hw_usart.h"
#include "stm8s.h"
#include "hw_timer.h"
#include "stdarg.h"
#include "stdio.h"
#include "string.h"

#define HW_USART2_SOFT_TIMER  HW_ST_TIMER_1

hw_usart_rx_t hw_usart_rx_structure[3];
hw_usart_rx_handler_t hw_usart_rx_handler_app = (hw_usart_rx_handler_t) 0;

static void _hw_usart_soft_timer_handler(void);

/*******************************************************************************************
 * @brief    初始化硬件串口2
 * @param    none
 * @return   none
 */
void hw_usart_init(void) {
	hw_usart_rx_structure[0].len = 0;
	hw_usart_rx_structure[1].len = 0;
	hw_usart_rx_structure[2].len = 0;

	hw_usart_rx_structure[0].read_lock = false;
	hw_usart_rx_structure[1].read_lock = false;
	hw_usart_rx_structure[2].read_lock = false;

	hw_soft_timer_set_handler(HW_USART2_SOFT_TIMER,
			_hw_usart_soft_timer_handler);

	GPIO_Init(GPIOD, (GPIO_Pin_TypeDef) GPIO_PIN_5, GPIO_MODE_OUT_PP_HIGH_FAST);
	GPIO_Init(GPIOD, (GPIO_Pin_TypeDef) GPIO_PIN_6, GPIO_MODE_IN_FL_NO_IT);
	UART2_Init((uint32_t) 19200, UART2_WORDLENGTH_8D, UART2_STOPBITS_1,
			UART2_PARITY_NO, UART2_SYNCMODE_CLOCK_DISABLE,
			UART2_MODE_TXRX_ENABLE);
	UART2_ITConfig(UART2_IT_RXNE_OR, ENABLE);
	UART2_Cmd(ENABLE);
}
/*******************************************************************************************
 * @brief    使用硬件串口发送数据
 * @param    data 数据指针
 * @param    length 要发送的数据长度(字节)
 * @return   none
 */
void hw_usart_write_len(uint8_t *data, uint16_t length) {
	uint16_t i = 0;

	while (length--) {
		while ((UART2->SR & (uint8_t) UART2_FLAG_TXE) == (uint8_t) 0x00)
			;
		UART2->DR = data[i++];
	}
}
/*******************************************************************************************
 * @brief    使用硬件串口发送数据
 * @param    data 数据指针
 * @param    length 要发送的数据长度(字节)
 * @return   none
 */
void hw_usart_write(uint8_t *data) {
	uint16_t i = 0;

	while (data[i] != '\0') {
		while ((UART2->SR & (uint8_t) UART2_FLAG_TXE) == (uint8_t) 0x00)
			;
		UART2->DR = data[i];
		i++;
	}
}
/*******************************************************************************************
 * @brief    设置串口数据接收回调函数
 * @param    handler 回调函数指针
 * @return   none
 */
void hw_usart_set_rx_handler(hw_usart_rx_handler_t handler) {
	hw_usart_rx_handler_app = handler;
}
/*******************************************************************************************
 * @brief    串口打印接口
 * @param    。。。
 * @return   none
 */
char s0[128];
void usr_print(const char *fmt, ...) {
	va_list list;
	memset(s0, '\0', 127);

	va_start(list, fmt);
	vsprintf(s0, fmt, list);
	va_end(list);

	hw_usart_write_len((uint8_t *) s0, strlen(s0));
}
/*******************************************************************************************
 * @brief    串口软件定时器溢出回调函数
 * @param    none
 * @return   none
 */
static void _hw_usart_soft_timer_handler(void) {
	uint8_t i;

	hw_soft_timer_stop(HW_USART2_SOFT_TIMER);

	for (i = 0; i < 3; i++) {
		if (hw_usart_rx_structure[i].len != 0) {
			if (0 != hw_usart_rx_handler_app) {
				if (hw_usart_rx_structure[i].read_lock == false) {
					hw_usart_rx_structure[i].read_lock = true;
					hw_usart_rx_handler_app(&hw_usart_rx_structure[i]);
				}
			}
		}
	}
}
/*******************************************************************************************
 * @brief    串口中断处理函数
 * @return   none
 */
INTERRUPT_HANDLER(UART2_RX_IRQHandler, 21) {
	uint8_t i, j;
	uint8_t buff[USART_RX_BUFF_MAX];

	if (UART2_GetITStatus(UART2_IT_RXNE) != RESET) {
		j = 0;
		hw_soft_timer_stop(HW_USART2_SOFT_TIMER);
		while (UART2_GetFlagStatus(UART2_FLAG_RXNE) != RESET) {
			buff[j++] = UART2_ReceiveData8();
		}

		for (i = 0; i < 3; i++) {
			if (hw_usart_rx_structure[i].read_lock == false) {
				memcpy(
						&hw_usart_rx_structure[i].data[hw_usart_rx_structure[i].len],
						buff, j);
				hw_usart_rx_structure[i].len += j;
				break;
			}
		}

		hw_soft_timer_start(HW_USART2_SOFT_TIMER, 20);
	}

	if (RESET != UART2_GetFlagStatus(UART2_FLAG_OR_LHE)) {
		UART2_ReceiveData8();
	}

	UART2_ClearITPendingBit(UART2_IT_RXNE);
}

