#ifndef __HALL_DISPLAY_H_
#define	__HALL_DISPLAY_H_

#include "stdint.h"


/***************** ILI934 ��ʾ��ȫ��Ĭ�ϣ�ɨ�跽��Ϊ1ʱ������Ⱥ����߶� *********************/
#define      ELINK042_Default_Max_Width		  400     //���
#define      ELINK042_Default_Max_Heigth		300     //�߶�


#define      WHITE		 		                  0xFFFF	   //��ɫ
#define      BLACK                         	0x0000	   //��ɫ 



/***************************** ILI934 ��ʾ�������ʼ������������� ***************************/
#define      ELINK042_DispWindow_X_Star		    0     //��ʼ���X����
#define      ELINK042_DispWindow_Y_Star		    0     //��ʼ���Y����

#define      ELINK042_DispWindow_COLUMN		  400     //������
#define      ELINK042_DispWindow_PAGE		    300     //������



/***************************** �� ILI934 ��ʾ������ʾ���ַ��Ĵ�С ***************************/
#define      WIDTH_EN_CHAR		             8	    //Ӣ���ַ���� 
#define      HEIGHT_EN_CHAR		            16		  //Ӣ���ַ��߶� 

#define      EN_CHAR_0816_BYTE		            16		  //Ӣ���ַ�8*16�ֽ���


#define      WIDTH_CH_CHAR		              16	    //�����ַ���� 
#define      HEIGHT_CH_CHAR		              16		  //�����ַ��߶� 

#define      CN_CHAR_1616_BYTE		            32		  //�����ַ�16*16�ֽ���


#define      GetGBKCode( ucBuffer, usChar )  GetGBKCode_from_EXFlash( ucBuffer, usChar )  //�����ȡ�����ַ���ģ����ĺ�������ucBufferΪ�����ģ��������usCharΪ�����ַ��������룩



/************************** PAD ��������********************************/


void Elink042DispChinaString( uint16_t usX, uint16_t usY, const uint8_t * pStr, uint16_t usColor_Background ); 
void ELINK042_DispString_EN_CH ( uint16_t usX, uint16_t usY, const uint8_t * pStr, uint16_t usColor_Background );


#endif /* __HALL_DISPLAY_H_ */

