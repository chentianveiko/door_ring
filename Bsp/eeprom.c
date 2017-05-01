#include "eeprom.h"

/*******************************************************************************************
*����:EEPROM_Init
*���:NONE
*����:NONE
*����:EEPROM��ʼ��
*����:EEPROM_Init();
*����:yangguo
*ʱ��:��
*******************************************************************************************/
void EEPROM_Init(void)
{
    FLASH->CR1 &= (uint8_t)(~FLASH_CR1_FIX);
    FLASH->CR1 |= (uint8_t)FLASH_PROGRAMTIME_STANDARD;
  
    FLASH->DUKR = FLASH_RASS_KEY2;  /* ���������� */
    FLASH->DUKR = FLASH_RASS_KEY1;
}
/*******************************************************************************************
*����:EEPROM_write_byte
*���:addr -- Ҫд���ֽڵĵ�ַ
*     data -- Ҫд�������
*����:��
*����:��EEPROM��д��һ���ֽ�����
*����:��
*����:
*ʱ��:
*******************************************************************************************/
void EEPROM_write_byte(uint32_t addr,uint8_t data)
{
    FLASH->DUKR = FLASH_RASS_KEY2;   /* ���������� */ 
    FLASH->DUKR = FLASH_RASS_KEY1;
    
    FLASH_ProgramByte(FLASH_DATA_START_PHYSICAL_ADDRESS+addr,data);
    FLASH_WaitForLastOperation(FLASH_MEMTYPE_DATA);//һ��Ҫִ��
    
    FLASH->IAPSR &= (uint8_t)FLASH_MEMTYPE_DATA;  /* Lock */
}
/*******************************************************************************************
*����:EEPROM_read_byte
*���:
*����:
*����:
*����:
*����:
*ʱ��:
*******************************************************************************************/
uint8_t EEPROM_read_byte(uint32_t addr)
{
    uint8_t temp;
    temp=FLASH_ReadByte(FLASH_DATA_START_PHYSICAL_ADDRESS+addr);
    return temp;
}
/*******************************************************************************************
*����:EEPROM_write
*���:
*����:
*����:
*����:
*����:
*ʱ��:
*******************************************************************************************/
void EEPROM_write(uint32_t addr, uint8_t *p, uint16_t wr)
{
  while(wr--)
  {
    EEPROM_write_byte(addr++,*p++);
  }
}
/*******************************************************************************************
*����:EEPROM_Read
*���:
*����:
*����:
*����:
*����:
*ʱ��:
*******************************************************************************************/
void EEPROM_Read(uint32_t addr, uint8_t *p, uint16_t br)
{
  uint16_t index;
  for(index = 0; index<br; index++)
  {
  	*p ++ = EEPROM_read_byte(addr++);
  }
}











