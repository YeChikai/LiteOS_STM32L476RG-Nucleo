#include "los_bsp_key.h"
#include "los_demo_debug.h"

#ifdef USE_STM32L4XX_NUCLEO
#include "stm32l4xx_hal.h"
#include "stm32l4xx_nucleo.h"
#endif

void LOS_EvbKeyInit(void)
{

#ifdef USE_STM32L4XX_NUCLEO
	
	BSP_PB_Init(BUTTON_KEY, BUTTON_MODE_EXTI);//BUTTON_MODE_EXTI	BUTTON_MODE_GPIO
	
#endif

}

#ifdef USE_STM32L4XX_NUCLEO
/**
  * @brief EXTI line detection callbacks
  * @param GPIO_Pin: Specifies the pins connected EXTI line
  * @retval None
  */
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
    if (GPIO_Pin == USER_BUTTON_PIN)
    {
//      BSP_LED_Toggle(LED2);
//			Debug("Key EXTI Interuption happened\r\n");
			PRINT_DEBUG("[%s] Los Key EXTI Interuption happened \r\n", __FUNCTION__);
    }
}
#endif


/*****************************************************************************
 Function    : LOS_EvbGetKeyVal
 Description : Get GIOP Key value
 Input       : int KeyNum
 Output      : None
 Return      : KeyVal
 *****************************************************************************/
unsigned int LOS_EvbGetKeyVal(int KeyNum)
{
    unsigned int KeyVal = LOS_GPIO_ERR; 
    
    //add you code here.
#ifdef USE_STM32L4XX_NUCLEO
	
		KeyVal = BSP_PB_GetState(BUTTON_KEY);
	
#endif
	
    return KeyVal;
}

