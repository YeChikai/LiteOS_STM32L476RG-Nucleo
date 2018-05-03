#ifndef  __HALLWIFI_H
#define	 __HALLWIFI_H


#include "los_typedef.h"

#ifdef LOS_STM32L476xx
#include "stm32l4xx_hal.h"
#include "stm32l4xx_nucleo.h"
#endif



/********************************** �û���Ҫ���õĲ���**********************************/
#define   macUser_ESP8266_BulitApSsid         "BirdLink"      //Ҫ�������ȵ������
#define   macUser_ESP8266_BulitApEcn           OPEN               //Ҫ�������ȵ�ļ��ܷ�ʽ
#define   macUser_ESP8266_BulitApPwd           "bird123456"         //Ҫ�������ȵ����Կ

#define   macUser_ESP8266_TcpServer_IP         "192.168.123.169"  //������������IP��ַ
#define   macUser_ESP8266_TcpServer_Port       "8080"             //�����������Ķ˿�   

#define   macUser_ESP8266_TcpServer_OverTime   "1800"             //��������ʱʱ�䣨��λ���룩



/********************************** ���Ժ������� ***************************************/
void	ESP8266_StaTcpClient_UnvarnishTest( void );



#endif

