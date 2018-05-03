/**
  ******************************************************************************
  * @file    HallCommon.c
  * @author  Sky.Ye
  * @version V1.0
  * @date    2018-03-xx
  * @brief   ESP8266 WiFi + Elink 4.2inch ePaperģ�����
  ******************************************************************************/


#include "HallCommon.h"


static char * itoa( int value, char *string, int radix );


/*
 * ��������USART_printf
 * ����  ����ʽ�������������C���е�printf��������û���õ�C��
 * ����  ��-USARTx ����ͨ��
 *		     -Data   Ҫ���͵����ڵ����ݵ�ָ��
 *			   -...    ��������
 * ���  ����
 * ����  ���� 
 * ����  ���ⲿ����
 *         ����Ӧ��USART_printf( USART2, "\r\n this is a demo \r\n" );
 *            		 USART_printf( USART2, "\r\n %d \r\n", i );
 *            		 USART_printf( USART2, "\r\n %s \r\n", j );
 */
void USART_printf ( UART_HandleTypeDef * huart, char * Data, ... )
{
	const char *s;
	int d;   
	char buf[16];
	char ch;
	
	va_list ap;
	va_start(ap, Data);

	while ( * Data != 0 )     // �ж��Ƿ񵽴��ַ���������
	{				                          
		if ( * Data == 0x5c )  //'\'
		{									  
			switch ( *++Data )
			{
				case 'r':							          //�س���
				//USART_SendData(USARTx, 0x0d);
				ch = 0x0d;
				HAL_UART_Transmit(huart, (uint8_t*)&ch, 1, 5000);
				Data ++;
				break;

				case 'n':							          //���з�
				//USART_SendData(USARTx, 0x0a);	
				ch = 0x0a;
				HAL_UART_Transmit(huart, (uint8_t*)&ch, 1, 5000);				
				Data ++;
				break;

				default:
				Data ++;
				break;
			}			 
		}
		
		else if ( * Data == '%')
		{									  //
			switch ( *++Data )
			{				
				case 's':										  //�ַ���
				s = va_arg(ap, const char *);
				
				for ( ; *s; s++) 
				{					
					HAL_UART_Transmit(huart, (uint8_t*)s, 1, 5000);
				}
				
				Data++;
				
				break;

				case 'd':						//ʮ����
				d = va_arg(ap, int);
				
				itoa(d, buf, 10);
				
				for (s = buf; *s; s++) 
				{
					HAL_UART_Transmit(huart, (uint8_t*)s, 1, 5000);
				}
				
				Data++;
				
				break;
				
				default:
				Data++;
				
				break;
				
			}		 
		}
		
		else 
		{
			//USART_SendData(USARTx, *Data++);
			HAL_UART_Transmit(huart, (uint8_t*)Data++, 1, 5000);
		}

	}
}


/*
 * ��������itoa
 * ����  ������������ת�����ַ���
 * ����  ��-radix =10 ��ʾ10���ƣ��������Ϊ0
 *         -value Ҫת����������
 *         -buf ת������ַ���
 *         -radix = 10
 * ���  ����
 * ����  ����
 * ����  ����USART2_printf()����
 */
static char * itoa( int value, char *string, int radix )
{
	int     i, d;
	int     flag = 0;
	char    *ptr = string;

	/* This implementation only works for decimal numbers. */
	if (radix != 10)
	{
		*ptr = 0;
		return string;
	}

	if (!value)
	{
		*ptr++ = 0x30;
		*ptr = 0;
		return string;
	}

	/* if this is a negative value insert the minus sign. */
	if (value < 0)
	{
		*ptr++ = '-';

		/* Make the value positive. */
		value *= -1;
		
	}

	for (i = 10000; i > 0; i /= 10)
	{
		d = value / i;

		if (d || flag)
		{
			*ptr++ = (char)(d + 0x30);
			value -= (d * i);
			flag = 1;
		}
	}

	/* Null terminate the string. */
	*ptr = 0;

	return string;

} /* NCL_Itoa */



