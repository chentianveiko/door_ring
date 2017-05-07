#include "esp8266.h"
#include "global_variable.h"
#include "string.h"
#include "stdlib.h"
#include "stdbool.h"
#include "hw_timer.h"

uint8_t cmd_ok_flag = 0;   // 用于判断命令是否执行成功!

static uint8_t esp_set_wifi_sta_mode(void);
static uint8_t esp_reset_device(void);
static uint8_t esp_set_wifi_param(void);
static uint8_t esp_set_remote_ser(void);

/*******************************************************************************************
 * @brief    复位wifi模块
 * @param    none
 * @return   none
 */
static uint8_t esp_reset_device(void) {
	uint8_t delay_cnt = 0;
	cmd_ok_flag = 0;

	usr_print("AT+RST\r\n");

	hw_soft_timer_start(ESP_SOFT_TIMER, 100);
	while (hw_soft_timer_is_run_out(ESP_SOFT_TIMER) != true) {
		if (cmd_ok_flag == 1) {
			hw_board_delay_ms(2000);
			return 1;
		} else if (cmd_ok_flag == 2) {
			hw_soft_timer_start(ESP_SOFT_TIMER, 100);

			usr_print("AT+RST\r\n");
		} else {
			hw_soft_timer_start(ESP_SOFT_TIMER, 100);
			while (hw_soft_timer_is_run_out(ESP_SOFT_TIMER) != true)
							;
			delay_cnt++;
			if(delay_cnt>=100){
				delay_cnt = 0;
				usr_print("AT+RST\r\n");
			}
			hw_soft_timer_start(ESP_SOFT_TIMER, 100);
		}
	}

	return 0;
}
/*******************************************************************************************
 * @brief    配置Wifi模块的工作模式为数据模式
 * @param    none
 * @return   none
 */
static uint8_t esp_set_wifi_sta_mode(void) {
	uint8_t delay_cnt = 0;
	cmd_ok_flag = 0;

	usr_print("AT+CWMODE=%d\r\n", 1);

	hw_soft_timer_start(ESP_SOFT_TIMER, 100);
	while (hw_soft_timer_is_run_out(ESP_SOFT_TIMER) != true) {
		if (cmd_ok_flag == 1) {
			hw_board_delay_ms(200);
			return 1;
		} else if (cmd_ok_flag == 2) {
			hw_soft_timer_start(ESP_SOFT_TIMER, 100);

			usr_print("AT+CWMODE=%d\r\n", 1);
		} else {
			hw_soft_timer_start(ESP_SOFT_TIMER, 100);
			while (hw_soft_timer_is_run_out(ESP_SOFT_TIMER) != true)
							;
			delay_cnt++;
			if(delay_cnt>=100){
				delay_cnt = 0;
				usr_print("AT+CWMODE=%d\r\n", 1);
			}
			hw_soft_timer_start(ESP_SOFT_TIMER, 20);
		}
	}

	return 0;
}/*******************************************************************************************
 * @brief    配置Wifi模块连接的目标路由器无线网络SSID和密码
 * @param    none
 * @return   none
 */
static uint8_t esp_set_wifi_param(void) {
	uint8_t delay_cnt = 0;
	cmd_ok_flag = 0;

	usr_print("AT+CWJAP=\"%s\",\"%s\"\r\n", ESP_WIFI_SSID_DEF,
	ESP_WIFI_PWD_DEF);

	hw_soft_timer_start(ESP_SOFT_TIMER, 100);
	while (hw_soft_timer_is_run_out(ESP_SOFT_TIMER) != true) {
		if (cmd_ok_flag == 1) {
			hw_board_delay_ms(1000);
			return 1;
		} else if (cmd_ok_flag == 2) {
			hw_soft_timer_start(ESP_SOFT_TIMER, 100);

			usr_print("AT+CWJAP=\"%s\",\"%s\"\r\n", ESP_WIFI_SSID_DEF,
			ESP_WIFI_PWD_DEF);
		} else {
			hw_soft_timer_start(ESP_SOFT_TIMER, 100);
			while (hw_soft_timer_is_run_out(ESP_SOFT_TIMER) != true)
							;
			delay_cnt++;
			if(delay_cnt>=200){
				delay_cnt = 0;
				usr_print("AT+CWJAP=\"%s\",\"%s\"\r\n", ESP_WIFI_SSID_DEF,
				ESP_WIFI_PWD_DEF);
			}
			hw_soft_timer_start(ESP_SOFT_TIMER, 10);
		}
	}

	return 0;
}
/*******************************************************************************************
 * @brief    配置远程服务器地址
 * @param    none
 * @return   none
 */
static uint8_t esp_set_remote_ser(void) {
	uint8_t delay_cnt = 0;
	cmd_ok_flag = 0;

	usr_print("AT+CIPSTART=\"TCP\",%s\r\n", ESP_SER_DEF);

	hw_soft_timer_start(ESP_SOFT_TIMER, 100);
	while (hw_soft_timer_is_run_out(ESP_SOFT_TIMER) != true) {
		if (cmd_ok_flag == 1) {
			hw_board_delay_ms(200);
			return 1;
		} else if (cmd_ok_flag == 2) {
			hw_soft_timer_start(ESP_SOFT_TIMER, 100);

			usr_print("AT+CIPSTART=\"TCP\",%s\r\n", ESP_SER_DEF);
		} else {
			hw_soft_timer_start(ESP_SOFT_TIMER, 100);
			while (hw_soft_timer_is_run_out(ESP_SOFT_TIMER) != true)
							;
			delay_cnt++;
			if(delay_cnt>=100){
				delay_cnt = 0;

				usr_print("AT+CIPSTART=\"TCP\",%s\r\n", ESP_SER_DEF);
			}

			hw_soft_timer_start(ESP_SOFT_TIMER, 10);
		}
	}

	return 0;
}
/*******************************************************************************************
 * @brief    初始化wifi模块(请提前将wifi模块的串口波特率设置为与对应串口波特率相同)
 * @param    none
 * @return   none
 */
void esp_init(void) {
	esp_set_wifi_sta_mode();   // 设置网络模块工作模式

	esp_reset_device();  // 复位生效

	esp_set_wifi_param();  // 配置目标wifiSSID和密码

	esp_set_remote_ser();  // 配置远程服务器地址
}
/*******************************************************************************************
 * @brief    获取wifi的mac地址
 * @param    none
 * @return   none
 */
void esp_get_mac(uint8_t *mac) {
	HW_MCU_READ_DEVICE_ID(mac);
}
/*******************************************************************************************
 * @brief    发送数据
 * @param    none
 * @return   none
 */
void esp_send(uint8_t *p, uint8_t len) {
	cmd_ok_flag = 0;
	usr_print("AT+CIPSEND=%d\r\n", len);
	//while(cmd_ok_flag != 3);
        hw_board_delay_ms(100);
	cmd_ok_flag = 0;
        hw_usart_write_len(p,len);
	//usr_print("%s", p);
}

void esp_usart_rx_handler(hw_usart_rx_t *s) {
	uint8_t *n = 0;
	uint8_t len = 0;

	if (strstr((uint8_t *) (s->data), ">") != NULL) {
		cmd_ok_flag = 3;  // 标志配置或其他命令执行成功
	} else if (strstr((uint8_t *)(s->data), "ERROR") != NULL) {
		cmd_ok_flag = 2;  // 标志错误
	} else if(strstr((uint8_t *)(s->data),"OK") != NULL){
		cmd_ok_flag = 1;
	}else{
		// 命令:读写Wifi的SSID
		n = strstr(s->data, "CMD_WifiSsidW");
		if (n > 0) {
			memset(door_ring.ssid,'\0',32);
			len = sizeof("CMD_WifiSsidW")-1;
			len = s->len - len;
			memcpy(door_ring.ssid,n+sizeof("CMD_WifiSsidW")-1,((len <= 32)? len:32));
		}

		// 命令:读写Wifi的密码
		n = strstr(s->data, "CMD_WifiPwdW");
		if (n > 0) {
			memset(door_ring.pwd,'\0',32);
			len = sizeof("CMD_WifiPwdW")-1;
			len = s->len - len;
			memcpy(door_ring.pwd,n+sizeof("CMD_WifiPwdW")-1,((len <= 32)? len:32));
		}
	}

	memset(s->data, '\0', USART_RX_BUFF_MAX);
	s->read_lock = false;
	s->len = 0;
}
