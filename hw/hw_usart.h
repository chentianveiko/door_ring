#ifndef __HW_USART_H__
#define __HW_USART_H__
/*
 *******************************************************************************
 *                                  INCLUDE                                  
 *******************************************************************************
 */
#include "hw_mcu.h"
   

/*
 *******************************************************************************
 *                                 CONSTANTS                                     
 *******************************************************************************
 */
#define HW_USART_BUFFER_SIZE      64


/*
 *******************************************************************************
 *                               CONFIGURATION                                     
 *******************************************************************************
 */
#define HW_USART_USING_USART1     
#define xHW_USART_USING_USART2


/*
 *******************************************************************************
 *                                  TYPEDEFS                                  
 *******************************************************************************
 */
typedef enum 
{
#if (defined HW_USART_USING_USART1)
  HW_USART_1,
#endif
  
#if (defined HW_USART_USING_USART2)
  HW_USART_2,
#endif
  
  __HW_USART_END__,
}hw_usart_t;

typedef void (* hw_usart_rx_handler_t)(uint8_t ch);

void hw_usart_init(void);
void hw_usart_write(uint8_t *data, uint16_t length);
void hw_usart_set_rx_handler(hw_usart_rx_handler_t handler);


#endif
