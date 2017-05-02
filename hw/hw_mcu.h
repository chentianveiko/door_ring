#ifndef __HW_MCU_H__
#define __HW_MCU_H__

#include "stm8s.h"

#include <string.h>

/*
 *******************************************************************************
 *                                 CONSTANTS                                     
 *******************************************************************************
 */
#define BIG_ENDIAN      0x1234
#define LITTLE_ENDIAN   0x3412

#define CPU_ENDIAN              BIG_ENDIAN    // stm8s系列单片机都是大端模式
#define HW_DEVICE_ID_SIZE       12

typedef uint8_t hw_device_id_t[HW_DEVICE_ID_SIZE];


#define HW_MCU_REBOOT()        { WWDG->CR = 0x80; } /*  When this bit (WDGA) = 1, the watchdogcan generate a reset. */

#if (CPU_ENDIAN == BIG_ENDIAN)
  #define HTONS(n)  (n)
  #define HTONL(n)  (n)
  #define HTONF(f)  (f)
  #define NTOHS(n)  HTONS(n)
  #define NTOHL(n)  HTONL(n)   
  #define NTOHF(f)  HTONF(f)
#else
  #define HTONS(n)  (uint16_t)((((n) & 0xFF) << 8) | (((n) & 0xFF00) >> 8))
  #define HTONL(n)  (uint32_t)((((n) & 0xFF) << 24) | (((n) & 0xFF00) << 8) | (((n) & 0xFF0000UL) >> 8) | (((n) & 0xFF000000UL) >> 24))
  #define HTONF(f)  htonf(f)
  #define NTOHS(n)  HTONS(n)
  #define NTOHL(n)  HTONL(n)  
  #define NTOHF(f)  HTONF(f) 
#endif

#define __align_begin(n)  
#define __align_end()    

#define HW_MCU_READ_DEVICE_ID(id)   memcpy(id, (uint8_t *)0x4926, HW_DEVICE_ID_SIZE)
   
//#define HW_MCU_READ_DEVICE_ID(id)     \
  id[0] = *((uint8_t *)0x4927);       \
  id[1] = *((uint8_t *)0x4929);       \
  id[2] = *((uint8_t *)0x492A);       \
  id[3] = *((uint8_t *)0x4931);


#if (LITTLE_ENDIAN == CPU_ENDIAN)
inline float htonf(float f) 
{ 
  union { float f; uint32_t i; } fi;
  
  fi.f = f;
  fi.i = ntohl(fi.i);
  
  return fi.f;  
} 
#endif
   
#endif

