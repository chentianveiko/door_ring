

#ifndef MAIN____H
#define MAIN____H

#include "stm8s.h"

#define KeyNone      0x00   /* 无按键 */
#define KeyRedShort  0x01   /* 短按红键 */
#define KeyRedLong   0x02   /* 长按红键 */
#define KeyBlueShort 0x03   /* 短按蓝键 */
#define KeyBlueLong  0x04   /* 长按蓝键 */

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










