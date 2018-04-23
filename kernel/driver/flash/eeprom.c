/**
  ******************************************************************************
  * File Name          : main.c
  * Description        : Main program body
  ******************************************************************************
  *
  * COPYRIGHT(c) 2015 STMicroelectronics
  *
  * Redistribution and use in source and binary forms, with or without modification,
  * are permitted provided that the following conditions are met:
  *   1. Redistributions of source code must retain the above copyright notice,
  *      this list of conditions and the following disclaimer.
  *   2. Redistributions in binary form must reproduce the above copyright notice,
  *      this list of conditions and the following disclaimer in the documentation
  *      and/or other materials provided with the distribution.
  *   3. Neither the name of STMicroelectronics nor the names of its contributors
  *      may be used to endorse or promote products derived from this software
  *      without specific prior written permission.
  *
  * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
  * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
  * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
  * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
  * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
  * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
  * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
  */
/* Includes ------------------------------------------------------------------*/

#include "eeprom.h"
#include "stdio.h"

#ifdef LOS_STM32L476xx
#include "stm32l4xx_hal.h"
#include "stm32l4xx_nucleo.h"
#endif

#include "los_demo_debug.h"

#if 1
/* USER CODE BEGIN Includes */

#define EEPROM_BASE_ADDR    0x08080000    
#define EEPROM_BYTE_SIZE    0x80000 	//512K

#define FLASH_ROW_SIZE          32

/* USER CODE END Includes */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */
static FLASH_EraseInitTypeDef EraseInitStruct;

static uint32_t GetBank(uint32_t Address);


/* USER CODE END PFP */

/* USER CODE BEGIN 0 */

__IO uint64_t data64 = 0;
uint8_t data_index = 0;


static const uint64_t Data64_To_Prog[FLASH_ROW_SIZE] = {
  0x0000000000000000, 0x1111111111111111, 0x2222222222222222, 0x3333333333333333,
  0x4444444444444444, 0x5555555555555555, 0x6666666666666666, 0x7777777777777777,
  0x8888888888888888, 0x9999999999999999, 0xAAAAAAAAAAAAAAAA, 0xBBBBBBBBBBBBBBBB,
  0xCCCCCCCCCCCCCCCC, 0xDDDDDDDDDDDDDDDD, 0xEEEEEEEEEEEEEEEE, 0xFFFFFFFFFFFFFFFF,
  0x0011001100110011, 0x2233223322332233, 0x4455445544554455, 0x6677667766776677,
  0x8899889988998899, 0xAABBAABBAABBAABB, 0xCCDDCCDDCCDDCCDD, 0xEEFFEEFFEEFFEEFF,
  0x2200220022002200, 0x3311331133113311, 0x6644664466446644, 0x7755775577557755,
  0xAA88AA88AA88AA88, 0xBB99BB99BB99BB99, 0xEECCEECCEECCEECC, 0xFFDDFFDDFFDDFFDD};
/* USER CODE END 0 */


/* USER CODE BEGIN 4 */
/**
  * WriteFlash(void)
*/ 
	
void WriteFlash(void)
{
		uint32_t Address = 0;
		uint32_t BankNumber = 0;
		uint32_t PAGEError = 0;
	
		HAL_FLASH_Unlock();
		__HAL_FLASH_CLEAR_FLAG(FLASH_FLAG_OPTVERR); 
		BankNumber = GetBank(FLASH_USER_START_ADDR);

		EraseInitStruct.TypeErase = FLASH_TYPEERASE_MASSERASE;
		EraseInitStruct.Banks     = BankNumber;

		/* Erase flash */
		if (HAL_FLASHEx_Erase(&EraseInitStruct, &PAGEError) != HAL_OK)
		{
			while (1)
			{
				printf("[%s] line[%d] Erase flash Error !\r\n", __FUNCTION__, __LINE__);
			}
		}
		
		Address = FLASH_USER_START_ADDR;

		while (Address < (FLASH_USER_START_ADDR + (FLASH_ROW_SIZE*sizeof(uint64_t))))
		{
			/* Program flash with double-word */
			if (HAL_FLASH_Program(FLASH_TYPEPROGRAM_FAST, Address, (uint64_t)Data64_To_Prog) == HAL_OK)
			{
				Address = Address + (FLASH_ROW_SIZE*sizeof(uint64_t));
			}
			else
			{
				while (1)
				{
					printf("[%s] line[%d] Program flash with double-word Error !\r\n", __FUNCTION__, __LINE__);
				}
			}
		}
		if (HAL_FLASH_Program(FLASH_TYPEPROGRAM_FAST_AND_LAST, Address, (uint64_t)Data64_To_Prog) != HAL_OK)
		{
			while (1)
			{
				printf("[%s] line[%d] Erase flash Error !\r\n", __FUNCTION__, __LINE__);
			}
		}

		HAL_FLASH_Lock();
		printf("[%s] line[%d] Flash write OK.\n\r", __FUNCTION__, __LINE__);
		printf("FLASH_ROW_SIZE=%d\n\r",(FLASH_ROW_SIZE*sizeof(uint64_t)));
}

/**
  * ReadFlash
*/ 
	
void ReadFlash(void)
{
		uint32_t Address = 0;
		__IO uint32_t MemoryProgramStatus = 0;
	
		Address = FLASH_USER_START_ADDR;
		MemoryProgramStatus = 0x0;

		while (Address < (FLASH_USER_START_ADDR + (FLASH_ROW_SIZE*sizeof(uint64_t))))
		{
			for (data_index = 0; data_index < FLASH_ROW_SIZE; data_index++)
			{
				data64 = *(__IO uint64_t *)Address;
				printf("data64 = %#llx\r",data64);
				if(data64 != Data64_To_Prog[data_index])
				{
					MemoryProgramStatus++;
				}
				Address = Address + sizeof(uint64_t);
			}
		}

		/*Check if there is an issue to program data*/
		if (MemoryProgramStatus == 0)
		{
			/* No error detected. Switch on LED1*/
			printf("No error detected\n\r");
		}
		else
		{
			/* Error detected. Switch on LED2*/
			printf("Error detected\n\r");
		}

}


/*------------------------------------------------------------ 
 Func: EEPROM read by Byte
 Note: 
-------------------------------------------------------------*/  
void EEPROM_ReadBytes(u32 Addr,u8 *Buffer,u16 Length)  
{  
    u8 * pcAddr;
  
    pcAddr=(u8 *)(EEPROM_BASE_ADDR+Addr);
  
    while(Length--)
		{  
        *Buffer++=*pcAddr++;
    }     
}


/*------------------------------------------------------------ 
 Func: EEPROM read by Word
 Note: 
-------------------------------------------------------------*/  
void EEPROM_ReadWords(u16 Addr,u16 *Buffer,u16 Length)  
{  
    u32 *wAddr;  
    wAddr=(u32 *)(EEPROM_BASE_ADDR+Addr);  
    while(Length--)
		{  
        *Buffer++=*wAddr++;  
    }     
}  


/**
  * @}
  */ 

static uint32_t GetBank(uint32_t Addr)
{
  uint32_t bank = 0;
  
  if (READ_BIT(SYSCFG->MEMRMP, SYSCFG_MEMRMP_FB_MODE) == 0)
  {
  	/* No Bank swap */
    if (Addr < (FLASH_BASE + FLASH_BANK_SIZE))
    {
      bank = FLASH_BANK_1;
    }
    else
    {
      bank = FLASH_BANK_2;
    }
  }
  else
  {
  	/* Bank swap */
    if (Addr < (FLASH_BASE + FLASH_BANK_SIZE))
    {
      bank = FLASH_BANK_2;
    }
    else
    {
      bank = FLASH_BANK_1;
    }
  }
  
  return bank;
}


#endif

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
