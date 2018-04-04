#ifndef __BSP_ELINK_H_
#define	__BSP_ELINK_H_

#include "bsp_spi.h"
#include "los_typedef.h"

#ifdef LOS_STM32L476xx
#include "stm32l4xx_hal.h"
#include "stm32l4xx_nucleo.h"
#endif


/****************************** LED 引脚配置参数定义***************************************/
#define             LCD_RST_GPIO_PORT                      GPIOB
#define             LCD_RST_GPIO_PIN                       GPIO_PIN_9

#define             LCD_BUSY_GPIO_PORT                     GPIOB
#define             LCD_BUSY_GPIO_PIN                      GPIO_PIN_8

#define             LCD_BS_GPIO_PORT                       GPIOB
#define             LCD_BS_GPIO_PIN                        GPIO_PIN_13


/****************************** LED 函数宏定义***************************************/
#define LCD_RST_GPIO_CLK_ENABLE()             __HAL_RCC_GPIOB_CLK_ENABLE()
#define LCD_BUSY_GPIO_CLK_ENABLE()            __HAL_RCC_GPIOB_CLK_ENABLE()
#define LCD_BS_GPIO_CLK_ENABLE()             	__HAL_RCC_GPIOB_CLK_ENABLE()


#define nRST_H 		HAL_GPIO_WritePin( LCD_RST_GPIO_PORT, LCD_RST_GPIO_PIN, GPIO_PIN_SET )  		//PE.14
#define nRST_L 		HAL_GPIO_WritePin( LCD_RST_GPIO_PORT, LCD_RST_GPIO_PIN, GPIO_PIN_RESET )

#define nBUSY  		HAL_GPIO_ReadPin(LCD_BUSY_GPIO_PORT, LCD_BUSY_GPIO_PIN) //PE.13

#define nBS_H  HAL_GPIO_WritePin( LCD_BS_GPIO_PORT, LCD_BS_GPIO_PIN, GPIO_PIN_SET )			//PE.11
#define nBS_L  HAL_GPIO_WritePin( LCD_BS_GPIO_PORT, LCD_BS_GPIO_PIN, GPIO_PIN_RESET )

//#define VPP_H	 GPIO_SetBits(GPIOA, GPIO_PIN_4)		//PA4
//#define VPP_L	 GPIO_ResetBits(GPIOA, GPIO_PIN_4)

/***************************变量定义******************************/



/************************** PAD 函数声明********************************/

void	elink_lcd_gpio_config(void);
void	elink_epd_w21_reset(void);
void	elink_check_busy_status(void);

void elink_booster_soft_start(void);
void elink_soft_panel_set(void);
void elink_soft_vcom_set(void);
void elink_soft_disp_refresh(void);
void elink_soft_deep_sleep(void);
void elink_soft_power_switch(unsigned char status);

void lut(void);
void lut1(void);

void elink_display_init(void);
void elink_framebuffer_display(const unsigned char * pStr);

void  partial_display(UINT8 x_start1, UINT8 x_start2, UINT8 x_end1, UINT8 x_end2, UINT8 y_start1, UINT8 y_start2, UINT8 y_end1, UINT8 y_end2, UINT8* pOldBuff, UINT8* pNewBuff, UINT16 length);



#endif /* __LED_H_ */

