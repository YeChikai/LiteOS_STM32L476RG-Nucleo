/**
  ******************************************************************************
  * @file    bsp_elink.c
  * @author  Sky.Ye
  * @version V1.0
  * @date    2018-03-xx
  * @brief   ESP8266 WiFi + Elink 4.2inch ePaperģ�����
  ******************************************************************************/

#include "bsp_elink.h"   
#include "DisplayBuffer.h"

#include "cmsis_os.h"
#include "los_demo_debug.h"


const unsigned char lut_vcomDC[] ={
0x00	,0x08	,0x00	,0x00	,0x00	,0x02,	
0x60	,0x28	,0x28	,0x00	,0x00	,0x01,	
0x00	,0x14	,0x00	,0x00	,0x00	,0x01,	
0x00	,0x12	,0x12	,0x00	,0x00	,0x01,	
0x00	,0x00	,0x00	,0x00	,0x00	,0x00,	
0x00	,0x00	,0x00	,0x00	,0x00	,0x00,	
0x00	,0x00	,0x00	,0x00	,0x00	,0x00	
,0x00	,0x00,					};
const unsigned char  lut_ww[] ={	
0x40	,0x08	,0x00	,0x00	,0x00	,0x02,	
0x90	,0x28	,0x28	,0x00	,0x00	,0x01,	
0x40	,0x14	,0x00	,0x00	,0x00	,0x01,	
0xA0	,0x12	,0x12	,0x00	,0x00	,0x01,	
0x00	,0x00	,0x00	,0x00	,0x00	,0x00,	
0x00	,0x00	,0x00	,0x00	,0x00	,0x00,	
0x00	,0x00	,0x00	,0x00	,0x00	,0x00,	};
const unsigned char  lut_bw[] ={	
0x40	,0x17	,0x00	,0x00	,0x00	,0x02	,
0x90	,0x0F	,0x0F	,0x00	,0x00	,0x03	,
0x40	,0x0A	,0x01	,0x00	,0x00	,0x01	,
0xA0	,0x0E	,0x0E	,0x00	,0x00	,0x02	,
0x00	,0x00	,0x00	,0x00	,0x00	,0x00	,
0x00	,0x00	,0x00	,0x00	,0x00	,0x00	,
0x00	,0x00	,0x00	,0x00	,0x00	,0x00	,					};
const unsigned char  lut_wb[] ={	
0x80	,0x08	,0x00	,0x00	,0x00	,0x02,	
0x90	,0x28	,0x28	,0x00	,0x00	,0x01,	
0x80	,0x14	,0x00	,0x00	,0x00	,0x01,	
0x50	,0x12	,0x12	,0x00	,0x00	,0x01,	
0x00	,0x00	,0x00	,0x00	,0x00	,0x00,	
0x00	,0x00	,0x00	,0x00	,0x00	,0x00,	
0x00	,0x00	,0x00	,0x00	,0x00	,0x00,	};
const unsigned char  lut_bb[] ={	
0x80	,0x08	,0x00	,0x00	,0x00	,0x02,	
0x90	,0x28	,0x28	,0x00	,0x00	,0x01,	
0x80	,0x14	,0x00	,0x00	,0x00	,0x01,	
0x50	,0x12	,0x12	,0x00	,0x00	,0x01,	
0x00	,0x00	,0x00	,0x00	,0x00	,0x00,	
0x00	,0x00	,0x00	,0x00	,0x00	,0x00,	
0x00	,0x00	,0x00	,0x00	,0x00	,0x00,	};

/////////////////////////////////��ˢ/////////////////////////////////////////////
const unsigned char  lut_vcom1[] ={
0x00	,0x19	,0x01	,0x00	,0x00	,0x01,
0x00	,0x00	,0x00	,0x00	,0x00	,0x00,
0x00	,0x00	,0x00	,0x00	,0x00	,0x00,
0x00	,0x00	,0x00	,0x00	,0x00	,0x00,
0x00	,0x00	,0x00	,0x00	,0x00	,0x00,
0x00	,0x00	,0x00	,0x00	,0x00	,0x00,
0x00	,0x00	,0x00	,0x00	,0x00	,0x00,
0x00	,0x00,};

const unsigned char  lut_ww1[] ={
0x00	,0x19	,0x01	,0x00	,0x00	,0x01,
0x00	,0x00	,0x00	,0x00	,0x00	,0x00,
0x00	,0x00	,0x00	,0x00	,0x00	,0x00,
0x00	,0x00	,0x00	,0x00	,0x00	,0x00,
0x00	,0x00	,0x00	,0x00	,0x00	,0x00,
0x00	,0x00	,0x00	,0x00	,0x00	,0x00,
0x00	,0x00	,0x00	,0x00	,0x00	,0x00,};

const unsigned char  lut_bw1[] ={
0x80	,0x19	,0x01	,0x00	,0x00	,0x01,	
0x00	,0x00	,0x00	,0x00	,0x00	,0x00,	
0x00	,0x00	,0x00	,0x00	,0x00	,0x00,	
0x00	,0x00	,0x00	,0x00	,0x00	,0x00,	
0x00	,0x00	,0x00	,0x00	,0x00	,0x00,	
0x00	,0x00	,0x00	,0x00	,0x00	,0x00,	
0x00	,0x00	,0x00	,0x00	,0x00	,0x00,	};

const unsigned char  lut_wb1[] ={
0x40	,0x19	,0x01	,0x00	,0x00	,0x01,	
0x00	,0x00	,0x00	,0x00	,0x00	,0x00,	
0x00	,0x00	,0x00	,0x00	,0x00	,0x00,	
0x00	,0x00	,0x00	,0x00	,0x00	,0x00,	
0x00	,0x00	,0x00	,0x00	,0x00	,0x00,	
0x00	,0x00	,0x00	,0x00	,0x00	,0x00,	
0x00	,0x00	,0x00	,0x00	,0x00	,0x00,	};

const unsigned char  lut_bb1[] ={
0x00	,0x19	,0x01	,0x00	,0x00	,0x01,	
0x00	,0x00	,0x00	,0x00	,0x00	,0x00,	
0x00	,0x00	,0x00	,0x00	,0x00	,0x00,	
0x00	,0x00	,0x00	,0x00	,0x00	,0x00,	
0x00	,0x00	,0x00	,0x00	,0x00	,0x00,	
0x00	,0x00	,0x00	,0x00	,0x00	,0x00,	
0x00	,0x00	,0x00	,0x00	,0x00	,0x00,};


 
/**
  * @brief  ��ʼ��elink4.2inchīˮ���õ���GPIO����
  * @param  ��
  * @retval ��
  */
void elink_lcd_gpio_config(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;
	
  LCD_RST_GPIO_CLK_ENABLE();
  GPIO_InitStructure.Pin = LCD_RST_GPIO_PIN;    // RST
  GPIO_InitStructure.Speed = GPIO_SPEED_FREQ_HIGH;
	GPIO_InitStructure.Pull  = GPIO_NOPULL;
  GPIO_InitStructure.Mode = GPIO_MODE_OUTPUT_PP;
  HAL_GPIO_Init(LCD_RST_GPIO_PORT, &GPIO_InitStructure);

	LCD_BUSY_GPIO_CLK_ENABLE();
  GPIO_InitStructure.Pin = LCD_BUSY_GPIO_PIN;    //BUSY input
  GPIO_InitStructure.Speed = GPIO_SPEED_FREQ_HIGH;
  GPIO_InitStructure.Mode = GPIO_MODE_INPUT;	/*!< Input Floating Mode */
  HAL_GPIO_Init(LCD_BUSY_GPIO_PORT, &GPIO_InitStructure);
	
  LCD_BS_GPIO_CLK_ENABLE();
  GPIO_InitStructure.Pin = LCD_BS_GPIO_PIN;    //BS
  GPIO_InitStructure.Speed = GPIO_SPEED_FREQ_HIGH;
  GPIO_InitStructure.Mode = GPIO_MODE_OUTPUT_PP;
  HAL_GPIO_Init(LCD_BS_GPIO_PORT, &GPIO_InitStructure);
}


/**
  * @brief  elink4.2inchīˮ��Ӳ����λ
  * @param  ��
  * @retval ��
  */
void elink_epd_w21_reset(void)
{
	PRINT_DEBUG( "[%s] Enter...\r\n",__FUNCTION__ );
	
	nBS_L;				//4 wire spi mode selected
	
	nRST_L;				//module reset	
	osDelay(1000);
	nRST_H;
	osDelay(1000);
	
	PRINT_DEBUG( "[%s] Exit...\r\n",__FUNCTION__ );

}


/**
  * @brief  elink4.2inchīˮ��Ӳ�����BUSY��״̬
  * @param  ��
  * @retval ��
  */
void elink_check_busy_status(void)
{
	unsigned char busy;
	do
	{
		SPI4W_WRITECOM(0x71);//Get Status (FLG)
		busy = nBUSY;
		busy =!(busy & 0x01);        
	}
	while(busy);   
	osDelay(100); //200                      
}


/**
  * @brief  elink4.2inchīˮ������������
  * @param  ��
  * @retval ��
  */
void elink_booster_soft_start(void)
{
	PRINT_DEBUG( "[%s] Enter...\r\n",__FUNCTION__ );
	
	/**	Booster soft start	**/
	SPI4W_WRITECOM(0x06);         
	SPI4W_WRITEDATA (0x17);
	SPI4W_WRITEDATA (0x17);
	SPI4W_WRITEDATA (0x17);
	
	PRINT_DEBUG( "[%s] Exit...\r\n",__FUNCTION__ );
}


/**
  * @brief  elink 4.2 inch ePaper panel setting
  * @param  None
  * @retval None
  */
void elink_soft_panel_set(void)
{
	/****Panel setting****/
//	SPI4W_WRITECOM(0x00);
//	SPI4W_WRITEDATA(0x1f);
	
	SPI4W_WRITECOM(0x00);			//panel setting
	SPI4W_WRITEDATA(0xbf);		//KW-BF   KWR-AF	BWROTP 0f	BWOTP 1f
	SPI4W_WRITEDATA(0x0d); 
}


/**
  * @brief  elink 4.2 inch ePaper Vcom and data interval setting
  * @param  None
  * @retval None
  */
void elink_soft_vcom_set(void)
{
	/**Vcom and data interval setting**/
	SPI4W_WRITECOM(0X50);
	SPI4W_WRITEDATA(0x17);		//border floating	 
}


/**
  * @brief  elink 4.2 inch ePaper Display Refresh control
  * @param  None
  * @retval None
  */
void elink_soft_disp_refresh(void)
{
	/***Display refresh**/
	SPI4W_WRITECOM(0x12);
}


/**
  * @brief  elink 4.2 inch ePaper power control
	* @param  unsigned char status : 1--Power ON; 0--Power OFF
  * @retval None
  */
void elink_soft_power_switch(unsigned char status)
{
	if(status)
	{
		/**	Power on	**/
		SPI4W_WRITECOM(0x04);  
	}
	else
	{
		/**Power off**/
		SPI4W_WRITECOM(0X02);   	
	}
   
}


/**
  * @brief  elink 4.2 inch ePaper deep sleep
  * @param  None
  * @retval None
  */
void elink_soft_deep_sleep(void)
{
	/**deep sleep**/
	SPI4W_WRITECOM(0X07);
	SPI4W_WRITEDATA(0xA5);
}


/**
  * @brief  elink 4.2 inch ePaper display white update
	* @param  None
  * @retval None
  */
void display_white(void)//
{
	UINT16 i = 0;
	
	SPI4W_WRITECOM(0x10);
	
	for(i=0;i<15000;i++)	     
	{
		SPI4W_WRITEDATA(0x00); //old pic_black 
	}  

	SPI4W_WRITECOM(0x13);
	for(i=0;i<15000;i++)	     
	{
		SPI4W_WRITEDATA(0xFF); //display white   
	}  
}   


/**
  * @brief  elink 4.2 inch ePaper power control
	* @param  unsigned char status : 1--Power ON; 0--Power OFF
  * @retval None
  */
void elink_framebuffer_display(const unsigned char * pStr)
{
	uint16_t i = 0;
	
	PRINT_DEBUG( "\r\n[%s] send display buffer[] START...\r\n",__FUNCTION__ );
	
	/**Data start transmission 1**/
	SPI4W_WRITECOM(0x10);	 
	for(i=0;i<15000;i++)	     
	{
		SPI4W_WRITEDATA(0xFF);  //Transport old data
	}  
	osDelay(2);
		
	/**Data start transmission 2**/
	SPI4W_WRITECOM(0x13);
	for(i=0;i<15000;i++)	     
	{		
		SPI4W_WRITEDATA(*(pStr+i));//Transport new data		
	}  
	osDelay(2);	           

	PRINT_DEBUG( "\r\n[%s] send display buffer[] END...\r\n",__FUNCTION__ );
}


/**
  * @brief  elink 4.2 inch ePaper power control
	* @param  unsigned char status : 1--Power ON; 0--Power OFF
  * @retval None
  */
void lut(void)
{
	unsigned int count;
	SPI4W_WRITECOM(0x20);
	for(count=0;count<44;count++)	     
		{SPI4W_WRITEDATA(lut_vcomDC[count]);}

	SPI4W_WRITECOM(0x21);
	for(count=0;count<42;count++)	     
		{SPI4W_WRITEDATA(lut_ww[count]);}   
	
	SPI4W_WRITECOM(0x22);
	for(count=0;count<42;count++)	     
		{SPI4W_WRITEDATA(lut_bw[count]);} 

	SPI4W_WRITECOM(0x23);
	for(count=0;count<42;count++)	     
		{SPI4W_WRITEDATA(lut_wb[count]);} 

	SPI4W_WRITECOM(0x24);
	for(count=0;count<42;count++)	     
		{SPI4W_WRITEDATA(lut_bb[count]);} 
}


/**
  * @brief  elink 4.2 inch ePaper power control
	* @param  unsigned char status : 1--Power ON; 0--Power OFF
  * @retval None
  */
void lut1(void)
{
	unsigned int count;
	
	SPI4W_WRITECOM(0x20);	
	for(count = 0; count < 44; count++)	     
	{
		SPI4W_WRITEDATA(lut_vcom1[count]);
	}

	SPI4W_WRITECOM(0x21);
	for(count = 0; count < 42; count++)	 	     
	{
		SPI4W_WRITEDATA(lut_ww1[count]);
	}   

	SPI4W_WRITECOM(0x22);
	for(count = 0; count < 42; count++)	 	     
	{
		SPI4W_WRITEDATA(lut_bw1[count]);
	}   	

	SPI4W_WRITECOM(0x23);
	for(count = 0; count < 42; count++)	 	     
	{
		SPI4W_WRITEDATA(lut_wb1[count]);
	}
	
	SPI4W_WRITECOM(0x24);
	for(count = 0; count < 42; count++)	 	     
	{
		SPI4W_WRITEDATA(lut_bb1[count]);
	}  
}

/**
  * @brief  elink 4.2 inch ePaper display init
  * @param  ��
  * @retval ��
  */
/********BWR mode & LUT from Register*******/
void elink_display_init(void)
{ 
	PRINT_DEBUG( "[%s] elink 4.2 inch ePaper display initial START...\r\n",__FUNCTION__ );
	
	/**EPD driver IC reset**/
	elink_epd_w21_reset(); 	
	
	/**	Booster soft start	**/
	elink_booster_soft_start();

	/**	POWER SETTING	**/
	SPI4W_WRITECOM(0x01);
	SPI4W_WRITEDATA (0x03);	          
	SPI4W_WRITEDATA (0x00);
	SPI4W_WRITEDATA (0x2b);
	SPI4W_WRITEDATA (0x2b);
	
	/**	Power on	**/
	elink_soft_power_switch(1);
	
	PRINT_DEBUG( "\r\n[%s] elink_check_busy_status START...\r\n",__FUNCTION__ );
  /**Check BUSY pin**/
	elink_check_busy_status();
	PRINT_DEBUG( "\r\n[%s] elink_check_busy_status END...\r\n",__FUNCTION__ );		
	
	/****Panel setting****/
	elink_soft_panel_set();

	SPI4W_WRITECOM(0x30);			//PLL setting
	SPI4W_WRITEDATA (0x3A);      	// 3A 100HZ   29 150Hz 39 200HZ	31 171HZ
	
	SPI4W_WRITECOM(0x61);			//Resolution setting
	SPI4W_WRITEDATA(0x01); 	//400
	SPI4W_WRITEDATA(0x90);        
	SPI4W_WRITEDATA(0x01);	//300
	SPI4W_WRITEDATA(0x2c);

	SPI4W_WRITECOM(0x82);			//vcom_DC setting
	SPI4W_WRITEDATA (0x28);				   

	SPI4W_WRITECOM(0X50);			//VCOM AND DATA INTERVAL SETTING			
	SPI4W_WRITEDATA(0x97);		//97white border 77black border		VBDF 17|D7 VBDW 97 VBDB 57		VBDF F7 VBDW 77 VBDB 37  VBDR B7
	
	lut();
	
	/***Display gImage_pic001**/
	elink_framebuffer_display(gImage_pic001);//gImage_pic001	gWord_data001

	/***Display refresh**/
	elink_soft_disp_refresh();	
	osDelay(100);	
	
	PRINT_DEBUG( "\r\n[%s] elink_check_busy_status START...\r\n",__FUNCTION__ );
  /**Check BUSY pin**/
	elink_check_busy_status();
	PRINT_DEBUG( "\r\n[%s] elink_check_busy_status END...\r\n",__FUNCTION__ );	
	
	/*** clean screen **/
	display_white();	//display white background
	
	/***Display refresh**/
	elink_soft_disp_refresh();	
	osDelay(100);
	
	PRINT_DEBUG( "\r\n[%s] elink_check_busy_status START...\r\n",__FUNCTION__ );
  /**Check BUSY pin**/
	elink_check_busy_status();
	PRINT_DEBUG( "\r\n[%s] elink_check_busy_status END...\r\n",__FUNCTION__ );	
	
	PRINT_DEBUG( "\r\n[%s] elink 4.2 inch ePaper display initial END ...\r\n",__FUNCTION__ );
}



/***************************partial display function*************************************/
void partial_display(UINT8 x_start1, UINT8 x_start2, UINT8 x_end1, UINT8 x_end2, UINT8 y_start1, UINT8 y_start2, UINT8 y_end1, UINT8 y_end2, UINT8* pOldBuff, UINT8* pNewBuff, UINT16 length)
{
		unsigned int i;

		PRINT_DEBUG( "\r\n[%s] Enter...\r\n",__FUNCTION__ );	
		
//		SPI4W_WRITECOM(0X50);
//		SPI4W_WRITEDATA(0x47);	//0x47 White background; 0x17 Black background

//		lut1();		

		SPI4W_WRITECOM(0x91);			//enter partial display mode

		SPI4W_WRITECOM(0x90);			//resolution setting	
		SPI4W_WRITEDATA (x_start1); 		//x-start[8]
		SPI4W_WRITEDATA (x_start2);    //x-start[7:0]
		SPI4W_WRITEDATA (x_end1); 			//x-end[8]  
		SPI4W_WRITEDATA (x_end2);   		//x-end[7:0] 

		SPI4W_WRITEDATA (y_start1); 		//y-start[8]
		SPI4W_WRITEDATA (y_start2);    //y-start[7:0]
		SPI4W_WRITEDATA (y_end1); 			//y-end[8]
		SPI4W_WRITEDATA (y_end2);   		//y-end[7:0]

		PRINT_DEBUG( "\r\n[%s] Start to send old buffer[%d]...\r\n", __FUNCTION__, length );	
		//partial display pic
		SPI4W_WRITECOM(0x10);
		for(i=0; i<length; i++)	  //32 CN; 16 EN
		{
			SPI4W_WRITEDATA(*(pOldBuff+i));  
		}  
		PRINT_DEBUG( "\r\n[%s] Start to send new buffer[%d]...\r\n", __FUNCTION__, length );	
		SPI4W_WRITECOM(0x13);
		for(i=0; i<length; i++)	     
		{
			SPI4W_WRITEDATA(*(pNewBuff+i));  
		}  
		PRINT_DEBUG( "\r\n[%s] Finish sending buffers...\r\n",__FUNCTION__ );	
		
	
		SPI4W_WRITECOM(0x12);			//DISPLAY REFRESH 		             
		//osDelay(100);
		
		elink_check_busy_status();
		
		PRINT_DEBUG( "\r\n[%s] Exit...\r\n",__FUNCTION__ );	
}



/*********************************************END OF FILE**********************/
