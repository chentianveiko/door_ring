/**
  **********************************  STM8S  ***********************************
  * @�ļ���     �� global_variable.h
  * @����       �� Huang Fugui
  * @��汾     �� V2.2.0
  * @�ļ��汾   �� V1.0.1
  * @����       �� 2014��12��22��
  * @ժҪ       �� ȫ�ֱ���ͷ�ļ�
  ******************************************************************************/

/* �����ֹ�ݹ���� ----------------------------------------------------------*/
#ifndef _GLOBAL_VARIABLE_H
#define _GLOBAL_VARIABLE_H

/* ������ͷ�ļ� --------------------------------------------------------------*/
#include "global_define.h"

/**************************************************************************************************
 *EEPROM
 */
#define E2P_VALUED1			 0x88  /* EEPROM����Ѿ���ʼ�����Ӧ�ֽ�д0(EEPROM��������0xff) */
#define E2P_VALUED2                     0x89
#define E2P_VALUED3                     0x56
#define E2P_VALUED4                     0x57

/**************************************************************************************************
 *ALARM
 */
#define USER_ALARM_TIME                 60   /* �����ʱ��Ϊ60s */
#define FP_ALARM_ERR_TIME               5     /* ������֤����������Ϊ����5�ξͱ��� */
#define ALARM_LeiJia                    0     /* ��/�ۼӱ����������1�Ļ���ʾ�ۼӱ���(�ۼӱ�������ÿ�α����󲻻�����������) */
   
#define MAIN_RUN_TIME                   60    /* ��λΪ�� */
   
/**************************************************************************************************
 *FP
 */
#define USER_MAX_FP_ID                  119   /* ָ��ͷ���IDΪUSER_MAX_FP_ID(0-USER_MAX_FP_IDΪ��Ч��ע��ID) */

/**************************************************************************************************
 *E2PROM-MAP
 */
#define ADDR_ALARM_SW          1    /* �������� */
#define ADDR_EEPROM_FLAG_S	2    /* EEPROM��ʼ����־������ʼ��ַ */
#define ADDR_EEPROM_FLAG_E     5    /* EEPROM��ʼ����־������ֹ��ַ */
#define ADDR_FP_ID_Number      6    /* EEPROM����ע��ָ��ID�����Ĵ�ŵ�ַ */
#define ADDR_ERR_FP_COUNT      7    /* ָ�ƱȶԴ�������洢��ַ */
#define ADDR_FP_SensorIDStart   20      /* ָ��ͷID�����ʼ��ַ */
#define ADDR_FP_SensorIDEnd     40   



/* ȫ�ֱ��� ------------------------------------------------------------------*/
/* TIM��ʱ�� */
extern uint8_t  gRx_CMDAvailable;                          //�ӻ�����ָ����Ч����

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
