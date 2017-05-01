#ifndef _EEPROM_H
#define _EEPROM_H

#include "global_variable.h"

void 	EEPROM_Init(void);
void 	EEPROM_write_byte(uint32_t addr,uint8_t data);
uint8_t EEPROM_read_byte(uint32_t addr);
void 	EEPROM_write(uint32_t addr, uint8_t *p, uint16_t wr);
void 	EEPROM_Read(uint32_t addr, uint8_t *p, uint16_t br);

#endif /* __EEPROM_H */