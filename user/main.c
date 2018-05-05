#include "los_sys.h"
#include "los_tick.h"
#include "los_task.ph"
#include "los_config.h"

#include "los_inspect_entry.h"
#include "los_demo_entry.h"
#include "los_api_fs.h"

#include "los_bsp_led.h"
#include "los_bsp_key.h"
#include "los_bsp_uart.h"

#include "eeprom.h"
#include "bsp_elink.h" 
#include "bsp_esp8266.h"
#include "HallDisplay.h"
#include "HallWIFI.h"

#include <string.h>

#ifdef LOS_CMBACKTRACE_COMPILE
#define HARDWARE_VERSION               "V1.0.0"
#define SOFTWARE_VERSION               "V0.1.0"
#endif

uint8_t aReadBuffer[1024];

static UINT32 g_uwboadTaskID;
static LITE_OS_SEC_TEXT void LOS_DisplayDemoTskfunc(void)
{
		PRINT_INFO("[%s] Enter...\r\n",__FUNCTION__);
	
		/**elink SPI init**/
		elink_spi_gpio_config();

		/**elink ePaper init**/
		elink_lcd_gpio_config();

		elink_display_init();
		
//		ELINK042_DispString_EN_CH( 128, 192, "Hello World...", WHITE); 
		ELINK042_DispString_EN_CH( 64, 64, "华为电子标签[20180415] abcdefghijklmn\r\n123456789", WHITE);
//		ELINK042_DispString_EN_CH( 128, 128, "HuaWei electric tag", WHITE); 
		
//		PRINT_DEBUG( "\r\n[BIRD] WF-ESP8266 WiFi模块测试...\r\n" );//打印测试例程提示信息

		ESP8266_StaTcpClient_UnvarnishTest();
		
		/************************power off Sequence************************/
		/**Vcom and data interval setting**/
		elink_soft_vcom_set();

		/**Power off**/
		elink_soft_power_switch(0);	
		
		/**deep sleep**/
		elink_soft_deep_sleep();
	
    while (1)
    {
//				PRINT_DEBUG("[%s] Board Hardware Test...\r\n",__FUNCTION__);
//				PRINT_DEBUG("%s", strEsp8266_Fram_Record.Data_RX_BUF);
			
        LOS_EvbLedControl(LOS_LED2, LED_ON);
        LOS_TaskDelay(500);
        LOS_EvbLedControl(LOS_LED2, LED_OFF);
        LOS_TaskDelay(500);
    }
}

void LOS_DisplayDemo_Entry(void)
{
    UINT32 uwRet;
    TSK_INIT_PARAM_S stTaskInitParam;

    (VOID)memset((void *)(&stTaskInitParam), 0, sizeof(TSK_INIT_PARAM_S));
    stTaskInitParam.pfnTaskEntry = (TSK_ENTRY_FUNC)LOS_DisplayDemoTskfunc;
    stTaskInitParam.uwStackSize = LOSCFG_BASE_CORE_TSK_IDLE_STACK_SIZE;
    stTaskInitParam.pcName = "BoardDemo";
    stTaskInitParam.usTaskPrio = 12;
    uwRet = LOS_TaskCreate(&g_uwboadTaskID, &stTaskInitParam);

    if (uwRet != LOS_OK)
    {
				PRINT_ERR("[%s] DisplayDemo task create ERROR !!! \r\n", __FUNCTION__);
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
		
//		/* Read chip internal flash(addr:[0x08080000]) by Byte test */
//		EEPROM_ReadBytes(0, aReadBuffer, 32);
//		
//		/* USER CODE END 2 */
//		for(uint8_t i = 0; i < 32; i++ )
//		{
//			printf("\n\r aReadBuffer[%d] = %#02x", i, aReadBuffer[i] );
//		}
		
//    LOS_Demo_Entry();

//    LOS_Inspect_Entry();

    LOS_DisplayDemo_Entry();

//		Example_Fs_Entry();
		
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
