
#ifndef BSP_STM32FLASH_H_
#define BSP_STM32FLASH_H_

#include "stdint.h"

void BSP_STM32FLASH_Init(void);
void BSP_STM32FLASH_WritePage(uint32_t data[], int len, int page);
void BSP_STM32FLASH_ReadPage(uint32_t data[], int len, int page);
void BSP_STM32FLASH_Test(void);

#endif 
