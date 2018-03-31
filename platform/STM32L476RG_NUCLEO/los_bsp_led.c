#include "los_bsp_led.h"

#ifdef USE_STM32L4XX_NUCLEO

#include "stm32l4xx_hal.h"
#include "stm32l4xx_nucleo.h"

#endif

void LOS_EvbLedInit(void)
{

#ifdef USE_STM32L4XX_NUCLEO
    BSP_LED_Init(LED2);
#endif

    return;
}

/*************************************************************************************************
 *  function��control led on off                                                                 *
 *  param (1) index Led's index                                                                  *
 *        (2) cmd   Led on or off                                                                *
 *  return : None                                                                                *
 *  discription:                                                                                 *
**************************************************************************************************/
void LOS_EvbLedControl(int index, int cmd)
{
#ifdef USE_STM32L4XX_NUCLEO
    switch (index)
    {
        case LOS_LED2:
        {
            if (cmd == LED_ON)
            {
                BSP_LED_On(LED2); /*led2 on */
            }
            else
            {
                BSP_LED_Off(LED2); /*led2 off */
            }
            break;
        }
        default:
        {
            break;
        }
    }
#endif
    return;
}


