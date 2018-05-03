#ifndef __BSP_SPI_H_
#define	__BSP_SPI_H_

#include "los_task.h"
#include "los_bsp_adapter.h"

#ifdef LOS_STM32L476xx
#include "stm32l4xx_hal.h"
#include "stm32l4xx_nucleo.h"
#endif


/****************************** LED 引脚配置参数定义***************************************/
#define             SPI_CLK_GPIO_PORT                       GPIOA
#define             SPI_CLK_GPIO_PIN                        GPIO_PIN_8

#define             SPI_SDA_GPIO_PORT                       GPIOA
#define             SPI_SDA_GPIO_PIN                        GPIO_PIN_6

#define             SPI_nDC_GPIO_PORT                       GPIOA
#define             SPI_nDC_GPIO_PIN                        GPIO_PIN_7

#define             SPI_nCS_GPIO_PORT                       GPIOB
#define             SPI_nCS_GPIO_PIN                        GPIO_PIN_6

/****************************** LED 函数宏定义***************************************/
#define SPI_CLK_GPIO_CLK_ENABLE()             __HAL_RCC_GPIOA_CLK_ENABLE()
#define SPI_SDA_GPIO_CLK_ENABLE()             __HAL_RCC_GPIOA_CLK_ENABLE()
#define SPI_nDC_GPIO_CLK_ENABLE()             __HAL_RCC_GPIOA_CLK_ENABLE()
#define SPI_nCS_GPIO_CLK_ENABLE()             __HAL_RCC_GPIOB_CLK_ENABLE()


#define SDA_H()  HAL_GPIO_WritePin(SPI_SDA_GPIO_PORT, SPI_SDA_GPIO_PIN, GPIO_PIN_SET)	  //PD.8
#define SDA_L()  HAL_GPIO_WritePin(SPI_SDA_GPIO_PORT, SPI_SDA_GPIO_PIN, GPIO_PIN_RESET)	  

#define SCLK_H() HAL_GPIO_WritePin(SPI_CLK_GPIO_PORT, SPI_CLK_GPIO_PIN, GPIO_PIN_SET)	  //PD.9
#define SCLK_L() HAL_GPIO_WritePin(SPI_CLK_GPIO_PORT, SPI_CLK_GPIO_PIN, GPIO_PIN_RESET)

#define nCS_H()  HAL_GPIO_WritePin(SPI_nCS_GPIO_PORT, SPI_nCS_GPIO_PIN, GPIO_PIN_SET)	  //PD.10
#define nCS_L()  HAL_GPIO_WritePin(SPI_nCS_GPIO_PORT, SPI_nCS_GPIO_PIN, GPIO_PIN_RESET)

#define nDC_H()  HAL_GPIO_WritePin(SPI_nDC_GPIO_PORT, SPI_nDC_GPIO_PIN, GPIO_PIN_SET) //PE.15
#define nDC_L()  HAL_GPIO_WritePin(SPI_nDC_GPIO_PORT, SPI_nDC_GPIO_PIN, GPIO_PIN_RESET)

/************************** PAD 函数声明********************************/

void elink_spi_gpio_config(void);
void SPI4W_WRITECOM(unsigned char INIT_COM);
void SPI4W_WRITEDATA(unsigned char INIT_DATA);
void SPI4W_WRITE(unsigned char INIT_COM,unsigned char INIT_DATA);

 
 

#endif /* __LED_H_ */

