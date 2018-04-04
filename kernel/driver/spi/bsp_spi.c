

#include "bsp_spi.h"   
#include "cmsis_os.h"


void elink_spi_gpio_config(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;	

  SPI_CLK_GPIO_CLK_ENABLE();
  GPIO_InitStructure.Pin = SPI_CLK_GPIO_PIN;    // CLK
  GPIO_InitStructure.Speed = GPIO_SPEED_FREQ_HIGH;
	GPIO_InitStructure.Pull  = GPIO_NOPULL;
  GPIO_InitStructure.Mode = GPIO_MODE_OUTPUT_PP;
  HAL_GPIO_Init(SPI_CLK_GPIO_PORT, &GPIO_InitStructure);
	
  SPI_SDA_GPIO_CLK_ENABLE();
  GPIO_InitStructure.Pin = SPI_SDA_GPIO_PIN;    //SDA
  GPIO_InitStructure.Speed = GPIO_SPEED_FREQ_HIGH;
  GPIO_InitStructure.Mode = GPIO_MODE_OUTPUT_PP;
  HAL_GPIO_Init(SPI_SDA_GPIO_PORT, &GPIO_InitStructure);

  SPI_nDC_GPIO_CLK_ENABLE();
  GPIO_InitStructure.Pin = SPI_nDC_GPIO_PIN;    //D/C
  GPIO_InitStructure.Speed = GPIO_SPEED_FREQ_HIGH;
  GPIO_InitStructure.Mode = GPIO_MODE_OUTPUT_PP;
  HAL_GPIO_Init(SPI_nDC_GPIO_PORT, &GPIO_InitStructure);

	SPI_nCS_GPIO_CLK_ENABLE();
  GPIO_InitStructure.Pin   = SPI_nCS_GPIO_PIN;	// CS
  GPIO_InitStructure.Mode  = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStructure.Pull  = GPIO_NOPULL;
  GPIO_InitStructure.Speed = GPIO_SPEED_FREQ_HIGH;
  HAL_GPIO_Init(SPI_nCS_GPIO_PORT, &GPIO_InitStructure);	
	
}


 /**
  * @brief  ���� SPI4W_WRITECOM ����
  * @param  ��
  * @retval ��
  */
void SPI4W_WRITECOM(unsigned char INIT_COM)
{
	unsigned char TEMPCOM;
	unsigned char scnt;
	TEMPCOM=INIT_COM;
	nCS_H;
	nCS_L;
	SCLK_L; 
	nDC_L;	//0 , CMD; 1 , DATA
	
	for(scnt=0;scnt<8;scnt++)
	{
		if(TEMPCOM&0x80)
			SDA_H;
		else
			SDA_L;
		
		delay_us(1);
		SCLK_H;  
		delay_us(1);
		SCLK_L;   
		TEMPCOM=TEMPCOM<<1;
		delay_us(1);
	}
	
	nCS_H;  
}


 /**
  * @brief  ���� SPI4W_WRITECOM ����
  * @param  ��
  * @retval ��
  */
void SPI4W_WRITEDATA(unsigned char INIT_DATA)
{
	unsigned char TEMPCOM;
	unsigned char scnt;
	TEMPCOM=INIT_DATA;
	nCS_H;
	nCS_L;
	SCLK_L; 
	nDC_H;	//0 , CMD; 1 , DATA
	
	for(scnt=0;scnt<8;scnt++)
	{
		if(TEMPCOM&0x80)
			SDA_H;
		else
			SDA_L;
		
		delay_us(1);
		SCLK_H;		
		delay_us(1);
		SCLK_L;
		
		TEMPCOM=TEMPCOM<<1;
		delay_us(1);
	}
	
	nCS_H; 
}



/*********************************************END OF FILE**********************/
