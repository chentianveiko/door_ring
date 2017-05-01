

#ifndef MAIN____H
#define MAIN____H

#include "stm8s.h"

#define KeyNone      0x00   /* �ް��� */
#define KeyRedShort  0x01   /* �̰���� */
#define KeyRedLong   0x02   /* ������� */
#define KeyBlueShort 0x03   /* �̰����� */
#define KeyBlueLong  0x04   /* �������� */

void Delay_N(uint32_t n);
uint8_t UserKeyScan(void);
void UserEnterLowPowerMode(void);
uint8_t UserBatteryScan(void);
uint8_t UserAlarmCheck(void);
void UserInitEEPROM(void);
uint8_t User_ReadFP_ERR_CNT(void);
uint8_t Alarm_WriteFP_ERR_CNT(uint8_t Num);
void UserExitLowPowerMode(void);






#endif










