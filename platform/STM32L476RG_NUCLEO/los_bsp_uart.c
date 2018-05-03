#include <stdarg.h>
#include "los_bsp_uart.h"
#include "los_printf.h"
#include "bsp_esp8266.h"

#ifdef LOS_STM32L476xx
#include "stm32l4xx_hal.h"
#include "stm32l4xx_nucleo.h"

UART_HandleTypeDef UartHandle;

static void Error_Handler(void)
{
    while(1)
    {
			PRINT_ERR("[%s] ERROR !!! \r\n", __FUNCTION__);
    }
}
#endif

/**
  * @brief UART MSP Initialization
  *        This function configures the hardware resources used in this example:
  *           - Peripheral's clock enable
  *           - Peripheral's GPIO Configuration
  * @param huart: UART handle pointer
  * @retval None
  */
void HAL_UART_MspInit(UART_HandleTypeDef *huart)
{
    GPIO_InitTypeDef  GPIO_InitStruct;

    RCC_PeriphCLKInitTypeDef RCC_PeriphClkInit;

		if(huart->Instance == USARTx)
		{
			/*##-1- Enable peripherals and GPIO Clocks #################################*/
			/* Enable GPIO TX/RX clock */
			USARTx_TX_GPIO_CLK_ENABLE();
			USARTx_RX_GPIO_CLK_ENABLE();

			/* Select SysClk as source of USART1 clocks */
			RCC_PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_USART1;
			RCC_PeriphClkInit.Usart1ClockSelection = RCC_USART1CLKSOURCE_SYSCLK;
			HAL_RCCEx_PeriphCLKConfig(&RCC_PeriphClkInit);

			/* Enable USARTx clock */
			USARTx_CLK_ENABLE();

			/*##-2- Configure peripheral GPIO ##########################################*/
			/* UART TX GPIO pin configuration  */
			GPIO_InitStruct.Pin       = USARTx_TX_PIN;
			GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
			GPIO_InitStruct.Pull = GPIO_PULLUP;
			GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
			GPIO_InitStruct.Alternate = USARTx_TX_AF;

			HAL_GPIO_Init(USARTx_TX_GPIO_PORT, &GPIO_InitStruct);

			/* UART RX GPIO pin configuration  */
			GPIO_InitStruct.Pin = USARTx_RX_PIN;
			GPIO_InitStruct.Alternate = USARTx_RX_AF;

			HAL_GPIO_Init(USARTx_RX_GPIO_PORT, &GPIO_InitStruct);			
		}
		else if(huart->Instance == macESP8266_USART)
		{
			/*##-1- Enable peripherals and GPIO Clocks #################################*/	
			macESP8266_USART_GPIO_CLK_ENABLE();
					
			/* Select SysClk as source of USART3 clocks */
			RCC_PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_USART3;
			RCC_PeriphClkInit.Usart3ClockSelection = RCC_USART3CLKSOURCE_SYSCLK;
			HAL_RCCEx_PeriphCLKConfig(&RCC_PeriphClkInit);

			/* Enable USARTx clock */
			macESP8266_USART_CLK_ENABLE();
		
			/* USART GPIO config */
			/* Configure USART Tx as alternate function push-pull */
			GPIO_InitStruct.Pin =  macESP8266_USART_TX_PIN;
			GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
			GPIO_InitStruct.Pull = GPIO_PULLUP;
			GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
			GPIO_InitStruct.Alternate = macESP8266_USART_TX_AF;
			
			HAL_GPIO_Init(macESP8266_USART_TX_PORT, &GPIO_InitStruct);
			
			/* Configure USART Rx as input floating */
			GPIO_InitStruct.Pin = macESP8266_USART_RX_PIN;
			GPIO_InitStruct.Alternate = macESP8266_USART_RX_AF;
			
			HAL_GPIO_Init(macESP8266_USART_RX_PORT, &GPIO_InitStruct);		
		}
		
		return;
}

/**
  * @brief UART MSP De-Initialization
  *        This function frees the hardware resources used in this example:
  *          - Disable the Peripheral's clock
  *          - Revert GPIO and NVIC configuration to their default state
  * @param huart: UART handle pointer
  * @retval None
  */
void HAL_UART_MspDeInit(UART_HandleTypeDef *huart)
{
    /*##-1- Reset peripherals ##################################################*/
    USARTx_FORCE_RESET();
    USARTx_RELEASE_RESET();

    /*##-2- Disable peripherals and GPIO Clocks #################################*/
    /* Configure UART Tx as alternate function  */
    HAL_GPIO_DeInit(USARTx_TX_GPIO_PORT, USARTx_TX_PIN);
    /* Configure UART Rx as alternate function  */
    HAL_GPIO_DeInit(USARTx_RX_GPIO_PORT, USARTx_RX_PIN);

}

void LOS_EvbUartInit(void)
{
#ifdef LOS_STM32L476xx
    UartHandle.Instance          = USARTx;

    UartHandle.Init.BaudRate     = 115200;
    UartHandle.Init.WordLength   = UART_WORDLENGTH_8B;
    UartHandle.Init.StopBits     = UART_STOPBITS_1;
    UartHandle.Init.Parity       = UART_PARITY_NONE;
    UartHandle.Init.HwFlowCtl    = UART_HWCONTROL_NONE;
    UartHandle.Init.Mode         = UART_MODE_TX_RX;
    UartHandle.Init.OverSampling = UART_OVERSAMPLING_16;

    if(HAL_UART_Init(&UartHandle) != HAL_OK)
    {
        Error_Handler();
    }

#endif
    
    return;
}


/*************************************************************************************************
 *  功能：向串口1发送一个字符                                                                    *
 *  参数：(1) 需要被发送的字符                                                                   *
 *  返回：                                                                                       *
 *  说明：                                                                                       *
 *************************************************************************************************/
void LOS_EvbUartWriteByte(char c)
{
#ifdef LOS_STM32L476xx
    if(HAL_UART_Transmit(&UartHandle, (uint8_t*)&c, 1, 5000)!= HAL_OK)
    {
        Error_Handler();
    }
#endif
    return;
}

/*************************************************************************************************
 *  功能：向串口1发送一个字符串                                                                  *
 *  参数：(1) 需要被发送的字符串                                                                 *
 *  返回：                                                                                       *
 *  说明：                                                                                       *
 *************************************************************************************************/
void LOS_EvbUartWriteStr(const char* str)
{
#ifdef LOS_STM32L476xx
    while (*str)
    {
        if(HAL_UART_Transmit(&UartHandle, (uint8_t*)str, 1, 5000)!= HAL_OK)
        {
            Error_Handler();
        }
        str++;
    }
#endif
    return;
}


/*************************************************************************************************
 *  功能：从串口1接收一个字符                                                                    *
 *  参数：(1) 存储接收到的字符                                                                   *
 *  返回：                                                                                       *
 *  说明：                                                                                       *
 *************************************************************************************************/
void LOS_EvbUartReadByte(char* c)
{
#ifdef LOS_STM32L476xx
    if(HAL_UART_Receive(&UartHandle, (uint8_t *)c, 1, 5000) != HAL_OK)
    {
        Error_Handler();
    }
#endif
    return;
}

#ifdef LOS_STM32L476xx
static char _buffer[128];
#endif

void LOS_EvbUartPrintf(char* fmt, ...)
{
#ifdef LOS_STM32L476xx
    int i;
    va_list ap;
    va_start(ap, fmt);
    vsprintf(_buffer, fmt, ap);
    va_end(ap);

    for (i = 0; _buffer[i] != '\0'; i++)
    {
        LOS_EvbUartWriteByte(_buffer[i]);
    }
#endif
    return;
}

/**
  * @brief Rx Transfer completed callback.
  * @param huart UART handle.
  * @retval None
  */
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
     
  /* NOTE : This function should not be modified, when the callback is needed,
            the HAL_UART_RxCpltCallback can be implemented in the user file.
   */
//	PRINT_DEBUG("[%s] Enter... ucTmp = %c \r\n", __FUNCTION__, strEsp8266_Fram_Record.ucTmp);
	
	if ( strEsp8266_Fram_Record .InfBit .FramLength < ( RX_BUF_MAX_LEN - 1 ) )                       //预留1个字节写结束符
		strEsp8266_Fram_Record .Data_RX_BUF [ strEsp8266_Fram_Record .InfBit .FramLength ++ ]  = strEsp8266_Fram_Record.ucTmp;

	HAL_UART_Receive_IT(&ESP8266UartHandle, &strEsp8266_Fram_Record.ucTmp, 1);	//RX_BUF_MAX_LEN
	
}

