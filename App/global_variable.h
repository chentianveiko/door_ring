
#ifndef _GLOBAL_VARIABLE_H
#define _GLOBAL_VARIABLE_H

#include "global_define.h"


typedef struct{
	uint8_t ssid[32];
	uint8_t pwd[32];

	uint8_t ser_add[32];
	uint8_t ser_port[8];

	uint8_t mac[25];

	bool rf_rx_flag;
}door_ring_t;

extern door_ring_t door_ring;


#endif /* _GLOBAL_VARIABLE_H */

/***** Copyright (C)2017.5 Veiko . All Rights Reserved ***** END OF FILE *****/
