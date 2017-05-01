#include "bsp.h"
#include "uart.h"
#include "timer.h"
#include "eeprom.h"
#include "main.h"

void main(void)
{  
  BSP_Initializes();
  disableInterrupts();
  enableInterrupts();
  
  while(1)
  {
    ;
  }
}

#ifdef USE_FULL_ASSERT

void assert_failed(u8* file, u32 line)
{
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

  /* Infinite loop */
  while (1)
  {
  }
}
#endif


/***** Copyright (C)2014 HuangFugui. All Rights Reserved ***** END OF FILE *****/
