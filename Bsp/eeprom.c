#include "eeprom.h"

/*******************************************************************************************
*函数:EEPROM_Init
*入参:NONE
*返回:NONE
*功能:EEPROM初始化
*范例:EEPROM_Init();
*作者:yangguo
*时间:略
*******************************************************************************************/
void EEPROM_Init(void)
{
    FLASH->CR1 &= (uint8_t)(~FLASH_CR1_FIX);
    FLASH->CR1 |= (uint8_t)FLASH_PROGRAMTIME_STANDARD;
  
    FLASH->DUKR = FLASH_RASS_KEY2;  /* 解锁数据区 */
    FLASH->DUKR = FLASH_RASS_KEY1;
}
/*******************************************************************************************
*函数:EEPROM_write_byte
*入参:addr -- 要写入字节的地址
*     data -- 要写入的数据
*返回:无
*功能:向EEPROM中写入一个字节数据
*范例:无
*作者:
*时间:
*******************************************************************************************/
void EEPROM_write_byte(uint32_t addr,uint8_t data)
{
    FLASH->DUKR = FLASH_RASS_KEY2;   /* 解锁数据区 */ 
    FLASH->DUKR = FLASH_RASS_KEY1;
    
    FLASH_ProgramByte(FLASH_DATA_START_PHYSICAL_ADDRESS+addr,data);
    FLASH_WaitForLastOperation(FLASH_MEMTYPE_DATA);//一定要执行
    
    FLASH->IAPSR &= (uint8_t)FLASH_MEMTYPE_DATA;  /* Lock */
}
/*******************************************************************************************
*函数:EEPROM_read_byte
*入参:
*返回:
*功能:
*范例:
*作者:
*时间:
*******************************************************************************************/
uint8_t EEPROM_read_byte(uint32_t addr)
{
    uint8_t temp;
    temp=FLASH_ReadByte(FLASH_DATA_START_PHYSICAL_ADDRESS+addr);
    return temp;
}
/*******************************************************************************************
*函数:EEPROM_write
*入参:
*返回:
*功能:
*范例:
*作者:
*时间:
*******************************************************************************************/
void EEPROM_write(uint32_t addr, uint8_t *p, uint16_t wr)
{
  while(wr--)
  {
    EEPROM_write_byte(addr++,*p++);
  }
}
/*******************************************************************************************
*函数:EEPROM_Read
*入参:
*返回:
*功能:
*范例:
*作者:
*时间:
*******************************************************************************************/
void EEPROM_Read(uint32_t addr, uint8_t *p, uint16_t br)
{
  uint16_t index;
  for(index = 0; index<br; index++)
  {
  	*p ++ = EEPROM_read_byte(addr++);
  }
}











