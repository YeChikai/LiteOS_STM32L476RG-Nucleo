#ifndef _LOS_BSP_UART_H
#define _LOS_BSP_UART_H

#ifdef LOS_STM32L476xx


#include "stm32l4xx_hal.h"
#include "stm32l4xx_nucleo.h"

/* Exported types ------------------------------------------------------------*/

extern	UART_HandleTypeDef UartHandle;
extern	UART_HandleTypeDef ESP8266UartHandle;

/* Exported constants --------------------------------------------------------*/
/* User can use this section to tailor USARTx/UARTx instance used and associated 
   resources */
/* Definition for USART1 clock resources */
#define USARTx                          USART1
#define USARTx_CLK_ENABLE()             __HAL_RCC_USART1_CLK_ENABLE()
#define USARTx_RX_GPIO_CLK_ENABLE()     __HAL_RCC_GPIOA_CLK_ENABLE()  // __HAL_RCC_GPIOC_CLK_ENABLE()
#define USARTx_TX_GPIO_CLK_ENABLE()     __HAL_RCC_GPIOA_CLK_ENABLE()  // __HAL_RCC_GPIOC_CLK_ENABLE()

#define USARTx_FORCE_RESET()            __HAL_RCC_USART1_FORCE_RESET()
#define USARTx_RELEASE_RESET()          __HAL_RCC_USART1_RELEASE_RESET()

/* Definition for USARTx Pins */
#define USARTx_TX_PIN                   GPIO_PIN_9  // GPIO_PIN_10
#define USARTx_TX_GPIO_PORT             GPIOA  			// GPIOC
#define USARTx_TX_AF                    GPIO_AF7_USART1

#define USARTx_RX_PIN                   GPIO_PIN_10  // GPIO_PIN_11
#define USARTx_RX_GPIO_PORT             GPIOA  				// GPIOC
#define USARTx_RX_AF                    GPIO_AF7_USART1

/* Definition for USART3 clock resources */
#define macESP8266_USART_FORCE_RESET()            __HAL_RCC_USART3_FORCE_RESET()
#define macESP8266_USART_RELEASE_RESET()          __HAL_RCC_USART3_RELEASE_RESET()

/******************************** ESP8266 串口 GPIO 配置 **********************************/
#define      macESP8266_USART                                USART3

#define      macESP8266_USART_BAUD_RATE                      115200

#define 		macESP8266_USART_TX_AF                    GPIO_AF7_USART3
#define 		macESP8266_USART_RX_AF                    GPIO_AF7_USART3

#define			macESP8266_USART_CLK_ENABLE()             __HAL_RCC_USART3_CLK_ENABLE()

#if 1
#define      macESP8266_USART_TX_PORT                         GPIOB   
#define      macESP8266_USART_TX_PIN                          GPIO_PIN_10

#define      macESP8266_USART_RX_PORT                         GPIOB
#define      macESP8266_USART_RX_PIN                          GPIO_PIN_11

#define 		 macESP8266_USART_GPIO_CLK_ENABLE()     		__HAL_RCC_GPIOB_CLK_ENABLE()

#else

#define      macESP8266_USART_TX_PORT                         GPIOC  
#define      macESP8266_USART_TX_PIN                          GPIO_PIN_10

#define      macESP8266_USART_RX_PORT                         GPIOC
#define      macESP8266_USART_RX_PIN                          GPIO_PIN_11

#define 		 macESP8266_USART_GPIO_CLK_ENABLE()     		__HAL_RCC_GPIOC_CLK_ENABLE()

#endif

#define      macESP8266_USART_IRQ                             USART3_IRQn
#define      macESP8266_USART_IRQHandler                      USART3_IRQHandler

/*********************************************** 函数宏定义 *******************************************/
#define     macESP8266_Usart( fmt, ... )           USART_printf ( &ESP8266UartHandle, fmt, ##__VA_ARGS__ ) 
#define     macPC_Usart( fmt, ... )                printf( fmt, ##__VA_ARGS__ ) 


/* Size of Trasmission buffer */
#define TXBUFFERSIZE                    (COUNTOF(aTxBuffer) - 1)
/* Size of Reception buffer */
#define RXBUFFERSIZE                    TXBUFFERSIZE
  
/* Exported macro ------------------------------------------------------------*/
#define COUNTOF(__BUFFER__)   (sizeof(__BUFFER__) / sizeof(*(__BUFFER__)))
/* Exported functions ------------------------------------------------------- */

#endif

/****************************************** 函数声明 ***********************************************/
void LOS_EvbUartInit(void);
void LOS_EvbUartWriteByte(char c);
void LOS_EvbUartWriteStr(const char* str);
void LOS_EvbUartReadByte(char* c);

void LOS_EvbUartPrintf(char* fmt, ...);

#endif
