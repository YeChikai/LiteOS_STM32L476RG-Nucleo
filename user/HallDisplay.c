/**
  ******************************************************************************
  * @file    HallDisplay.c
  * @author  Sky.Ye
  * @version V1.0
  * @date    2018-03-xx
  * @brief   ESP8266 WiFi + Elink 4.2inch ePaperģ�����
  ******************************************************************************/
	
#include "HallDisplay.h"

#include "bsp_elink.h"
#include "eeprom.h"
#include "los_demo_debug.h"
#include "ascii.h"
 
uint8_t OldBufferCN[32] = {0x00, 0x00, 0x00, 0x00,0x00, 0x00, 0x00, 0x00,0x00, 0x00, 0x00, 0x00,0x00, 0x00, 0x00, 0x00};
uint8_t OldBufferEN[16] = {0x00, 0x00, 0x00, 0x00,0x00, 0x00, 0x00, 0x00,0x00, 0x00, 0x00, 0x00,0x00, 0x00, 0x00, 0x00};
 
 

/**
 * @brief  �� Elink042 ��ʾ������ʾһ��Ӣ���ַ�
 * @param  usX �����ض�ɨ�跽�����ַ�����ʼX����
 * @param  usY �����ض�ɨ�跽���¸õ����ʼY����
 * @param  cChar ��Ҫ��ʾ��Ӣ���ַ�
 * @param  usColor_Background ��ѡ��Ӣ���ַ��ı���ɫ
 * @retval ��
 */
void Elink042_DispChar_EN( uint16_t usX, uint16_t usY, const char cChar, uint16_t usColor_Background)
{
	uint8_t ucRelativePositon, ucPage;
	uint8_t ucBuffer[16] = {0x00,0x00,0x00,0x66,0x66,0x66,0x66,0x7E,0x66,0x66,0x66,0x66,0x00,0x00,0x00,0x00};/*"H",40*/
	
	uint8_t x_start1 = usX >> 8;
	uint8_t x_start2 = usX & 0XFF;
	uint8_t x_end1 = (usX+WIDTH_EN_CHAR-1)>> 8;		//WIDTH_EN_CHAR
	uint8_t x_end2 = (usX+WIDTH_EN_CHAR-1)& 0XFF; //WIDTH_EN_CHAR
	
	uint8_t y_start1 = usY >> 8;
	uint8_t y_start2 = usY & 0XFF;
	uint8_t y_end1 = (usY+HEIGHT_EN_CHAR-1)>> 8; 
	uint8_t y_end2 = (usY+HEIGHT_EN_CHAR-1)& 0XFF;

	ucRelativePositon = cChar - ' ';	
		
	for( ucPage = 0; ucPage < HEIGHT_EN_CHAR; ucPage ++ )
	{
		ucBuffer[ucPage] = ucAscii_1608[ ucRelativePositon ] [ ucPage ];				
	}/* ȫ��д�� */
	
//	PRINT_DEBUG( "\r\n[%s] x_start1 = 0x%2x,	x_start2 = %d, x_end1 = 0x%2x, x_end2 = %d\r\n", __FUNCTION__, x_start1, x_start2, x_end1, x_end2 );
//	PRINT_DEBUG( "\r\n[%s] y_start1 = 0x%2x,	y_start2 = %d, y_end1 = 0x%2x, y_end2 = %d\r\n", __FUNCTION__, y_start1, y_start2, y_end1, y_end2 );
	
	partial_display(x_start1, x_start2,x_end1, x_end2, y_start1, y_start2, y_end1, y_end2, OldBufferEN, ucBuffer,EN_CHAR_0816_BYTE);
}

/**
 * @brief  �� Elink ��ʾ������ʾһ�������ַ�
 * @param  usX �����ض�ɨ�跽�����ַ�����ʼX����
 * @param  usY �����ض�ɨ�跽�����ַ�����ʼY����
 * @param  usChar ��Ҫ��ʾ�������ַ��������룩 
 * @retval ��
 */ 
void Elink042_DispChar_CN ( uint16_t usX, uint16_t usY, uint16_t usChar, uint16_t usColor_Background)
{
	uint8_t ucBuffer[32] = {0x00, 0x00};
 	
	uint8_t x_start1 = usX >> 8;
	uint8_t x_start2 = usX & 0XFF;
	uint8_t x_end1 = (usX+WIDTH_CH_CHAR-1)>> 8;
	uint8_t x_end2 = (usX+WIDTH_CH_CHAR-1)& 0XFF; 
	
	uint8_t y_start1 = usY >> 8;
	uint8_t y_start2 = usY & 0XFF;
	uint8_t y_end1 = (usY+HEIGHT_CH_CHAR-1)>> 8; 
	uint8_t y_end2 = (usY+HEIGHT_CH_CHAR-1)& 0XFF;
	   
  GetGBKCode( ucBuffer, usChar );	//ȡ��ģ����
	
	partial_display(x_start1, x_start2,x_end1, x_end2, y_start1, y_start2, y_end1, y_end2, OldBufferCN, ucBuffer, CN_CHAR_1616_BYTE);
		
}


/**
 * @brief  �� Elink ��ʾ������ʾ�����ַ���
 * @param  usX �����ض�ɨ�跽�����ַ�������ʼX����
 * @param  usY �����ض�ɨ�跽�����ַ�������ʼY����
 * @param  pStr ��Ҫ��ʾ��Ӣ���ַ������׵�ַ
 * @param  usColor_Background ��ѡ���ַ����ı���ɫ
 * @retval ��
 */
void Elink042DispChinaString( uint16_t usX, uint16_t usY, const uint8_t * pStr, uint16_t usColor_Background)
{	
	uint16_t usCh;
		
	while( * pStr != '\0' )
	{		
		if ( ( usX - ELINK042_DispWindow_X_Star + WIDTH_CH_CHAR ) > ELINK042_DispWindow_COLUMN )
		{
			usX = ELINK042_DispWindow_X_Star;
			usY += HEIGHT_CH_CHAR;
		}
		
		if ( ( usY - ELINK042_DispWindow_Y_Star + HEIGHT_CH_CHAR ) > ELINK042_DispWindow_PAGE )
		{
			usX = ELINK042_DispWindow_X_Star;
			usY = ELINK042_DispWindow_Y_Star;
		}	
		
		usCh = * ( uint16_t * ) pStr;	
	  usCh = ( usCh << 8 ) + ( usCh >> 8 );//��С��ת��

		Elink042_DispChar_CN( usX, usY, usCh, usColor_Background );
		
		usX += WIDTH_CH_CHAR;
		
		pStr += 2;           //һ�����������ֽ� 

	}	   
	
}


/**
 * @brief  �� ELINK042 ��ʾ������ʾ��Ӣ���ַ���
 * @param  usX �����ض�ɨ�跽�����ַ�������ʼX����
 * @param  usY �����ض�ɨ�跽�����ַ�������ʼY����
 * @param  pStr ��Ҫ��ʾ���ַ������׵�ַ
 * @param  usColor_Background ��ѡ���ַ����ı���ɫ
 * @retval ��
 */
void ELINK042_DispString_EN_CH ( uint16_t usX, uint16_t usY, const uint8_t * pStr, uint16_t usColor_Background )
{
	uint16_t usCh;
	
	SPI4W_WRITECOM(0X50);
	SPI4W_WRITEDATA(0x47);	//0x47 White background; 0x17 Black background

	lut1();		
	
	while( * pStr != '\0' )
	{
		if ( * pStr <= 126 )	           	//Ӣ���ַ�
		{
			if ( ( usX - ELINK042_DispWindow_X_Star + WIDTH_EN_CHAR ) > ELINK042_DispWindow_COLUMN )
			{
				usX = ELINK042_DispWindow_X_Star;
				usY += HEIGHT_EN_CHAR;
			}
			
			if ( ( usY - ELINK042_DispWindow_Y_Star + HEIGHT_EN_CHAR ) > ELINK042_DispWindow_PAGE )
			{
				usX = ELINK042_DispWindow_X_Star;
				usY = ELINK042_DispWindow_Y_Star;
			}			
		
		  Elink042_DispChar_EN( usX, usY, * pStr, usColor_Background);
			PRINT_DEBUG( "\r\n[%s] English char: %c	\r\n",__FUNCTION__, * pStr );
			
			usX += WIDTH_EN_CHAR;
		
		  pStr++;

		}		
		else	                            //�����ַ�
		{
			if ( ( usX - ELINK042_DispWindow_X_Star + WIDTH_CH_CHAR ) > ELINK042_DispWindow_COLUMN )
			{
				usX = ELINK042_DispWindow_X_Star;
				usY += HEIGHT_CH_CHAR;
			}
			
			if ( ( usY - ELINK042_DispWindow_Y_Star + HEIGHT_CH_CHAR ) > ELINK042_DispWindow_PAGE )
			{
				usX = ELINK042_DispWindow_X_Star;
				usY = ELINK042_DispWindow_Y_Star;
			}	
			
			usCh = * ( uint16_t * ) pStr;	
			
			usCh = ( usCh << 8 ) + ( usCh >> 8 );		

			Elink042_DispChar_CN( usX, usY, usCh, usColor_Background);
			PRINT_DEBUG( "\r\n[%s] Chinese char: %ls \r\n",__FUNCTION__, ( uint16_t * ) pStr );
			
			usX += WIDTH_CH_CHAR;
			
			pStr += 2;           //һ�����������ֽ� 
		
    }
		
  }
	
	PRINT_DEBUG( "\r\n[%s] Display String complished !!!\r\n", __FUNCTION__ );	
} 


/*******************************************************************************
* Function Name  : GetGBKCode_from_FLASH
*******************************************************************************/ 
int GetGBKCode_from_Flash( uint8_t * pBuffer, uint16_t c)
{ 
	unsigned char High8bit,Low8bit;
	unsigned int pos;


	High8bit= c >> 8;     /* ȡ��8λ���� */
	Low8bit= c & 0x00FF;  /* ȡ��8λ���� */	


	pos = ((High8bit-0xa0-16)*94+Low8bit-0xa0-1)*2*16;
	EEPROM_ReadBytes(pos, pBuffer, CN_CHAR_1616_BYTE);

//	PRINT_DEBUG( "High8bit[%02x] Low8bit[%02x] position:[%d] %02x %02x %02x %02x\n", High8bit, Low8bit, pos, pBuffer[0],pBuffer[1],pBuffer[2],pBuffer[3]);

	return 0;       
}


/*********************************************END OF FILE**********************/
