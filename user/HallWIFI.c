/**
  ******************************************************************************
  * @file    HallWIFI.c
  * @author  Sky.Ye
  * @version V1.0
  * @date    2018-03-xx
  * @brief   ESP8266 WiFi + Elink 4.2inch ePaper模块测试
  ******************************************************************************/
	
#include "HallWIFI.h"
#include "HallDisplay.h"

#include "bsp_esp8266.h"
#include "los_bsp_led.h"
#include "los_demo_debug.h"
#include "cmsis_os.h"

/**
  * @brief  ESP8266 （Sta Tcp Client）透传
  * @param  无
  * @retval 无
  */
void ESP8266_StaTcpClient_UnvarnishTest ( void )
{
	uint8_t ucId, ucLen;
	uint8_t ucLed1Status = 0, ucLed2Status = 0, ucLed3Status = 0, ucBuzzerStatus = 0;

	char cStr[ 100 ] = { 0 }, cCh;
	char cInfo[ 100 ] = { 0 };
  char * pCh, * pCh1;

  PRINT_INFO( "\r\n[%s] 正在配置 ESP8266 ......\r\n", __FUNCTION__ );

	macESP8266_CH_ENABLE();
	
	ESP8266_AT_Test();
	
	ESP8266_Net_Mode_Choose( AP );

  while ( ! ESP8266_CIPAP( macUser_ESP8266_TcpServer_IP ) );

  while ( ! ESP8266_BuildAP( macUser_ESP8266_BulitApSsid, macUser_ESP8266_BulitApPwd, macUser_ESP8266_BulitApEcn ) );	
	
	ESP8266_Enable_MultipleId( ENABLE );
	
	while ( !	ESP8266_StartOrShutServer( ENABLE, macUser_ESP8266_TcpServer_Port, macUser_ESP8266_TcpServer_OverTime ) );

	ESP8266_Inquire_ApIp( cStr, 20 );
	PRINT_INFO( "\r\n本模块WIFI为%s，密码开放\r\nAP IP 为：%s，开启的端口为：%s\r\n手机网络助手连接该 IP 和端口，最多可连接5个客户端\r\n",
           macUser_ESP8266_BulitApSsid, cStr, macUser_ESP8266_TcpServer_Port );
	
	
	strEsp8266_Fram_Record .InfBit .FramLength = 0;
	strEsp8266_Fram_Record .InfBit .FramFinishFlag = 0;	
	
	while ( 1 )
	{
		if ( strEsp8266_Fram_Record.InfBit.FramFinishFlag )
		{
//			__HAL_UART_DISABLE_IT(&ESP8266UartHandle, USART_IT_RXNE);	//禁用串口接收中断
			strEsp8266_Fram_Record.Data_RX_BUF[ strEsp8266_Fram_Record.InfBit.FramLength ]  = '\0';
			
			PRINT_INFO( "\r\n[%s] %s\r\n", __FUNCTION__, strEsp8266_Fram_Record .Data_RX_BUF );
			osDelay(10);
			
			if ( ( pCh = strstr ( strEsp8266_Fram_Record .Data_RX_BUF, "CMD_LED_" ) ) != 0 ) 
			{
				cCh = * ( pCh + 8 );
			
				switch ( cCh )
				{
					case '1':
						cCh = * ( pCh + 10 );
					  switch ( cCh )
					  {
							case '0':
								LOS_EvbLedControl(LOS_LED2, LED_OFF);
							  ucLed1Status = 0;
						    break;
							case '1':
								LOS_EvbLedControl(LOS_LED2, LED_ON);
							  ucLed1Status = 1;
						    break;
							default :
								break;
						}
						break;
						
					case '2':
						cCh = * ( pCh + 10 );
					  switch ( cCh )
					  {
							case '0':
								LOS_EvbLedControl(LOS_LED2, LED_OFF);
							  ucLed2Status = 0;
						    break;
							case '1':
								LOS_EvbLedControl(LOS_LED2, LED_ON);
							  ucLed2Status = 1;
						    break;
							default :
								break;
						}
						break;

					case '3':
						cCh = * ( pCh + 10 );
					  switch ( cCh )
					  {
							case '0':
								LOS_EvbLedControl(LOS_LED2, LED_OFF);
							  ucLed3Status = 0;
						    break;
							case '1':
								LOS_EvbLedControl(LOS_LED2, LED_ON);
							  ucLed3Status = 1;
						    break;
							default :
								break;
						}
						break;
						
				  default :
            break;					
						
				}
				
				sprintf ( cStr, "CMD_LED_%d_%d_%d_ENDLED_END", ucLed1Status, ucLed2Status, ucLed3Status );
				
			}
			
			else if ( ( pCh = strstr ( strEsp8266_Fram_Record .Data_RX_BUF, "CMD_BUZZER_" ) ) != 0 ) 
			{
				cCh = * ( pCh + 11 );
				
				switch ( cCh )
				{
					case '0':
//						macBEEP_OFF ();
					  ucBuzzerStatus = 0;
						ELINK042_DispString_EN_CH( 64, 80, (const uint8_t *)pCh, WHITE); //display CMD infomation on the Elink ePaper
					
						break;
					case '1':
//						macBEEP_ON ();
					  ucBuzzerStatus = 1;
						ELINK042_DispString_EN_CH( 64, 96, (const uint8_t *)pCh, WHITE); //display CMD infomation on the Elink ePaper				
					
						break;
					default:
						break;
				}
				
				sprintf ( cStr, "CMD_BUZZER_%d_ENDBUZZER_END", ucBuzzerStatus );
				
			}
				
			else if ( ( ( pCh  = strstr ( strEsp8266_Fram_Record .Data_RX_BUF, "CMD_UART_" ) ) != 0 ) && 
				        ( ( pCh1 = strstr ( strEsp8266_Fram_Record .Data_RX_BUF, "_ENDUART_END" ) )  != 0 ) ) 
			{
				if ( pCh < pCh1)
				{
					ucLen = pCh1 - pCh + 12;
					memcpy( cStr, pCh, ucLen );
					cStr[ ucLen ] = '\0';
					
					memcpy( cInfo, pCh + strlen( "CMD_UART_" ), pCh1 - pCh - strlen( "CMD_UART_" ) );
					cInfo[ pCh1 - pCh - strlen( "CMD_UART_" ) ] = '\0';
					ELINK042_DispString_EN_CH( 0, 128, (const uint8_t *)cInfo, WHITE); //display CMD infomation on the Elink ePaper					
				}
			}			
				
			if ( ( pCh = strstr( strEsp8266_Fram_Record .Data_RX_BUF, "+IPD," ) ) != 0 ) 
			{
				ucId = * ( pCh + strlen ( "+IPD," ) ) - '0';
				ESP8266_SendString( DISABLE, cStr, strlen ( cStr ), ( ENUM_ID_NO_TypeDef ) ucId );
			}
			
		  strEsp8266_Fram_Record .InfBit .FramLength = 0;
	    strEsp8266_Fram_Record .InfBit .FramFinishFlag = 0;	
			
//			__HAL_UART_ENABLE_IT(&ESP8266UartHandle, USART_IT_RXNE);	//使能串口接收中断
		}
		
	}
	
		
}


