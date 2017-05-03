#include "global_variable.h"

const uint8_t esp8266_get_wifi_mode[] = "AT+CWMODE=?\r\n";
const uint8_t esp8266_set_wifi_sta_mode[] = "AT+CWMODE=1\r\n";
const uint8_t esp8266_set_wifi_ap_mode[] = "AT+CWMODE=2\r\n";
const uint8_t esp8266_set_wifi_ap_sta_mode[] = "AT+CWMODE=3\r\n";
const uint8_t esp8266_get_sta_mac[] = "AT+CIPSTAMAC?\r\n";
const uint8_t esp8266_connect_ap[] = "AT+CWJAP_CUR =\"CHT_LXPP\", \"13709009914\"";
const uint8_t esp8266_auto_connect_to_ap[] = "AT+CWAUTOCONN=1";

/***** Copyright (C)2014 HuangFugui. All Rights Reserved ***** END OF FILE *****/
