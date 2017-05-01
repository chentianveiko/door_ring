
#ifndef Battery___H
#define Battery___H

#include "stm8s.h"
#include "NY3P.h"

#define PORT_POWERCheck    GPIOB
#define Pin_POWERCheck     GPIO_PIN_1

void ADC_Config(void);
void bubbleSort(uint16_t arr[],uint16_t n);/* ц╟ещеепР */
uint16_t GetSystemPower(void);

#endif










