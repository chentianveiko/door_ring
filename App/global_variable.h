/**
  **********************************  STM8S  ***********************************
  * @文件名     ： global_variable.h
  * @作者       ： Huang Fugui
  * @库版本     ： V2.2.0
  * @文件版本   ： V1.0.1
  * @日期       ： 2014年12月22日
  * @摘要       ： 全局变量头文件
  ******************************************************************************/

/* 定义防止递归包含 ----------------------------------------------------------*/
#ifndef _GLOBAL_VARIABLE_H
#define _GLOBAL_VARIABLE_H

/* 包含的头文件 --------------------------------------------------------------*/
#include "global_define.h"

/**************************************************************************************************
 *EEPROM
 */
#define E2P_VALUED1			 0x88  /* EEPROM如果已经初始化则对应字节写0(EEPROM擦除后是0xff) */
#define E2P_VALUED2                     0x89
#define E2P_VALUED3                     0x56
#define E2P_VALUED4                     0x57

/**************************************************************************************************
 *ALARM
 */
#define USER_ALARM_TIME                 60   /* 报警最长时间为60s */
#define FP_ALARM_ERR_TIME               5     /* 错误验证计数最大次数为连续5次就报警 */
#define ALARM_LeiJia                    0     /* 不/累加报警，如果是1的话表示累加报警(累加报警，即每次报警后不会清除错误计数) */
   
#define MAIN_RUN_TIME                   60    /* 单位为秒 */
   
/**************************************************************************************************
 *FP
 */
#define USER_MAX_FP_ID                  119   /* 指纹头最大ID为USER_MAX_FP_ID(0-USER_MAX_FP_ID为有效可注册ID) */

/**************************************************************************************************
 *E2PROM-MAP
 */
#define ADDR_ALARM_SW          1    /* 报警开关 */
#define ADDR_EEPROM_FLAG_S	2    /* EEPROM初始化标志存入起始地址 */
#define ADDR_EEPROM_FLAG_E     5    /* EEPROM初始化标志存入终止地址 */
#define ADDR_FP_ID_Number      6    /* EEPROM中已注册指纹ID个数的存放地址 */
#define ADDR_ERR_FP_COUNT      7    /* 指纹比对错误记数存储地址 */
#define ADDR_FP_SensorIDStart   20      /* 指纹头ID存放起始地址 */
#define ADDR_FP_SensorIDEnd     40   



/* 全局变量 ------------------------------------------------------------------*/
/* TIM定时器 */
extern uint8_t  gRx_CMDAvailable;                          //从机接收指令有效命令

extern uint16_t BattaryRegValue;
extern bool TIM2_OVER_Flag;
extern uint8_t UserKeyDownFlag;
//extern bool FP_OPEN_Flag;
extern bool ZD_Flag;
extern bool SLIP_COVER_TRG;
extern bool Alarm_SWSTU;
extern uint16_t MainRunTime;



#endif /* _GLOBAL_VARIABLE_H */

/***** Copyright (C)2014 HuangFugui. All Rights Reserved ***** END OF FILE *****/
