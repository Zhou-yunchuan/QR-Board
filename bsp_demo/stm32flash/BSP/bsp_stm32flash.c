

#include "bsp_stm32flash.h"
#include "main.h"
#include "bsp_usart.h"

/*
    0x0800 -> 2k
    addr = page*0x0800 + FLASH_BASE_ADDRESS
    page = (addr - FLASH_BASE_ADDRESS)/0x0800
    0 <= page <= 63
*/

#define FLASH_BASE_ADDRESS (0x08000000)

void BSP_STM32FLASH_WriteAddr(uint32_t len, uint64_t data[], uint32_t addr);
void BSP_STM32FLASH_ReadAddr(uint32_t len, uint32_t data[], uint32_t addr);

void BSP_STM32FLASH_Init(void)
{

}

void BSP_STM32FLASH_Test(void)
{

    const uint8_t LEN = 4;
    uint32_t write_data[LEN] = {2,4,8,16};
    uint32_t read_data[LEN] = {0};

    printf("set data zero !\r\n");
    for(int i=0;i<LEN;i++)
    {
        read_data[i] = 0;
        printf("data[%d] = %d\r\n",i, read_data[i]);
    }

    BSP_STM32FLASH_WritePage(write_data, LEN, 50);
    BSP_STM32FLASH_ReadPage(read_data, LEN, 50);

    printf("read stm32flash is ok !\r\n");
    for(int i=0;i<LEN;i++)
    {
        printf("data[%d] = %d\r\n",i, read_data[i]);
    }
    printf("\r\n");
}


void BSP_STM32FLASH_WritePage(uint32_t data[], int len, int page)
{
    uint32_t flash_addr = page*0x0800 + FLASH_BASE_ADDRESS;
    uint64_t temp[4] = {0};
    for(int i=0;i<len/2;i++)
    {
        temp[i] = (uint64_t)data[2*i+1]<<32 | (uint64_t)data[2*i];
    }
    BSP_STM32FLASH_WriteAddr(len/2, temp, flash_addr);
}


void BSP_STM32FLASH_ReadPage(uint32_t data[], int len, int page)
{
    uint32_t flash_addr = page*0x0800 + FLASH_BASE_ADDRESS;
    BSP_STM32FLASH_ReadAddr(len,data,flash_addr);
}


void BSP_STM32FLASH_WriteAddr(uint32_t len, uint64_t data[], uint32_t addr)
{
    uint16_t page = (addr-FLASH_BASE_ADDRESS)/0x0800;
    HAL_FLASH_Unlock();
    FLASH_EraseInitTypeDef FLASH_InitStruct;
    FLASH_InitStruct.TypeErase = FLASH_TYPEERASE_PAGES;
    FLASH_InitStruct.Banks = FLASH_BANK_1;
    FLASH_InitStruct.Page = page;
    FLASH_InitStruct.NbPages = 1;
    uint32_t PageError = 0;
    HAL_FLASHEx_Erase(&FLASH_InitStruct, &PageError);
    for(int i=0;i<len;i++)
    {
        HAL_FLASH_Program(FLASH_TYPEPROGRAM_DOUBLEWORD, addr+i*8, data[i]);
    }
    HAL_FLASH_Lock();
}


void BSP_STM32FLASH_ReadAddr(uint32_t len, uint32_t data[], uint32_t addr)
{
    for(int i=0; i<len; i++)
    {
        data[i] = *(__IO uint32_t*)(addr+4*i);
    }
}


