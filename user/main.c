#include "los_sys.h"
#include "los_tick.h"
#include "los_task.ph"
#include "los_config.h"

#include "los_inspect_entry.h"
#include "los_demo_entry.h"

#include "los_bsp_led.h"
#include "los_bsp_key.h"
#include "los_bsp_uart.h"

#include "bsp_elink.h" 
#include "HallDisplay.h"

#include <string.h>

#ifdef LOS_CMBACKTRACE_COMPILE
#define HARDWARE_VERSION               "V1.0.0"
#define SOFTWARE_VERSION               "V0.1.0"
#endif

extern void LOS_EvbSetup(void);

static UINT32 g_uwboadTaskID;
static LITE_OS_SEC_TEXT void LOS_BoardExampleTskfunc(void)
{
		PRINT_DEBUG("[%s] Enter...\r\n",__FUNCTION__);
	
		/**elink SPI init**/
		elink_spi_gpio_config();

		/**elink ePaper init**/
		elink_lcd_gpio_config();

		elink_display_init();
		
		ELINK042_DispString_EN_CH( 128, 192, "Hello World...", WHITE); 
//		ELINK042_DispString_EN_CH( 64, 64, "��Ϊ���ӱ�ǩ", WHITE); 
		ELINK042_DispString_EN_CH( 128, 128, "HuaWei electric tag", WHITE); 
		
//		PRINT_DEBUG( "\r\n[BIRD] WF-ESP8266 WiFiģ�����...\r\n" );//��ӡ����������ʾ��Ϣ

//		ESP8266_StaTcpClient_UnvarnishTest();
		
		/************************power off Sequence************************/
		/**Vcom and data interval setting**/
		elink_soft_vcom_set();

		/**Power off**/
		elink_soft_power_switch(0);	
		
		/**deep sleep**/
		elink_soft_deep_sleep();
	
    while (1)
    {
				PRINT_DEBUG("[%s] Board Hardware Test...\r\n",__FUNCTION__);
			
        LOS_EvbLedControl(LOS_LED2, LED_ON);
        LOS_TaskDelay(500);
        LOS_EvbLedControl(LOS_LED2, LED_OFF);
        LOS_TaskDelay(500);
    }
}

void LOS_BoardExampleEntry(void)
{
    UINT32 uwRet;
    TSK_INIT_PARAM_S stTaskInitParam;

    (VOID)memset((void *)(&stTaskInitParam), 0, sizeof(TSK_INIT_PARAM_S));
    stTaskInitParam.pfnTaskEntry = (TSK_ENTRY_FUNC)LOS_BoardExampleTskfunc;
    stTaskInitParam.uwStackSize = LOSCFG_BASE_CORE_TSK_IDLE_STACK_SIZE;
    stTaskInitParam.pcName = "BoardDemo";
    stTaskInitParam.usTaskPrio = 12;
    uwRet = LOS_TaskCreate(&g_uwboadTaskID, &stTaskInitParam);

    if (uwRet != LOS_OK)
    {
				PRINT_ERR("[%s] BoardExample task create ERROR !!! \r\n", __FUNCTION__);
        return;
    }
    return;
}

/*****************************************************************************
Function    : main
Description : Main function entry
Input       : None
Output      : None
Return      : None
 *****************************************************************************/
LITE_OS_SEC_TEXT_INIT
int main(void)
{
    UINT32 uwRet;
    /*
        add you hardware init code here
        for example flash, i2c , system clock ....
     */
//    HAL_Init();
    
#ifdef LOS_CMBACKTRACE_COMPILE
    cm_backtrace_init("LOS_CmBacktrace", HARDWARE_VERSION, SOFTWARE_VERSION);
#endif

    /*Init LiteOS kernel */
    uwRet = LOS_KernelInit();
    if (uwRet != LOS_OK) {
        return LOS_NOK;
    }
    /* Enable LiteOS system tick interrupt */
    uwRet = LOS_EnableTick();
    if (uwRet != LOS_OK) {
        return LOS_NOK;
    }
   
    /*
        Notice: add your code here
        here you can create task for your function 
        do some hw init that need after systemtick init
     */
    LOS_EvbSetup();	//init the device on the dev baord

//    LOS_Demo_Entry();

//    LOS_Inspect_Entry();

    LOS_BoardExampleEntry();

    /* Kernel start to run */
    (void)LOS_Start();
		
		while(1)
		{

//		/* USER CODE END WHILE */
//			BSP_LED_Toggle(LED2);
//		/* USER CODE BEGIN 3 */
//			HAL_Delay(500);

//			PRINT_DEBUG("hello,world!\r\n");
			
		}
    /* Replace the dots (...) with your own code. */
}
