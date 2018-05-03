#ifndef __HALLCOMMON_H
#define __HALLCOMMON_H

#include <stdarg.h>
#include "los_typedef.h"
#include "los_demo_debug.h"
#include "los_bsp_uart.h"

#ifdef LOS_STM32L476xx
#include "stm32l4xx_hal.h"
#include "stm32l4xx_nucleo.h"
#endif


/******************************* 宏定义 ***************************/


/********************************** 函数声明 ***************************************/
void    USART_printf( UART_HandleTypeDef * huart, char * Data, ... );


#endif /* __HALLCOMMON_H */

